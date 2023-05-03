#ifndef _YAN_WINDOW_H_
#define _YAN_WINDOW_H_
#include <pltut/kminput.h>
namespace yan {

    struct wndconfig {
        int           width, height;
        const char*   title;
        long long     style;
        bool          is_fullscreen;
        struct {
            unsigned char*  pixels;
            int      width, height;
            int      channels;
        } icon, cursor;
    };

    // I don't have enum for this, just use system style your self.
    using window_style = long long;

    namespace window_styles {
        constexpr window_style win32_overlapped       = 0x00000000L;
        constexpr window_style win32_popup            = 0x80000000L;
        constexpr window_style win32_child            = 0x40000000L;
        constexpr window_style win32_minimize         = 0x20000000L;
        constexpr window_style win32_visible          = 0x10000000L;
        constexpr window_style win32_disabled         = 0x08000000L;
        constexpr window_style win32_clipsiblings     = 0x04000000L;
        constexpr window_style win32_clipchildren     = 0x02000000L;
        constexpr window_style win32_maximize         = 0x01000000L;
        constexpr window_style win32_caption          = 0x00C00000L;
        constexpr window_style win32_border           = 0x00800000L;
        constexpr window_style win32_dlgframe         = 0x00400000L;
        constexpr window_style win32_vscroll          = 0x00200000L;
        constexpr window_style win32_hscroll          = 0x00100000L;
        constexpr window_style win32_sysmenu          = 0x00080000L;
        constexpr window_style win32_thickframe       = 0x00040000L;
        constexpr window_style win32_group            = 0x00020000L;
        constexpr window_style win32_tabstop          = 0x00010000L;
        constexpr window_style win32_minimizebox      = 0x00020000L;
        constexpr window_style win32_maximizebox      = 0x00010000L;
    }


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
        void                   style(window_style _Style);
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