#ifndef _OMI_INPUT_H_
#define _OMI_INPUT_H_

#include <vector>
#include <bitset>
#include <climits>
#include "input_query.h"

namespace yan {

    constexpr bool _G_press = true;
    constexpr bool _G_release = true;

    class YAN_API kminput {
        friend platform::plat_window;

        kminput();
        ~kminput();
    public:
        struct event_t {
            bool is_pressed = false, is_released = false; // Two key state detach.
        };

        const event_t                get_button(button_e _But) const;
        const event_t                get_key(scancode_e _Scan) const;

        const bool                   get_mouse(mouse_e _Which) const;
        const bool                   get_mod(mod_e _Which) const;
        const std::tuple<int, int>   get_mpos(void) const;

        void                         set_autorepeat(bool);
        void                         flush(void);

    private:
        // for friend class usage.
        void             _M_on_button(bool _PorR, button_e _But);
        void             _M_on_mouse(mouse_e _Which, std::pair<int, int> _Pos = { 0,0 });
        void             _M_on_key(bool _PorR, plat_scan_trans::trans_type _Which);
    private:
        // esc must be specialized.
        event_t _M_escape_event;
        // only win32 has this.
        int     _M_wheel_delta;

        // For mouse.
        bool           _M_is_inwindow;
        bool           _M_is_auto_repeat;

        // For button state
        // It's very similar to key inputs.
        std::bitset<5u>         _M_but_state;
        std::vector<button_e>   _M_but_queue;
        // State check for mouse events.
        std::vector<mouse_e>    _M_mouse_state;

        // For the mouse position.
        // First one is x-coord and the second one is y-coord.
        std::pair<int, int>        _M_position;

        // clear state is this one.
        std::bitset<plat_scan_trans::max_queue_size>    _M_first_state;             // Release or Press.
        std::vector<unsigned char>                      _M_first_queue;             // Which key.
        std::bitset<7u>                                 _M_mod_state;
    };

}

#endif //! _OGT_IMPL_INPUT_H_