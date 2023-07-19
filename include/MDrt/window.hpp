#pragma once
#include "event.hpp"
#include <utility>

namespace CRS {
    namespace MDrt {
        // ���� ���ָ�� ����ͼ�� ���а�ť�ȵȵ�ͼƬ��ʽ��
        struct wndimage {
            std::byte*    pixels;
            std::size_t   width, height;
            std::size_t   channels;
        };
        typedef enum {
            none       = 0,            // No border / title bar (this flag and all others are mutually exclusive)
            titlebar   = 1 << 0,       // Title bar + fixed border
            resize     = 1 << 1,       // Title bar + resizable border + maximize button
            close      = 1 << 2,       // Title bar + close button
            fullscreen = 1 << 3,       // Fullscreen mode (this flag and all others are mutually exclusive)

            initsetting = (1 << 3) - 1
        } styles;
        struct wndconfig {
            std::size_t   width;
            std::size_t   height;
            const char*   title;
            styles        style;
            wndimage      icon, cursor;
        };
        // �û���Ҫָ���������ͣ���ģ����Զ�����ָ��
        template <class WinType>
        class basic_window {
            WinType* m_inst;
        public:

            basic_window(const wndconfig&);

            // �������Ͳ�֧�ֿ������ƶ�
            basic_window(const basic_window<WinType>&) = delete;
            basic_window(basic_window<WinType>&&) = delete;

            // basic window framework
            void                   show();
            bool                   poll_event(wevent& E);
            void                   close(bool _IsShouldClose);
            constexpr bool         close() const noexcept;
            void*                  native_handle() const noexcept;

            _Detail::pairsz        size() const noexcept;
            void                   size(_Detail::pairsz);
            void                   style(styles _Style);
            styles                 style() const;
            void                   title(const char*);
            const char*            title() const;
            void                   cursor_display(bool _ShouldDisplay);
            constexpr bool         cursor_display() const noexcept;

            void                   set_icon  (const wndimage& img);
            void                   set_cursor(const wndimage& img);

            static const wndconfig get_best_config();
            ~basic_window();
        };
        // ���������Ǹ��û�ʹ�õ�
        using window = basic_window<plat_window>;
    }

}//! namespace CRS.