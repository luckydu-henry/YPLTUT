#pragma once
#include "config.hpp"
namespace crs {
    namespace plat {
        // ����һ����д�����������д��ԭ���� se ���Щ�ͻ���� z �ķ���
        // ��д�������������� API �ı��볤�ȶ��䣬��ǿ����Ŀɶ��Ժ�����
        class mouz {
        public:
            // (Button)
            // ��ť����ö��
            enum btn : char16_t {
                bundef,  // δ���尴��
                left,
                right,  
                middle, // �����ǿ��԰��µ�
                xbtn1,  // ֧�ֺ���չ���������Ż��������
                xbtn2   // ��չ�� 2
            };
            // (Wheel)
            // ���ֱ���ö��
            enum whu : char16_t {
                wundef, // δ���������Ϊ
                vt,     // ��ֱ���֣���������ϵĳ������
                hz,     // ˮƽ���֣�һЩ����������
            };
            static constexpr auto bcount = static_cast<std::size_t>(xbtn2);
            static constexpr auto wcount = static_cast<std::size_t>(hz);
            // �����һ����������������첽��ȡ���״̬
            // ����������ʵ������Ҽ�ͬʱ�������Ĳ��������Ǵ����¼��Ͳ���
            static const bool is_pressed(btn);
        };


    }
}