#pragma once
#include "config.hpp"
namespace crs {
    namespace plat {
        // 这是一个缩写，会用这个缩写的原因是 se 念快些就会近似 z 的发音
        // 缩写可以让其与其它 API 的编码长度对其，增强代码的可读性和美感
        class mouz {
        public:
            // (Button)
            // 按钮编码枚举
            enum btn : char16_t {
                bundef,  // 未定义按键
                left,
                right,  
                middle, // 滚轮是可以按下的
                xbtn1,  // 支持宏扩展的特殊鼠标才会有这个键
                xbtn2   // 扩展键 2
            };
            // (Wheel)
            // 滚轮编码枚举
            enum whu : char16_t {
                wundef, // 未定义滚轮行为
                vt,     // 垂直滚轮，就是鼠标上的常规滚轮
                hz,     // 水平滚轮，一些特殊鼠标会有
            };
            static constexpr auto bcount = static_cast<std::size_t>(xbtn2);
            static constexpr auto wcount = static_cast<std::size_t>(hz);
            // 与键盘一样，这个函数可以异步获取鼠标状态
            // 所以它可以实现左键右键同时按这样的操作，但是窗口事件就不行
            static const bool is_pressed(btn);
        };


    }
}