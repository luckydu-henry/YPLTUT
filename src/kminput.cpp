#include <pltut/kminput.h>
#include <tuple>

namespace yan
{
    kminput::kminput()
        :_M_first_queue(), _M_is_auto_repeat(false),
         _M_but_queue(),   _M_is_inwindow(false), _M_wheel_delta(0) {}


    template<>
    const scancode_e kminput::get_event<scancode_e>() {

        plat_scan_trans::trans_type oldest_msg = !_M_first_queue.empty() ? _M_first_queue.front() : 0;

        if (!_M_first_queue.empty())
            _M_first_queue.pop();

        return static_cast<scancode_e>(oldest_msg);
    }

    template<>
    const button_e  kminput::get_event<button_e>() {
        auto oldest_msg = !_M_but_queue.empty() ? _M_but_queue.front() : button_e::null;
        if (!_M_but_queue.empty())
            _M_but_queue.pop();
        return oldest_msg;
    }

    template<>
    const mouse_e   kminput::get_event<mouse_e>() {
        auto oldest_msg = !_M_mouse_queue.empty() ? _M_mouse_queue.front() : mouse_e::null;
        if (!_M_mouse_queue.empty())
            _M_mouse_queue.pop();

        return oldest_msg;
    }

    const bool kminput::get_mod(mod_e _Mod) {
        return _M_mod_state[static_cast<plat_scan_trans::trans_type>(_Mod) - 0x9f];
    }

    const std::tuple<int, int> kminput::get_mpos(void) const {
        return std::make_tuple(_M_position.first, _M_position.second);
    }
    void kminput::set_autorepeat(bool _Xx) {
        _M_is_auto_repeat = _Xx;
    }
    void kminput::_M_on_button(button_e _But) {
        _M_but_queue.push(_But);
    }
    void kminput::_M_on_mouse(mouse_e _Which, std::pair<int, int> _Pos) {
        // A little switch to decide particular use of diffrent event.
        switch (_Which) {
            default: break;
            case yan::mouse_e::move: _M_position = _Pos; break;
            case yan::mouse_e::enter: _M_is_inwindow = true; break;
            case yan::mouse_e::leave: _M_is_inwindow = false; break;
        }
        _M_mouse_queue.push(_Which);
    }
    void kminput::_M_on_key(plat_scan_trans::trans_type _Which) {
        _M_first_queue.push(_Which);
    }
}