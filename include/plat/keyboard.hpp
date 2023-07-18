#pragma once
#include "config.hpp"
namespace crs {
    namespace plat {
        // (Keyboard) ������
        // ����������������뻹�а����������ع���
        // ����ಢ���ʺ����ı����������Ҫ���ı����������������ṩ�˶�������빦�ܡ�
        class kybd {
        public:
            // (KeyCode) �洢��������
            // ���а�����Ŷ�ֻд��һ��״̬������ CapsLock ֮����Щ���Ͳ���ʹ��
            enum kc : char16_t {
                undef = 0, // δ���밴��
                A,         // A
                B,         // B
                C,         // C
                D,         // D
                E,         // E
                F,         // F
                G,         // G
                H,         // H
                I,         // I
                J,         // J
                K,         // K
                L,         // L
                M,         // M
                N,         // N
                O,         // O
                P,         // P
                Q,         // Q
                R,         // R
                S,         // S
                T,         // T
                U,         // U
                V,         // V
                W,         // W
                X,         // X
                Y,         // Y
                Z,         // Z
                N0,        // ������ 0 // ���� ~ �ұ���һ�е�
                N1,        // ������ 1
                N2,        // ������ 2
                N3,        // ������ 3
                N4,        // ������ 4
                N5,        // ������ 5
                N6,        // ������ 6
                N7,        // ������ 7
                N8,        // ������ 8
                N9,        // ������ 9
                escape,    // �˳�
                Lctrl,     // �����
                Lshift,    // ���ϵ�
                Lalt,      // ����
                Lsuper,    // �󳬿� ���� Windows �����Ӵ��� Mac ������Ҷ�ݣ�������ұ��Ǹ�����
                Rctrl,     // �ҿ���
                Rshift,    // ���ϵ�
                Ralt,      // �ҽ���
                Rsuper,    // �ҳ��� ���� һ��ļ�����û���������
                menu,      // �˵��� (��Щ���̿�����Ҫ Fn ����ʹ��)
                Lbracket,  // [ 
                Rbracket,  // ] 
                semicolon, // ; 
                comma,     // , 
                period,    // . 
                quote,     // ' 
                slash,     // / 
                backslash, // \ 
                tilde,     // ~ 
                equal,     // = 
                hyphen,    // - ���ַ���С���̼Ӻ������Ǹ���
                space,     // �ո� 
                enter,     // �س�
                backspace, // �˸�
                tab,       // �Ʊ�
                pgup,      // ��ҳ
                pgdn,      // ��ҳ
                end,       // ĩҳ
                home,      // ��ҳ
                insert,    // ����
                del,       // ɾ��
                add,       // + 
                sub,       // -
                mul,       // * 
                div,       // / 
                left,      // ���ͷ
                right,     // �Ҽ�ͷ
                up,        // �ϼ�ͷ
                down,      // �¼�ͷ
                NP0,       // ���ְ� 0
                NP1,       // ���ְ� 1
                NP2,       // ���ְ� 2
                NP3,       // ���ְ� 3
                NP4,       // ���ְ� 4
                NP5,       // ���ְ� 5
                NP6,       // ���ְ� 6
                NP7,       // ���ְ� 7
                NP8,       // ���ְ� 8
                NP9,       // ���ְ� 9
                F1,        // F1 
                F2,        // F2 
                F3,        // F3 
                F4,        // F4 
                F5,        // F5 
                F6,        // F6 
                F7,        // F7 
                F8,        // F8 
                F9,        // F9 
                F10,       // F10
                F11,       // F11
                F12,       // F12
                F13,       // F13
                F14,       // F14
                F15,       // F15
                pause,     // ��ͣ
            };
            // ���̰�����������
            static constexpr auto kcount = static_cast<std::size_t>(pause);
            // �첽��ȡ����״̬���������֧��ͨ���߼� and �������
            // ��Ҫֱ����ö��֮��ʹ�� | �� & �ⲻ�Ǹ�״̬��
            // �ú����޹ش���״̬�������¼������������κ������ֱ�ӻ�ȡ�κΰ�������Ϣ
            // ���ӣ���Ϸ������ƶ�
            // if (is_pressed(W)) walk();
            // if (is_pressed(W) && is_pressed_async(Lshift)) run();
            static const bool is_pressed(kc k);
        };

    }
}