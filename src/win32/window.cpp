#include "window.h"
#include <memory_resource>
#include <vector>
#include <memory_resource>
// 全局空间内的函数
namespace {

static constexpr const char*    Class_name = "CRS_plat_window";
static std::size_t              Instance_count = 0;        

// 这个函数可以通过图片的原始数据，即内存缓冲来创建 HICON
// HICON 可以被用于 cursor 或者 window-icon 的设置
// Windows HICON 使用的是 BGRA 这步是在转换。
static HICON make_ico(const crs::plat::wndimage& img) {
    std::pmr::vector<std::byte> iconPixels(img.width * img.height * 4);
    for (std::size_t i = 0; i < iconPixels.size() >> 2; ++i)
    {
        iconPixels[i << 2 + 0] = img.pixels[i << 2 + 2];
        iconPixels[i << 2 + 1] = img.pixels[i << 2 + 1];
        iconPixels[i << 2 + 2] = img.pixels[i << 2 + 0];
        iconPixels[i << 2 + 3] = img.pixels[i << 2 + 3];
    }
    // Create the icon from the pixel array
    return CreateIcon(GetModuleHandleW(nullptr), img.width, img.height, 1, 32, nullptr, reinterpret_cast<BYTE*>(&iconPixels[0]));
}

static inline crs::plat::kybd::kc trans_virtual_kc(WPARAM key, LPARAM flags) {
    using namespace crs::plat;
    switch (key) {
        // Check the scancode to distinguish between left and right shift
        case VK_SHIFT: {
            static UINT lShift = MapVirtualKeyW(VK_LSHIFT, MAPVK_VK_TO_VSC);
            UINT scancode = static_cast<UINT>((flags & (0xFF << 16)) >> 16);
            return scancode == lShift ? kybd::Lshift : kybd::Rshift;
        }

        // Check the "extended" flag to distinguish between left and right alt
        case VK_MENU: return (HIWORD(flags) & KF_EXTENDED) ? kybd::Ralt : kybd::Lalt;

            // Check the "extended" flag to distinguish between left and right control
        case VK_CONTROL: return (HIWORD(flags) & KF_EXTENDED) ? kybd::Rctrl : kybd::Lctrl;

            // Other keys are reported properly
        case VK_LWIN:       return kybd::Lsuper;
        case VK_RWIN:       return kybd::Rsuper;
        case VK_APPS:       return kybd::menu;
        case VK_OEM_1:      return kybd::semicolon;
        case VK_OEM_2:      return kybd::slash;
        case VK_OEM_PLUS:   return kybd::equal;
        case VK_OEM_MINUS:  return kybd::hyphen;
        case VK_OEM_4:      return kybd::Lbracket;
        case VK_OEM_6:      return kybd::Rbracket;
        case VK_OEM_COMMA:  return kybd::comma;
        case VK_OEM_PERIOD: return kybd::period;
        case VK_OEM_7:      return kybd::quote;
        case VK_OEM_5:      return kybd::backslash;
        case VK_OEM_3:      return kybd::tilde;
        case VK_ESCAPE:     return kybd::escape;
        case VK_SPACE:      return kybd::space;
        case VK_RETURN:     return kybd::enter;
        case VK_BACK:       return kybd::backspace;
        case VK_TAB:        return kybd::tab;
        case VK_PRIOR:      return kybd::pgup;
        case VK_NEXT:       return kybd::pgdn;
        case VK_END:        return kybd::end;
        case VK_HOME:       return kybd::home;
        case VK_INSERT:     return kybd::insert;
        case VK_DELETE:     return kybd::del;
        case VK_ADD:        return kybd::add;
        case VK_SUBTRACT:   return kybd::sub;
        case VK_MULTIPLY:   return kybd::mul;
        case VK_DIVIDE:     return kybd::div;
        case VK_PAUSE:      return kybd::pause;
        case VK_F1:         return kybd::F1;
        case VK_F2:         return kybd::F2;
        case VK_F3:         return kybd::F3;
        case VK_F4:         return kybd::F4;
        case VK_F5:         return kybd::F5;
        case VK_F6:         return kybd::F6;
        case VK_F7:         return kybd::F7;
        case VK_F8:         return kybd::F8;
        case VK_F9:         return kybd::F9;
        case VK_F10:        return kybd::F10;
        case VK_F11:        return kybd::F11;
        case VK_F12:        return kybd::F12;
        case VK_F13:        return kybd::F13;
        case VK_F14:        return kybd::F14;
        case VK_F15:        return kybd::F15;
        case VK_LEFT:       return kybd::left;
        case VK_RIGHT:      return kybd::right;
        case VK_UP:         return kybd::up;
        case VK_DOWN:       return kybd::down;
        case VK_NUMPAD0:    return kybd::NP0;
        case VK_NUMPAD1:    return kybd::NP1;
        case VK_NUMPAD2:    return kybd::NP2;
        case VK_NUMPAD3:    return kybd::NP3;
        case VK_NUMPAD4:    return kybd::NP4;
        case VK_NUMPAD5:    return kybd::NP5;
        case VK_NUMPAD6:    return kybd::NP6;
        case VK_NUMPAD7:    return kybd::NP7;
        case VK_NUMPAD8:    return kybd::NP8;
        case VK_NUMPAD9:    return kybd::NP9;
        case 'A':           return kybd::A;
        case 'Z':           return kybd::Z;
        case 'E':           return kybd::E;
        case 'R':           return kybd::R;
        case 'T':           return kybd::T;
        case 'Y':           return kybd::Y;
        case 'U':           return kybd::U;
        case 'I':           return kybd::I;
        case 'O':           return kybd::O;
        case 'P':           return kybd::P;
        case 'Q':           return kybd::Q;
        case 'S':           return kybd::S;
        case 'D':           return kybd::D;
        case 'F':           return kybd::F;
        case 'G':           return kybd::G;
        case 'H':           return kybd::H;
        case 'J':           return kybd::J;
        case 'K':           return kybd::K;
        case 'L':           return kybd::L;
        case 'M':           return kybd::M;
        case 'W':           return kybd::W;
        case 'X':           return kybd::X;
        case 'C':           return kybd::C;
        case 'V':           return kybd::V;
        case 'B':           return kybd::B;
        case 'N':           return kybd::N;
        case '0':           return kybd::N0;
        case '1':           return kybd::N1;
        case '2':           return kybd::N2;
        case '3':           return kybd::N3;
        case '4':           return kybd::N4;
        case '5':           return kybd::N5;
        case '6':           return kybd::N6;
        case '7':           return kybd::N7;
        case '8':           return kybd::N8;
        case '9':           return kybd::N9;
    }
    return kybd::undef;
}
static inline char16_t*  utf16decode(char16_t* begin, char16_t* end, char32_t& out, char32_t repl) {
    char16_t first = *begin++;

    // If it's a surrogate pair, first convert to a single UTF-32 character
    if ((first >= 0xD800) && (first <= 0xDBFF)) {
        if (begin < end) {
            char32_t second = *begin++;
            if ((second >= 0xDC00) && (second <= 0xDFFF)) {
                // The second element is valid: convert the two elements to a UTF-32 character
                out = static_cast<char32_t>(((first - 0xD800) << 10) + (second - 0xDC00) + 0x0010000);
            }
            else
                // Invalid character
                out = repl;
        }
        else {
            // Invalid character
            begin = end;
            out = repl;
        }
    }
    else
        // We can make a direct copy
        out = first;
    return begin;
}
static inline void utf16to32(char16_t* begin, char16_t* end, char32_t* out) {
    while (begin < end) {
        char32_t codepoint;
        begin = utf16decode(begin, end, codepoint, 0);
        *out++ = codepoint;
    }
}
} // namespace anoymous

namespace crs {
    namespace plat {

        win32_window::win32_window(const wndconfig& cfg) :
        m_inst              (GetModuleHandle(nullptr)),
        m_wnd_style         (0),
        m_style             (cfg.style),
        m_name              (cfg.title),
        m_cur               (nullptr),
        m_ico               (nullptr),
        m_last_size         ({cfg.width, cfg.height }),
        m_is_full_screen    ((cfg.style & styles::fullscreen) != 0),
        m_is_cursor_grabbed ((cfg.style & styles::fullscreen) != 0),
        m_is_resizing       (false)  
        {
            Instance_count++;

            m_ico = cfg.icon.pixels   != nullptr ? make_ico(cfg.icon)   : nullptr;
            m_cur = cfg.cursor.pixels != nullptr ? make_ico(cfg.cursor) : nullptr;

            WNDCLASSEXA windowclass{};
            windowclass.cbSize        = sizeof(windowclass);
            windowclass.style         = CS_OWNDC;
            windowclass.lpfnWndProc   = m_HandleMsgSetup;
            windowclass.cbClsExtra    = 0;
            windowclass.cbWndExtra    = 0;
            windowclass.hInstance     = m_inst;
            windowclass.hIcon         = m_ico;
            windowclass.hCursor       = m_cur;
            windowclass.hbrBackground = nullptr;
            windowclass.lpszMenuName  = nullptr;
            windowclass.lpszClassName = Class_name;
            windowclass.hIconSm       = m_ico;
            RegisterClassExA(&windowclass);

            // 只针对客户区的长和宽
            RECT wr{};
            wr.left   = 100;
            wr.right  = cfg.width + wr.left;
            wr.top    = 100;
            wr.bottom = cfg.height + wr.top;

            if (AdjustWindowRect(&wr, 13238272L, 0) == 0)
                throw CRS_EXCEPTION("Can't adjust window rect!");

            // 根据样式类型来选择窗口样式
            m_wnd_style = WS_VISIBLE;
            if (m_style == styles::none) m_wnd_style |= WS_POPUP;
            else {
                if (m_style & styles::titlebar)    m_wnd_style |= WS_CAPTION | WS_MINIMIZEBOX;
                if (m_style & styles::resize)      m_wnd_style |= WS_THICKFRAME | WS_MAXIMIZEBOX;
                if (m_style & styles::close)       m_wnd_style |= WS_SYSMENU;
            }

            m_handle = CreateWindowExA(0, Class_name,
                m_name.data(), m_wnd_style, // style.
                CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
                nullptr, nullptr, m_inst, this
            );

            if (m_handle == nullptr)
                throw CRS_EXCEPTION("Window creation failed!");

            if (m_is_full_screen) m_to_fullscreen();

            // 只有这一行加上窗口才可以正常显示标题
            SetWindowTextA(m_handle, m_name.data());

            if (m_cur == nullptr) {
                m_cur = LoadCursorA(nullptr, MAKEINTRESOURCEA(32512)); // To system default icon => arrow.
                SetCursor(m_cur);
            }

        }
        void win32_window::show(void) {
            ShowWindow(m_handle, 10);
            UpdateWindow(m_handle);
        }
        void win32_window::set_icon(const wndimage& img) {
            m_ico = ::make_ico(img);

            if (!m_ico) {
                throw CRS_EXCEPTION("Can't create icon!");
            }
            //Change both icons to the same icon handle.
            SendMessageA(m_handle, WM_SETICON, ICON_SMALL, (LPARAM)m_ico);
            SendMessageA(m_handle, WM_SETICON, ICON_BIG, (LPARAM)m_ico);

            //This will ensure that the application icon gets changed too.
            SendMessageA(GetWindow(m_handle, GW_OWNER), WM_SETICON, ICON_SMALL, (LPARAM)m_ico);
            SendMessageA(GetWindow(m_handle, GW_OWNER), WM_SETICON, ICON_BIG, (LPARAM)m_ico);
        }
        void win32_window::set_cursor(const wndimage& img) {
            m_cur = ::make_ico(img);
            if (m_cur) {
                ::SetCursor(m_cur);
                return;
            }
            throw CRS_EXCEPTION("Can't create cursor!");
        }
        void win32_window::title(const char* name) {
            m_name = name;
            if (SetWindowTextA(m_handle, m_name.data()) == 0)
                throw CRS_EXCEPTION("Can't set title!");
        }
        const char* win32_window::title() const {
            return m_name.data();
        }
        void win32_window::style(styles style) {
            m_style          = style;
            m_wnd_style      = 0;
            m_is_full_screen = (m_style & styles::fullscreen) != 0;
            m_is_cursor_grabbed = m_is_full_screen;
            m_to_fullscreen();
        }
        styles win32_window::style() const {
            return m_style;
        }
        void win32_window::auto_repeat(bool s) {
            m_is_auto_repeated = s;
        }
        bool win32_window::auto_repeat() const {
            return m_is_auto_repeated;
        }
        _Detail::pairsz win32_window::size() const {
            return m_last_size;
        }
        void win32_window::size(_Detail::pairsz sz) {
            RECT rectangle = { 0, 0, static_cast<long>(sz.first), static_cast<long>(sz.second) };
            AdjustWindowRect(&rectangle, GetWindowLong(m_handle, GWL_STYLE), false);
            int width = rectangle.right - rectangle.left;
            int height = rectangle.bottom - rectangle.top;

            SetWindowPos(m_handle, nullptr, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
        }
        void win32_window::m_set_tracking(bool track) {
            TRACKMOUSEEVENT msEvent{};
            msEvent.cbSize       = sizeof(TRACKMOUSEEVENT);
            msEvent.dwFlags      = track ? TME_LEAVE : TME_CANCEL;
            msEvent.hwndTrack    = m_handle;
            msEvent.dwHoverTime  = HOVER_DEFAULT;
            TrackMouseEvent(&msEvent);
        }
        void win32_window::m_to_fullscreen() {
            RECT wr{};
            if (m_is_full_screen) {
                wr.left   = 100;
                wr.right  = GetSystemMetrics(SM_CXSCREEN) + wr.left;
                wr.top    = 100;
                wr.bottom = GetSystemMetrics(SM_CYSCREEN) + wr.top;

                SetWindowLongA(m_handle, GWL_STYLE, WS_BORDER);
                SetWindowPos(m_handle, HWND_TOPMOST, 0, 0, wr.right, wr.bottom, SWP_SHOWWINDOW);
                return;
            }
            GetWindowRect(m_handle, &wr);
            SetWindowLongA(m_handle, GWL_STYLE, 13565952L);
            SetWindowPos(m_handle, HWND_NOTOPMOST, 0, 0,
                wr.right, wr.bottom, SWP_SHOWWINDOW);

            return;
        }
        void win32_window::cursor_display(bool shouldDisplay) {
            m_is_cursor_display = shouldDisplay;
            ShowCursor((BOOL)m_is_cursor_display);
        }
        bool win32_window::cursor_display(void) const {
            return m_is_cursor_display;
        }
        bool win32_window::close(void) const {
            return m_is_close;
        }
        void win32_window::close(bool isClose) {
            m_is_close = isClose == true ? WM_CLOSE : WM_NULL;
            SendMessageA(m_handle, m_is_close, 0, 0);
        }
        win32_window::~win32_window() {
            //Change both icons to the same icon handle.
            SendMessageA(m_handle, WM_SETICON, ICON_SMALL, 0);
            SendMessageA(m_handle, WM_SETICON, ICON_BIG, 0);

            //This will ensure that the application icon gets changed too.
            SendMessageA(GetWindow(m_handle, GW_OWNER), WM_SETICON, ICON_SMALL, 0);
            SendMessageA(GetWindow(m_handle, GW_OWNER), WM_SETICON, ICON_BIG, 0);

            if (m_handle != nullptr) {
                DestroyWindow(m_handle);
                Instance_count--;
            }
        }
        void win32_window::m_grab_cursor(bool grabbed) {
            if (grabbed) {
                RECT rect;
                GetClientRect(m_handle, &rect);
                MapWindowPoints(m_handle, nullptr, reinterpret_cast<LPPOINT>(&rect), 2);
                ClipCursor(&rect);
            }
            else ClipCursor(nullptr);
        }
        LRESULT win32_window::m_HandleMsgSetup(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept {
            if (msg == WM_NCCREATE) {
                const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lp);
                win32_window* const pWnd = static_cast<win32_window*>(pCreate->lpCreateParams);
                SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
                SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&win32_window::m_HandleMsgThunk));
                return pWnd->m_handle_msg(hwnd, msg, wp, lp);
            }
            return DefWindowProc(hwnd, msg, wp, lp);
        }
        LRESULT win32_window::m_HandleMsgThunk(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept {
            win32_window* const pWnd = reinterpret_cast<win32_window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
            return pWnd->m_handle_msg(hwnd, msg, wp, lp);
        }
        void win32_window::m_process_events() {
            MSG message;
            while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE)) {
                TranslateMessage(&message);
                DispatchMessageA(&message);
            }
        }
        // Message handle defination.
        // Will be changing oftenly.
        LRESULT win32_window::m_handle_msg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

            if (m_handle == nullptr) return 0;

            switch (message) {
                case WM_DESTROY: {
                    //! TODO: 资源清理函数
                    //this->cleanup()
                    this->close();
                    break;
                }
                case WM_SETCURSOR: {
                    if (LOWORD(lParam) == HTCLIENT)
                        SetCursor(m_cur);

                    break;
                }
                case WM_CLOSE: {
                    wevent E{};
                    E.type = wevent::closed;
                    push_event(E);
                    break;
                }
                case WM_SIZE:
                {
                    if (wParam != SIZE_MINIMIZED && !m_is_resizing && m_last_size != size()) {
                        m_last_size = size();

                        wevent E{};
                        E.type = wevent::resized;
                        E.size.width =  m_last_size.first;
                        E.size.height = m_last_size.second;
                        push_event(E);

                        m_grab_cursor(m_is_cursor_grabbed);
                    }
                    break;
                }
                case WM_ENTERSIZEMOVE: {
                    m_is_resizing = true;
                    m_grab_cursor(false);
                    break;
                }
                case WM_EXITSIZEMOVE: {
                    m_is_resizing = false;

                    if (m_last_size != size()) {
                        m_last_size =  size();

                        wevent E{};
                        E.type = wevent::resized;
                        E.size.width  = m_last_size.first;
                        E.size.height = m_last_size.second;
                        push_event(E);
                    }

                    m_grab_cursor(m_is_cursor_grabbed);
                    break;
                }
                // 系统要求的最大最小信息
                case WM_GETMINMAXINFO: {
                    MINMAXINFO* info = reinterpret_cast<MINMAXINFO*>(lParam);
                    info->ptMaxTrackSize.x = 50000;
                    info->ptMaxTrackSize.y = 50000;
                    break;
                }
                case WM_SETFOCUS: {
                    m_grab_cursor(m_is_cursor_grabbed);

                    wevent E;
                    E.type = wevent::gainedfocus;
                    push_event(E);
                    break;
                }
                case WM_KILLFOCUS: {
                    m_grab_cursor(false);

                    wevent E{};
                    E.type = wevent::lostfocus;
                    push_event(E);
                    break;
                }
                case WM_CHAR:
                {
                    if (m_is_auto_repeated || ((lParam & (1 << 30)) == 0)) {
                        // Get the code of the typed character
                        char32_t character = static_cast<char32_t>(wParam);

                        // Check if it is the first part of a surrogate pair, or a regular character
                        if ((character >= 0xD800) && (character <= 0xDBFF)) {
                            // First part of a surrogate pair: store it and wait for the second one
                            m_surrogate = static_cast<char16_t>(character);
                        }
                        else {
                            // Check if it is the second part of a surrogate pair, or a regular character
                            if ((character >= 0xDC00) && (character <= 0xDFFF)) {
                                // Convert the UTF-16 surrogate pair to a single UTF-32 value
                                char16_t utf16[2] = { m_surrogate, static_cast<char16_t>(character) };
                                utf16to32(utf16, utf16 + 2, &character);
                                m_surrogate = 0;
                            }

                            // Send a TextEntered E
                            wevent E{};
                            E.type = wevent::txtentered;
                            E.text.unicode = character;
                            push_event(E);
                        }
                    }
                    break;
                }
                case WM_KEYDOWN:
                case WM_SYSKEYDOWN: {
                    if (m_is_auto_repeated || ((HIWORD(lParam) & KF_REPEAT) == 0)) {
                        wevent E{};
                        E.type = wevent::kyprsd;
                        E.key.alt    = HIWORD(GetKeyState(VK_MENU)) != 0;
                        E.key.ctrl   = HIWORD(GetKeyState(VK_CONTROL)) != 0;
                        E.key.shift  = HIWORD(GetKeyState(VK_SHIFT)) != 0;
                        E.key.super  = HIWORD(GetKeyState(VK_LWIN)) || HIWORD(GetKeyState(VK_RWIN));
                        E.key.code   = trans_virtual_kc(wParam, lParam);
                        push_event(E);
                    }
                    break;
                }
                case WM_KEYUP:
                case WM_SYSKEYUP: {
                    wevent E{};
                    E.type       = wevent::kyrlsd;
                    E.key.alt    = HIWORD(GetKeyState(VK_MENU)) != 0;
                    E.key.ctrl   = HIWORD(GetKeyState(VK_CONTROL)) != 0;
                    E.key.shift  = HIWORD(GetKeyState(VK_SHIFT)) != 0;
                    E.key.super  = HIWORD(GetKeyState(VK_LWIN)) || HIWORD(GetKeyState(VK_RWIN));
                    E.key.code = trans_virtual_kc(wParam, lParam);
                    push_event(E);
                    break;
                }
                case WM_MOUSEWHEEL: {
                    POINT position {
                        static_cast<std::uint16_t>(LOWORD(lParam)),
                        static_cast<std::uint16_t>(HIWORD(lParam))
                    };
                    ScreenToClient(m_handle, &position);

                    std::uint16_t delta = static_cast<std::uint16_t>(HIWORD(wParam));

                    wevent E{};

                    E.type = wevent::mswhumvd;
                    E.mswhu.delta = delta / 120.f;
                    E.mswhu.x     = position.x;
                    E.mswhu.y     = position.y;
                    push_event(E);

                    E.type = wevent::mswhumvd;
                    E.mswhu.wheel = mouz::whu::vt;
                    E.mswhu.delta = static_cast<float>(delta) / 120.f;
                    E.mswhu.x     = position.x;
                    E.mswhu.y     = position.y;
                    push_event(E);
                    break;
                }
                case WM_MOUSEHWHEEL: {
                    // 将屏幕坐标转变为窗口坐标
                    POINT position{
                        static_cast<std::int16_t>(LOWORD(lParam)),
                        static_cast<std::int16_t>(HIWORD(lParam))
                    };
                    ScreenToClient(m_handle, &position);

                    std::int16_t delta = static_cast<std::int16_t>(HIWORD(wParam));

                    wevent E{};
                    E.type = wevent::mswhumvd;
                    E.mswhu.wheel = mouz::whu::hz;
                    E.mswhu.delta = -static_cast<float>(delta) / 120.f;
                    E.mswhu.x     = position.x;
                    E.mswhu.y     = position.y;
                    push_event(E);
                    break;
                }
                case WM_LBUTTONDOWN:{
                    wevent E{};
                    E.type = wevent::msbtnprsd;
                    E.msbtn.btn = mouz::left;
                    E.msbtn.x   = static_cast<std::int16_t>(LOWORD(lParam));
                    E.msbtn.y   = static_cast<std::int16_t>(HIWORD(lParam));
                    push_event(E);
                    break;
                }
                case WM_LBUTTONUP: {
                    wevent E;
                    E.type      = wevent::msbtnrlsd;
                    E.msbtn.btn = mouz::left;
                    E.msbtn.x   = static_cast<std::int16_t>(LOWORD(lParam));
                    E.msbtn.y   = static_cast<std::int16_t>(HIWORD(lParam));
                    push_event(E);
                    break;
                }
                case WM_RBUTTONDOWN: {
                    wevent E{};
                    E.type = wevent::msbtnprsd;
                    E.msbtn.btn = mouz::right;
                    E.msbtn.x = static_cast<std::int16_t>(LOWORD(lParam));
                    E.msbtn.y = static_cast<std::int16_t>(HIWORD(lParam));
                    push_event(E);
                    break;
                }
                case WM_RBUTTONUP: {
                    wevent E{};
                    E.type = wevent::msbtnrlsd;
                    E.msbtn.btn = mouz::right;
                    E.msbtn.x = static_cast<std::int16_t>(LOWORD(lParam));
                    E.msbtn.y = static_cast<std::int16_t>(HIWORD(lParam));
                    push_event(E);
                    break;
                }
                case WM_MBUTTONDOWN:
                {
                    wevent E{};
                    E.type = wevent::msbtnprsd;
                    E.msbtn.btn = mouz::middle;
                    E.msbtn.x = static_cast<std::int16_t>(LOWORD(lParam));
                    E.msbtn.y = static_cast<std::int16_t>(HIWORD(lParam));
                    push_event(E);
                    break;
                }
                case WM_MBUTTONUP: {
                    wevent E{};
                    E.type = wevent::msbtnrlsd;
                    E.msbtn.btn = mouz::middle;
                    E.msbtn.x = static_cast<std::int16_t>(LOWORD(lParam));
                    E.msbtn.y = static_cast<std::int16_t>(HIWORD(lParam));
                    push_event(E);
                    break;
                }
                case WM_XBUTTONDOWN: {
                    wevent E{};
                    E.type = wevent::msbtnprsd;
                    E.msbtn.btn = HIWORD(wParam) == XBUTTON1 ? mouz::xbtn1 : mouz::xbtn2;
                    E.msbtn.x = static_cast<std::int16_t>(LOWORD(lParam));
                    E.msbtn.y = static_cast<std::int16_t>(HIWORD(lParam));
                    push_event(E);
                    break;
                }
                case WM_XBUTTONUP: {
                    wevent E{};
                    E.type = wevent::msbtnrlsd;
                    E.msbtn.btn = HIWORD(wParam) == XBUTTON1 ? mouz::xbtn1 : mouz::xbtn2;
                    E.msbtn.x = static_cast<std::int16_t>(LOWORD(lParam));
                    E.msbtn.y = static_cast<std::int16_t>(HIWORD(lParam));
                    push_event(E);
                    break;
                }
                case WM_MOUSELEAVE: {
                    if (m_is_msinside) {
                        m_is_msinside = false;

                        wevent E{};
                        E.type = wevent::msleft;
                        push_event(E);
                    }
                    break;
                }

                case WM_MOUSEMOVE: {
                    // 解析鼠标的位置
                    int x = static_cast<std::int16_t>(LOWORD(lParam));
                    int y = static_cast<std::int16_t>(HIWORD(lParam));

                    // 获得客户区大小
                    RECT area;
                    GetClientRect(m_handle, &area);

                    // 捕获鼠标，以防用户想要将鼠标拖到屏幕外
                    if ((wParam & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON | MK_XBUTTON1 | MK_XBUTTON2)) == 0) {
                        if (GetCapture() == m_handle)
                            ReleaseCapture();
                    }
                    else if (GetCapture() != m_handle) {
                        SetCapture(m_handle);
                    }
                    // 如果鼠标离开了客户区
                    if ((x < area.left) || (x > area.right) || (y < area.top) || (y > area.bottom))
                    {
                        // 如果它以前是在里面的就不去管它
                        if (m_is_msinside) {
                            m_is_msinside = false;

                            // 不再关注离开窗口的鼠标
                            m_set_tracking(false);

                            wevent E{};
                            E.type = wevent::msleft;
                            push_event(E);
                        }
                    }
                    else {
                        // and vice-versa
                        if (!m_is_msinside) {

                            m_is_msinside = true;
                            m_set_tracking(true);

                            wevent E{};
                            E.type = wevent::msentered;
                            push_event(E);
                        }
                    }
                    wevent E{};
                    E.type = wevent::msmvd;
                    E.msmv.x = x;
                    E.msmv.y = y;
                    push_event(E);
                    break;
                }
                //!TODO: Joystick implementation
                //case WM_DEVICECHANGE:
                //{
                //    // Some sort of device change has happened, update joystick connections
                //    if ((wParam == DBT_DEVICEARRIVAL) || (wParam == DBT_DEVICEREMOVECOMPLETE))
                //    {
                //        // Some sort of device change has happened, update joystick connections if it is a device interface
                //        DEV_BROADCAST_HDR* deviceBroadcastHeader = reinterpret_cast<DEV_BROADCAST_HDR*>(lParam);

                //        if (deviceBroadcastHeader && (deviceBroadcastHeader->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE))
                //            JoystickImpl::updateConnections();
                //    }

                //    break;
                //}
            }
            return DefWindowProc(hwnd, message, wParam, lParam);
        }
        void* win32_window::native_handle(void) {
            return m_handle;
        }
    }
} // namespace crs.