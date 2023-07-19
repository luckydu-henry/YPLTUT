#ifndef _WIN32_WINDOW_H_
#define _WIN32_WINDOW_H_

#include <MDrt/exception.hpp>
#include <MDrt/window.hpp>
#include "../event_impl.h"
#include <Windows.h>

namespace CRS {
    namespace MDrt {

        class win32_window {
            win32_window(const win32_window&) = delete;
            win32_window(win32_window&&) = delete;
            win32_window& operator=(const win32_window&) = delete;
        public:

            win32_window(const wndconfig&);

            void             show(void);
            // ͼ���ָ�벻֧�ֻ�ȡ��ֻ������
            void             set_icon  (const wndimage& img);
            void             set_cursor(const wndimage& img);

            // �������ͻ�ȡ��
            void             title(const char* _Name);
            const char*      title() const;
            void             style(styles _Style);
            styles           style() const;
            void             cursor_display(bool _ShouldDisplay);
            bool             cursor_display(void) const;
            void             close(bool _IsShouldClose);
            bool             close(void) const;
            void             auto_repeat(bool);
            bool             auto_repeat() const;
            _Detail::pairsz  size() const;
            void             size(_Detail::pairsz);

            void*            native_handle(void);

            // ���������⺯���Ǵ� event_impl α�̳����ģ����Ⲣ����¶
            inline void  push_event(wevent& E)            { CRS_PLAT_EVENT_IMPL_PUSH_EVENT(E); }
            inline bool  pop_event(wevent& E, bool block) { CRS_PLAT_EVENT_IMPL_POP_EVENT(E, block); }

            ~win32_window();
        // ������������ʹ���¼��̳�
        protected:
            // α��̳�
            CRS_INHERITAGE_EVENT_IMPL;
        private:

            static LRESULT CALLBACK m_HandleMsgSetup(HWND, UINT, WPARAM, LPARAM) noexcept;
            static LRESULT CALLBACK m_HandleMsgThunk(HWND, UINT, WPARAM, LPARAM) noexcept;

            LRESULT m_handle_msg(HWND, UINT, WPARAM, LPARAM); // ʵ�ʵ�ϵͳ��Ϣ����
            void    m_process_events();
            void    m_grab_cursor(bool);
            void    m_set_tracking(bool);
            void    m_to_fullscreen();


            HWND                m_handle;
            HCURSOR             m_cur;
            HICON               m_ico;
            HINSTANCE           m_inst;
            DWORD               m_wnd_style;
            styles              m_style;
            char16_t            m_surrogate = 0;
            bool                m_is_msinside          = false;
            bool                m_is_cursor_grabbed    = false;
            bool                m_is_resizing          = false;
            bool                m_is_cursor_display    = false;
            bool                m_is_full_screen       = false;
            bool                m_is_close             = false;
            bool                m_is_auto_repeated     = false;
            std::string_view    m_name;
            _Detail::pairsz     m_last_size;

        };
    }
} // namespace CRS;
#endif //! _WIN32_WINDOW_H_
