#include <pltut/window.h>
#include <iostream>

#if   IS_PLATFORM_WIN32
#include "win32/window.h"
#elif IS_PLATFORM_LINUX
#include "linux/window.h"
#endif

#define EXTENDED_METHOD_OPERATION(type, check, opsuccess, str) \
constexpr bool has_method = requires(type test) { test.check; }; \
if constexpr (has_method) \
    opsuccess;\
else std::cout << str << std::endl

namespace yan {

    template class basic_window<platform::plat_window>;

    template <class _Sub_window>
    basic_window<_Sub_window>::basic_window(const wndconfig& _cfg)
        :_M_inst(new _Sub_window(_cfg)) {}

    template <class _Sub_window>
    void basic_window<_Sub_window>::show() {
        _M_inst->show();
    }
    template <class _Sub_window>
    void basic_window<_Sub_window>::poll_events() {
        _M_inst->poll_events();
    }
    template <class _Sub_window>
    void basic_window<_Sub_window>::close(bool _IsShouldClose) {
        _M_inst->close(_IsShouldClose);
    }
    template <class _Sub_window>
    constexpr bool basic_window<_Sub_window>::close() const noexcept {
        return _M_inst->close();
    }
    template <class _Sub_window>
    void* basic_window<_Sub_window>::native_handle() const noexcept {
        return _M_inst->native_handle();
    }
    template <class _Sub_window>
    std::size_t basic_window<_Sub_window>::get_size(screen_prop _Enum) const noexcept {
        return _M_inst->get_size(_Enum);
    }
    template <class _Sub_window>
    kminput& basic_window<_Sub_window>::kmhandle() noexcept {
        return _M_inst->kmhandle();
    }

    // extention methods
    template <class _Sub_window>
    void basic_window<_Sub_window>::style(window_style _Style) {
        EXTENDED_METHOD_OPERATION(
            _Sub_window, style(),
            _M_inst->style(_Style), "Style setter not supported!"
        );
    }
    template <class _Sub_window>
    void basic_window<_Sub_window>::full_screen(bool _IsFullScreen) {
        EXTENDED_METHOD_OPERATION(
            _Sub_window,
            full_screen(),
            _M_inst->full_screen(_IsFullScreen),
            "Full screen set not supported!");
    }
    template <class _Sub_window>
    constexpr bool basic_window<_Sub_window>::full_screen() const noexcept {
        EXTENDED_METHOD_OPERATION(
            _Sub_window,
            full_screen(),
            return _M_inst->full_screen(),
            "Full screen get not supported!");
        return false;
    }
    template <class _Sub_window>
    void basic_window<_Sub_window>::cursor_display(bool _ShouldDisplay) {
        EXTENDED_METHOD_OPERATION(
            _Sub_window,
            cursor_display(true),
            _M_inst->cursor_display(_ShouldDisplay),
            "cursor_display set not supported!");
    }
    template <class _Sub_window>
    constexpr bool basic_window<_Sub_window>::cursor_display() const noexcept{
        EXTENDED_METHOD_OPERATION(
            _Sub_window,
            cursor_display(),
            return _M_inst->cursor_display(),
            "cursor_display get not supported!");
        return false;
    }

    template <class _Sub_window>
    void basic_window<_Sub_window>::set_icon(unsigned char* _Pixels, int _width, int _height, int _Channel) {
        EXTENDED_METHOD_OPERATION(
            _Sub_window,
            set_icon((unsigned char*)("..."), 0, 0, 0),
            _M_inst->set_icon(_Pixels, _width, _height, _Channel),
            "Can't set icon on this platform!");
    }
    template <class _Sub_window>
    void basic_window<_Sub_window>::set_cursor(unsigned char* _Pixels, int _width, int _height, int _Channel) {
        EXTENDED_METHOD_OPERATION(
            _Sub_window,
            set_cursor((unsigned char*)("..."), 0, 0, 0),
            _M_inst->set_cursor(_Pixels, _width, _height, _Channel),
            "Can't set cursor on this platform!");
    }

    template <class _Sub_window>
    basic_window<_Sub_window>::~basic_window() {
        delete _M_inst;
    }

    // utility
    template <class _Sub_window>
    const std::uint32_t basic_window<_Sub_window>::get_screenprop(screen_prop _Enum) {
        return _Sub_window::get_screenprop(_Enum);
    }
}   
    
    
    
    
