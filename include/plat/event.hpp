#pragma once
#include "config.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"
namespace crs {
    namespace plat {
        // ��������������봰���йص��¼�����
        // ���е��¼����ͣ�ĩβ��������һ�� e ��ʶ
        class wevent {
        public:
            // ���ڴ�С����¼�
            struct size_e {
                std::size_t width;
                std::size_t height;
            };
            // ���������¼�
            struct key_e {
                kybd::kc code;  
                // �ж���Щ���ⰴ���Ƿ񱻰���
                bool     shift;
                bool     ctrl;
                bool     alt;
                bool     super;
            };
            // �ı������¼����
            struct text_e {
                // char32_t �� C++11 �����ԣ����� uint_least_32_t ��һ���ĵ���
                // ���������ĺ����廹�����Եȷ���Ŀ��ǣ�����ʹ�þ�����
                char32_t unicode; // Ψһ�ĳ�Ա�� utf-32 ģʽ�µ� unicode ��������
            };
            // ����ƶ��¼�
            struct mouz_mv_e {
                std::int32_t x;
                std::int32_t y;
            };
            // ��갴���¼�
            struct mouz_btn_e {
                mouz::btn    btn;
                std::int32_t x;
                std::int32_t y;
            };
            // �����¼�
            struct mouz_whu_e {
                mouz::whu    wheel;
                float        delta;
                std::int32_t x, y;
            };

            enum types
            {
                closed,                 // ���ڱ�Ҫ��ر�
                resized,                // ���ڴ�С����
                lostfocus,              // ����ʧȥ��ע
                gainedfocus,            // ���ڻ�ù�ע
                txtentered,             // �ı�����
                kyprsd,                 // ��������
                kyrlsd,                 // �����ɿ�
                mswhumvd,               // �����ֹ���
                msbtnprsd,              // ��갴ť����
                msbtnrlsd,              // ��갴ť�ɿ�
                msmvd,                  // ���ָ���ƶ�
                msentered,              // ���ָ����봰�ڿͻ���
                msleft,                 // ���ָ���뿪���ڿͻ���
            };

            static constexpr auto tcount = static_cast<std::size_t>(msleft + 1);
            types type; // �洢��һ���¼�������
            // �����������������������֧�ֵģ����ܷ������¼�
            // ������ʹ����������������Щ�¼������ǲ��еģ�Ҳ����ζ��
            // ������ÿһֻ֡�ܲ����¼������е�һ���¼�
            union {
                size_e      size;
                key_e       key;
                text_e      text;
                mouz_mv_e   msmv;
                mouz_btn_e  msbtn;
                mouz_whu_e  mswhu;
            };
        }; //! wevent
    }
}
