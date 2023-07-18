#include <plat/window.hpp>
#include <iostream>

#if   CRS_ISOS_WIN32
#include "win32/window.h"
#elif CRS_ISOS_UNIX
#include "linux/window.h"
#endif

namespace crs {
    namespace plat {

        template class basic_window<plat_window>;

        template <class WinType>
        basic_window<WinType>::basic_window(const wndconfig& _cfg)
            :m_inst(new WinType(_cfg)) {}

        template <class WinType>
        void basic_window<WinType>::show() {
            m_inst->show();
        }
        template <class WinType>
        bool basic_window<WinType>::poll_event(wevent& E) {
            if (m_inst && m_inst->pop_event(E, false)) {
                return true;
            }
            return false;
        }
        template <class WinType>
        void basic_window<WinType>::close(bool _IsShouldClose) {
            m_inst->close(_IsShouldClose);
        }
        template <class WinType>
        constexpr bool basic_window<WinType>::close() const noexcept {
            return m_inst->close();
        }
        template <class WinType>
        void* basic_window<WinType>::native_handle() const noexcept {
            return (void*)m_inst->native_handle();
        }
        template<class WinType>
        _Detail::pairsz basic_window<WinType>::size() const noexcept {
            return m_inst->size();
        }
        template<class WinType>
        void basic_window<WinType>::size(_Detail::pairsz sz) {
            m_inst->size(sz);
        }
        template <class WinType>
        void basic_window<WinType>::style(styles Style) {
            m_inst->style(Style);
        }
        template<class WinType>
        styles basic_window<WinType>::style() const {
            return m_inst->style();
        }
        template<class WinType>
        void basic_window<WinType>::title(const char* name) {
            m_inst->title(name);
        }
        template<class WinType>
        const char* basic_window<WinType>::title() const {
            return m_inst->title();
        }
        template <class WinType>
        void basic_window<WinType>::cursor_display(bool shouldDisplay) {
            m_inst->cursor_display(shouldDisplay);
        }
        template <class WinType>
        constexpr bool basic_window<WinType>::cursor_display() const noexcept {
            return m_inst->cursor_display();
        }

        template <class WinType>
        void basic_window<WinType>::set_icon(const wndimage& img) {
            m_inst->set_icon(img);
        }
        template <class WinType>
        void basic_window<WinType>::set_cursor(const wndimage& img) {
            m_inst->set_cursor(img);
        }
        template <class WinType>
        basic_window<WinType>::~basic_window() {
            delete m_inst;
        }
        // 这个工具函数专门针对最适配系统的 cfg 获取
        template<class WinType>
        const wndconfig basic_window<WinType>::get_best_config() {
            wndconfig cfg{};
            cfg.style         = initsetting;
#if   CRS_ISOS_WIN32
            DEVMODE win32Mode{};
            win32Mode.dmSize = sizeof(win32Mode);
            win32Mode.dmDriverExtra = 0;
            EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &win32Mode);
            cfg.width  = win32Mode.dmPelsWidth;
            cfg.height = win32Mode.dmPelsHeight;
#endif
            return cfg;
        }
    }
}   