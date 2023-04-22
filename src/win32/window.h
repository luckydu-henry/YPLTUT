#ifndef _WIN32_WINDOW_H_
#define _WIN32_WINDOW_H_

#include <pltut/except.h>
#include <pltut/window.h>
#include <Windows.h>

namespace yan {

    namespace platform {
        class win32_exception : public except {
            HRESULT _M_result;
        public:
            win32_exception(std::source_location Loc, HRESULT hr) noexcept;

            const char* what()     const noexcept override;
            std::string_view     err_type() const noexcept override;
            void                 trans_hresult();
        };

        class YAN_API win32_window {
            win32_window(const win32_window&) = delete;
            win32_window(win32_window&&) = delete;
            win32_window& operator=(const win32_window&) = delete;
        public:

            win32_window(const wndconfig&);

            void         set_icon  (unsigned char* _Pixels, int _width, int _height, int _Channel);
            void         set_cursor(unsigned char* _Pixels, int _width, int _height, int _Channel);
            void         show(void);
            void         set_title(const char* _Name);
            void         full_screen(bool _IsFullScreen);
            bool         full_screen(void) const;
            void         cursor_display(bool _ShouldDisplay);
            bool         cursor_display(void) const;
            void         close(bool _IsShouldClose);
            bool         close(void) const;
            void*        native_handle(void);
            void         poll_events(void);
            kminput&     kmhandle();

            std::size_t  get_size(screen_prop _Enum);

            static const std::uint32_t get_screenprop(screen_prop _Enum);

            ~win32_window();

            kminput  km_handle;

        private:
            static LRESULT CALLBACK _M_HandleMsgSetup(HWND, UINT, WPARAM, LPARAM) noexcept;
            static LRESULT CALLBACK _M_HandleMsgThunk(HWND, UINT, WPARAM, LPARAM) noexcept;
            LRESULT _M_HandleMsg(HWND, UINT, WPARAM, LPARAM);

            // attribute varibiles.
            std::pair<int, int> _M_wndsize;
            std::string_view    _M_name;
            HCURSOR             _M_cur;
            HINSTANCE           _M_inst;
            HWND                _M_handle;

            // window counts.
            static uint8_t _S_inst_count;

            // state check varibiles.
            bool _M_is_cursor_display = false;
            bool _M_is_full_screen = false;
            bool _M_shoule_close = false;

        };
    }
} // namespace yan;
#define WIN32_HWND_EXCEPT(hr) win32_exception(std::source_location::current(), hr)
#define WIN32_HWND_LASTERR()  win32_exception(std::source_location::current(), GetLastError())
#endif //! _WIN32_WINDOW_H_
