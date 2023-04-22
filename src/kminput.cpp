#include <pltut/kminput.h>
#include <tuple>

namespace yan
{
    kminput::kminput()
        :_M_first_queue(1u), _M_is_auto_repeat(false),
         _M_but_queue(1u),   _M_is_inwindow(false), _M_wheel_delta(0) {}

    const kminput::event_t kminput::get_button(button_e _But) const {
        auto idx = static_cast<plat_scan_trans::trans_type>(_But);

        if (_M_but_state[idx] == _G_press && _M_but_queue.back() == _But)
            return { true, false };
        if (_M_but_state[idx] == _G_release && _M_but_queue.back() == _But)
            return { false, true };

        return {};
    }
    const bool kminput::get_mouse(mouse_e _Which) const {
        return _M_mouse_state.back() == _Which ? true : false;
    }
    const std::tuple<int, int> kminput::get_mpos(void) const {
        return std::make_tuple(_M_position.first, _M_position.second);
    }
    const kminput::event_t kminput::get_key(scancode_e _Scan) const {
        auto _Key = plat_scan_trans::scan_to_key(_Scan);

        if (_Key == plat_scan_trans::scan_to_key(scancode_e::escape))
            return _M_escape_event;

        auto _KC = static_cast<plat_scan_trans::trans_type>(_Key);

        if (_M_first_state[_KC] == _G_press && _M_first_queue.back() == _KC)
            return { true, false };
        if (_M_first_state[_KC] == _G_release && _M_first_queue.back() == _KC)
            return { false, true };
        return { };
    }
    const bool kminput::get_mod(mod_e _Which) const {
        return _M_mod_state[static_cast<plat_scan_trans::trans_type>(_Which) - 0x9f];
    }
    void kminput::set_autorepeat(bool _Xx) {
        _M_is_auto_repeat = _Xx;
    }
    void kminput::flush(void) {
        _M_first_queue.clear();
        _M_but_queue.clear();
    }
    void kminput::_M_on_button(bool _PorR, button_e _But) {
        _M_but_state[static_cast<plat_scan_trans::trans_type>(_But)] = _PorR;
        _M_but_queue.push_back(_But);
    }
    void kminput::_M_on_mouse(mouse_e _Which, std::pair<int, int> _Pos) {
        // A little switch to decide particular use of diffrent event.
        switch (_Which) {
            default: break;
            case yan::mouse_e::move: _M_position = _Pos; break;
            case yan::mouse_e::enter: _M_is_inwindow = true; break;
            case yan::mouse_e::leave: _M_is_inwindow = false; break;
        }
        _M_mouse_state.push_back(_Which);
    }
    void kminput::_M_on_key(bool _PorR, plat_scan_trans::trans_type _Which) {
        _M_first_state[_Which] = _PorR;
        _M_first_queue.push_back(_Which);
    }
    kminput::~kminput() {
        _M_first_queue.clear();
        _M_first_state.reset();
        _M_but_queue.clear();
    }
}