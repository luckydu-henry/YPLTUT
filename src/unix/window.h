#ifndef _OGT_LINUX_WINDOW_H_
#define _OGT_LINUX_WINDOW_H_

#include <odk/windowapi/kminput.h>
#include <odk/windowapi/window.h>
#include <odk/windowapi/except.h>
#include "header.h"

#include <utility>

namespace odk {

    class x11_exception : public except {
    public:
        x11_exception(std::source_location _Loc, std::string_view _ErrStr) noexcept;

        const char* what() const noexcept override;

        ~x11_exception() = default;
    };

    namespace platform { 
        class x11_window {
            x11_window(const x11_window&) = delete;
            x11_window& operator=(const x11_window&) = delete;
        public:
            x11_window(const wndconfig&);
    
            void         show(void)                     ;
            void         poll_events(void)              ;
            void         set_title(const char* _Title)  ;
    
            void         cursor_display(bool _IsDisplay);
            bool         cursor_display(void) const     ;
            void         full_screen(bool _IsFullScreen);
            bool         full_screen(void) const        ;
            void         close(bool)                    ;
            bool         close(void) const              ;
    
            std::size_t         get_size(screen_prop _Enum);
            void*               native_handle(void)        ;
            kminput&            kmhandle();

            kminput km_handle;

            static const std::uint32_t get_screenprop(screen_prop _Enum);
            ~x11_window();
        private:
            std::pair<uint32_t, uint32_t> _M_wnd_size;
    
            bool _M_is_should_close;
            bool _M_is_fullscrenn;
            bool _M_is_cursor_display;
    
            x11_hwnd _M_wnd;
        };
    }
} // namespace odk
#define X11_EXCEPT(ErrStr) odk::x11_exception(std::source_location::current(), ErrStr)
#endif //!_OGT_LINUX_WINDOW_H_
