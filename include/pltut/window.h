#ifndef _YAN_WINDOW_H_
#define _YAN_WINDOW_H_
#include <pltut/kminput.h>
namespace yan {

    struct wndconfig {
        int           width, height;
        const char*   title;
        bool          is_fullscreen;
        struct {
            unsigned char*  pixels;
            int      width, height;
            int      channels;
        } icon, cursor;
    };

    enum screen_prop : unsigned char {
        scrwidth = 1, scrheight 
    };

    template <class _Sub_window>
    class YAN_API basic_window {
        _Sub_window* _M_inst;
    public:

        basic_window(const wndconfig&);

        // current not support copy and move.
        basic_window(const basic_window<_Sub_window>&) = delete;
        basic_window(basic_window<_Sub_window>&&)      = delete;

        // basic window framework
        void                   show();
        void                   poll_events();
        void                   close(bool _IsShouldClose);
        constexpr bool         close() const noexcept;
        void*                  native_handle() const noexcept;
        kminput&               kmhandle() noexcept;
        std::size_t            get_size(screen_prop _Enum) const noexcept;

        // extended window framework
        void                   full_screen(bool _IsFullScreen);
        constexpr bool         full_screen() const noexcept;
        void                   cursor_display(bool _ShouldDisplay);
        constexpr bool         cursor_display() const noexcept;

        void                   set_icon  (unsigned char* _Pixels, int _width, int _height, int _Channel);
        void                   set_cursor(unsigned char* _Pixels, int _width, int _height, int _Channel);

        // utility
        static const std::uint32_t get_screenprop(screen_prop _Enum);

        ~basic_window();
    };

    using window = basic_window<platform::plat_window>;

}//! namespace yan.

#endif //!_YAN_WINDOW_H_