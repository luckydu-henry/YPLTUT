#include "window.h"
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

// 全局空间内的函数
namespace {
    // 这个函数可以通过图片的原始数据，即内存缓冲来创建 HICON
    // HICON 可以被用于 cursor 或者 window-icon 的设置
    static HICON MakeIcon(unsigned char* _pixels, int _width, int _height, int _channel) {

        if (_pixels == nullptr || _width == 0 || _height == 0) return nullptr;

        Gdiplus::GdiplusStartupInput  gdiplus_startupinout;
        ULONG_PTR                     gdiplus_token;

        Gdiplus::GdiplusStartup(&gdiplus_token, &gdiplus_startupinout, nullptr);

        BITMAPINFO bmi;
        memset(&bmi, 0, sizeof(bmi));
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = _height;
        bmi.bmiHeader.biHeight = _width;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_BITFIELDS;
        bmi.bmiHeader.biBitCount = _channel * 8;

        Gdiplus::Bitmap* myImage = Gdiplus::Bitmap::FromBITMAPINFO(&bmi, _pixels);
        HICON icon = nullptr;

        if (myImage->GetWidth()) {
            myImage->GetHICON(&icon);
            delete myImage;
        }

        Gdiplus::GdiplusShutdown(gdiplus_token);
        return icon;
    }
}

namespace yan {

    using namespace platform;

    // 实例计数。
    uint8_t win32_window::_S_inst_count = 0;
    MSG _Inline_message;

    win32_window::win32_window(const wndconfig& _cfg)
        :_M_inst(GetModuleHandle(nullptr)), 
         _M_name(_cfg.title),
         _M_cur(nullptr),
         _M_wndsize({ _cfg.width, _cfg.height}) {
        _S_inst_count++;

        auto ico = MakeIcon(_cfg.icon.pixels, _cfg.icon.width, _cfg.icon.height, _cfg.icon.channels);
        _M_cur   = MakeIcon(_cfg.cursor.pixels, _cfg.cursor.width, _cfg.cursor.height, _cfg.cursor.channels);

        WNDCLASSEXA windowclass = {  };
        windowclass.cbSize = sizeof(windowclass);
        windowclass.style = CS_OWNDC;
        windowclass.lpfnWndProc = _M_HandleMsgSetup;
        windowclass.cbClsExtra = 0;
        windowclass.cbWndExtra = 0;
        windowclass.hInstance = _M_inst;
        windowclass.hIcon   = ico;
        windowclass.hCursor = _M_cur;
        windowclass.hbrBackground = nullptr;
        windowclass.lpszMenuName = nullptr;
        windowclass.lpszClassName = _M_name.data();
        windowclass.hIconSm = ico;
        RegisterClassExA(&windowclass);

        //! Make width and hight only for client area.
        RECT wr = {};
        wr.left = 100;
        wr.right =_cfg.width + wr.left;
        wr.top = 100;
        wr.bottom = _cfg.height + wr.top;

        if (AdjustWindowRect(&wr, 13238272L, 0) == 0)
            throw WIN32_HWND_LASTERR();

        DWORD WndStyle = _cfg.is_fullscreen == true ? WS_POPUP : 13565952L;

        _M_handle = CreateWindowExA(0, _M_name.data(),
            _M_name.data(), WndStyle, // style.
            CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
            nullptr, nullptr, _M_inst, this
        );

        if (_M_handle == nullptr)
            throw WIN32_HWND_LASTERR();

        // I don't know why, but I have to add this line.
        // Or the title showing would be like ...
        SetWindowTextA(_M_handle, _M_name.data());

        if (_M_cur == nullptr) {
            _M_cur = LoadCursorA(nullptr, MAKEINTRESOURCEA(32512)); // To system default icon => arrow.
            ::SetCursor(_M_cur);
        }

    }

    void win32_window::show(void) {
        //! This line will show window.
        ::ShowWindow(_M_handle, 10);
        UpdateWindow(_M_handle);
    }
    
    void win32_window::set_icon(unsigned char* _Pixels, int _width, int _height, int _Channel) {
    
        auto hIcon = ::MakeIcon(_Pixels, _width, _height, _Channel);

        if (!hIcon) {
            throw WIN32_HWND_LASTERR();
        }
        //Change both icons to the same icon handle.
        SendMessageA(_M_handle, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
        SendMessageA(_M_handle, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    
        //This will ensure that the application icon gets changed too.
        SendMessageA(GetWindow(_M_handle, GW_OWNER), WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
        SendMessageA(GetWindow(_M_handle, GW_OWNER), WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    }
    void win32_window::set_cursor(unsigned char* _Pixels, int _width, int _height, int _Channel) {

        _M_cur = ::MakeIcon(_Pixels, _width, _height, _Channel);

        if (_M_cur) {
            ::SetCursor(_M_cur);
            return;
        }
        throw WIN32_HWND_LASTERR();
    }

    void win32_window::set_title(const char* _Name) {
        if (SetWindowTextA(_M_handle, _Name) == 0)
            throw WIN32_HWND_LASTERR();
    }

    void win32_window::full_screen(bool _IsFullScreen) {
        _M_is_full_screen = _IsFullScreen;

        RECT wr = {};

        if (_M_is_full_screen) {
            wr.left = 100;
            wr.right = GetSystemMetrics(SM_CXSCREEN) + wr.left;
            wr.top = 100;
            wr.bottom = GetSystemMetrics(SM_CYSCREEN) + wr.top;

            SetWindowLongA(_M_handle, GWL_STYLE, WS_BORDER);
            SetWindowPos(_M_handle, HWND_TOPMOST, 0, 0, wr.right, wr.bottom, SWP_SHOWWINDOW);
            return;
        }
        GetWindowRect(_M_handle, &wr);
        SetWindowLongA(_M_handle, GWL_STYLE, 13565952L);
        SetWindowPos(_M_handle, HWND_NOTOPMOST, 0, 0,
            wr.right, wr.bottom, SWP_SHOWWINDOW);

        return;
    }

    bool win32_window::full_screen(void) const {
        return _M_is_full_screen;
    }

    void win32_window::cursor_display(bool _ShouldDisplay) {
        _M_is_cursor_display = _ShouldDisplay;
        ShowCursor((BOOL)_M_is_cursor_display);
    }
    bool win32_window::cursor_display(void) const {
        return _M_is_cursor_display;
    }
    bool win32_window::close(void) const {
        return _M_shoule_close;
    }
    void win32_window::close(bool _IsShouldClose) {
        _M_shoule_close = _IsShouldClose == true ? WM_CLOSE : WM_NULL;
        SendMessageA(_M_handle, _M_shoule_close, 0, 0);
    }
    win32_window::~win32_window() {
        //Change both icons to the same icon handle.
        SendMessageA(_M_handle, WM_SETICON, ICON_SMALL, 0);
        SendMessageA(_M_handle, WM_SETICON, ICON_BIG, 0);

        //This will ensure that the application icon gets changed too.
        SendMessageA(GetWindow(_M_handle, GW_OWNER), WM_SETICON, ICON_SMALL, 0);
        SendMessageA(GetWindow(_M_handle, GW_OWNER), WM_SETICON, ICON_BIG, 0);

        if (_M_handle != nullptr)
        {
            DestroyWindow(_M_handle);
            _S_inst_count--;
        }
    }

    LRESULT win32_window::_M_HandleMsgSetup(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept {
        if (msg == WM_NCCREATE)
        {
            const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lp);
            win32_window* const pWnd = static_cast<win32_window*>(pCreate->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
            SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&win32_window::_M_HandleMsgThunk));
            return pWnd->_M_HandleMsg(hwnd, msg, wp, lp);
        }
        return DefWindowProc(hwnd, msg, wp, lp);
    }

    LRESULT win32_window::_M_HandleMsgThunk(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept {
        win32_window* const pWnd = reinterpret_cast<win32_window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        return pWnd->_M_HandleMsg(hwnd, msg, wp, lp);
    }

    // Message handle defination.
    // Will be changing oftenly.
    LRESULT win32_window::_M_HandleMsg(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
        switch (msg)
        {
        case WM_CLOSE:
            if (_S_inst_count == 1)
                PostQuitMessage(0);
            else
                this->~win32_window();

            return 0;
        case WM_SETCURSOR:
            if (LOWORD(lp) == HTCLIENT || LOWORD(lp) == HTBORDER) {
                ::SetCursor(_M_cur);
                return true;
            }
            break;
            /** km_handle events!
            * ================
            * ================ */
        case WM_MOUSEMOVE: {
            const POINTS pt = MAKEPOINTS(lp);
            if (pt.x >= 0 && pt.x < _M_wndsize.first && pt.y >= 0 && pt.y < _M_wndsize.second) {
                km_handle._M_on_mouse(mouse_e::move, { pt.x, pt.y });
                if (!km_handle._M_is_inwindow) {
                    ::SetCapture(_M_handle);
                    km_handle._M_on_mouse(mouse_e::enter);
                }
            }
            else {
                if (wp & (MK_LBUTTON | MK_RBUTTON))
                    km_handle._M_on_mouse(mouse_e::move, { pt.x, pt.y });
                else {
                    ::ReleaseCapture();
                    km_handle._M_on_mouse(mouse_e::leave);
                }
            }

            break;
        }
        // Button handle.
        case WM_LBUTTONDOWN:
            km_handle._M_on_button(_G_press, button_e::left);
            break;
        case WM_RBUTTONDOWN:
            km_handle._M_on_button(_G_press, button_e::right);
            break;
        case WM_MBUTTONDOWN:
            km_handle._M_on_button(_G_press, button_e::middle);
            break;
        case WM_LBUTTONUP:
            km_handle._M_on_button(_G_release, button_e::left);
            break;
        case WM_RBUTTONUP:
            km_handle._M_on_button(_G_release, button_e::right);
            break;
        case WM_MBUTTONUP:
            km_handle._M_on_button(_G_release, button_e::middle);
            break;

            // km_handle wheel handle.
        case WM_MOUSEWHEEL: {
            const POINTS pt = MAKEPOINTS(lp);
            const int delta = GET_WHEEL_DELTA_WPARAM(wp);

            km_handle._M_wheel_delta += delta;
            // Generate events for every 120(WHEEL_DELTA)
            while (km_handle._M_wheel_delta >= 120)
            {
                km_handle._M_wheel_delta -= 120;
                km_handle._M_on_mouse(mouse_e::wup);
            }
            while (km_handle._M_wheel_delta <= -120)
            {
                km_handle._M_wheel_delta += 120;
                km_handle._M_on_mouse(mouse_e::wdown);
            }
            break;
        }
        // km_handle events!
        // ================
        // ================
        // Let window to stop loop a input.
        case WM_KILLFOCUS:
            km_handle._M_first_state.reset();
            break;
            // Set key input handle.
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            switch (wp) {
            case VK_SHIFT:
                km_handle._M_mod_state[0] = false;
                if (GetKeyState(VK_LSHIFT) & 0x8000)
                    km_handle._M_mod_state[1] = true;
                else km_handle._M_mod_state[2] = true;
                break;
            case VK_CONTROL:
                km_handle._M_mod_state[0] = false;
                if (GetKeyState(VK_LCONTROL) & 0x8000)
                    km_handle._M_mod_state[3] = true;
                else km_handle._M_mod_state[4] = true;
                break;
            case VK_MENU:
                km_handle._M_mod_state[0] = false;
                if (GetKeyState(VK_LMENU) & 0x8000)
                    km_handle._M_mod_state[5] = true;
                else km_handle._M_mod_state[6] = true;
                break;
                // Especially for Escape because it doesn't work in the normal way!
            case VK_ESCAPE:
                if (!(lp & 0x40000000) || km_handle._M_is_auto_repeat == true) {
                    km_handle._M_escape_event.is_pressed= true;
                    km_handle._M_escape_event.is_released = false;
                }
                break;
            default:
                if (!(lp & 0x40000000) || km_handle._M_is_auto_repeat == true)
                    km_handle._M_on_key(_G_press, static_cast<unsigned char>(wp));
                break;
            }
            break;
        case WM_KEYUP:
        case WM_SYSKEYUP:

            switch (wp) {
            case VK_SHIFT:
            case VK_MENU:
            case VK_CONTROL:
                km_handle._M_mod_state.reset();
                km_handle._M_mod_state[0] = true;
                break;
                // Especially for Escape because it doesn't work in the normal way!
            case VK_ESCAPE:
                km_handle._M_escape_event.is_pressed  = false;
                km_handle._M_escape_event.is_released = true;
                break;
            default:
                km_handle._M_on_key(_G_release, static_cast<unsigned char>(wp));
                break;
            }
            break;
        }
        //! Set key input handle.
        return DefWindowProc(hwnd, msg, wp, lp);
    }

    void* win32_window::native_handle(void) {
        return _M_handle;
    }

    void win32_window::poll_events() {
        // while queue has message, remove and dispatch them.
        while (PeekMessageA(&_Inline_message, nullptr, 0, 0, PM_REMOVE))
        {
            if (_Inline_message.message == WM_QUIT)
            {
                // return optional wrapping.
                _M_shoule_close = true;
                return;
            }
            TranslateMessage(&_Inline_message);
            DispatchMessageA(&_Inline_message);
        }

        // return empty optional when not quitting app.
        return;
    }
    std::size_t win32_window::get_size(screen_prop _Enum) {
        switch (_Enum)
        {
        case scrwidth: return _M_wndsize.first;
        case scrheight: return _M_wndsize.second;
        }
    }

    kminput& win32_window::kmhandle(){
        return km_handle;
    }

    //! ==============================================
    //! ============== Error Handling ================
    //! ==============================================

    win32_exception::win32_exception(std::source_location _Loc, HRESULT hr) noexcept
        :yan::except(_Loc), _M_result(hr) {}

    const char* win32_exception::what() const noexcept {
        return _M_what.c_str();
    }

    std::string_view win32_exception::err_type() const noexcept {
        return "win32 window error";
    }

    void win32_exception::trans_hresult() {
        char* pMsgBuf = nullptr;
        DWORD nMsgLen = FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM
            | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr, _M_result, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
        );
        if (nMsgLen == 0) return;
        _M_what += pMsgBuf;
        LocalFree(pMsgBuf);
    }

    // utility function
    const std::uint32_t win32_window::get_screenprop(screen_prop _Enum) {
        return GetSystemMetrics(_Enum - 1);
    }

} // namespace yan.