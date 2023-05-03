#ifndef _OMI_INPUT_H_
#define _OMI_INPUT_H_

#include <bitset>
#include <climits>
#include <queue>
#include "input_query.h"

namespace yan {

    constexpr bool _G_press = true;
    constexpr bool _G_release = true;

    class YAN_API kminput {
        friend platform::plat_window;

        kminput();
        ~kminput() = default;
    public:

        template <typename _EventT>
        requires std::is_enum_v<_EventT>
        const _EventT                get_event();

        template <>
        const scancode_e             get_event();
        template <>
        const button_e               get_event();
        template <>
        const mouse_e                get_event();

        // This is the only one could not use get_event.
        const bool                   get_mod(mod_e _Mod);
        const std::tuple<int, int>   get_mpos(void) const;

        void                         set_autorepeat(bool);
        //void                         flush(void);

    private:
        // for friend class usage.
        void                         _M_on_button(button_e _But);
        void                         _M_on_mouse(mouse_e _Which, std::pair<int, int> _Pos = { 0,0 });
        void                         _M_on_key(plat_scan_trans::trans_type _Which);
    private:
        // only win32 has this.
        int     _M_wheel_delta;

        // For mouse.
        bool                                            _M_is_inwindow;
        bool                                            _M_is_auto_repeat;
        // For button state
        // It's very similar to key inputs.
        std::queue<button_e>                            _M_but_queue;
        // State check for mouse events.
        std::queue<mouse_e>                             _M_mouse_queue;
        // For the mouse position.
        // First one is x-coord and the second one is y-coord.
        std::pair<int, int>                             _M_position;
        // clear state is this one.
        std::queue<unsigned char>                       _M_first_queue;             // Which key.
        std::bitset<7u>                                 _M_mod_state;
    };
}

#endif //! _OGT_IMPL_INPUT_H_