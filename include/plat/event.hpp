#pragma once
#include "config.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"
namespace crs {
    namespace plat {
        // 这个类用来进行与窗口有关的事件处理
        // 所有的事件类型，末尾都跟随有一个 e 标识
        class wevent {
        public:
            // 窗口大小变更事件
            struct size_e {
                std::size_t width;
                std::size_t height;
            };
            // 按键输入事件
            struct key_e {
                kybd::kc code;  
                // 判断这些特殊按键是否被按下
                bool     shift;
                bool     ctrl;
                bool     alt;
                bool     super;
            };
            // 文本输入事件侦测
            struct text_e {
                // char32_t 是 C++11 的特性，它与 uint_least_32_t 是一样的但是
                // 出于上下文和语义还有特性等方面的考虑，这里使得就是它
                char32_t unicode; // 唯一的成员是 utf-32 模式下的 unicode 按键编码
            };
            // 鼠标移动事件
            struct mouz_mv_e {
                std::int32_t x;
                std::int32_t y;
            };
            // 鼠标按键事件
            struct mouz_btn_e {
                mouz::btn    btn;
                std::int32_t x;
                std::int32_t y;
            };
            // 滚轮事件
            struct mouz_whu_e {
                mouz::whu    wheel;
                float        delta;
                std::int32_t x, y;
            };

            enum types
            {
                closed,                 // 窗口被要求关闭
                resized,                // 窗口大小重置
                lostfocus,              // 窗口失去关注
                gainedfocus,            // 窗口获得关注
                txtentered,             // 文本键入
                kyprsd,                 // 按键按下
                kyrlsd,                 // 按键松开
                mswhumvd,               // 鼠标滚轮滚动
                msbtnprsd,              // 鼠标按钮按下
                msbtnrlsd,              // 鼠标按钮松开
                msmvd,                  // 鼠标指针移动
                msentered,              // 鼠标指针进入窗口客户区
                msleft,                 // 鼠标指针离开窗口客户区
            };

            static constexpr auto tcount = static_cast<std::size_t>(msleft + 1);
            types type; // 存储了一个事件的类型
            // 这个匿名联集储存了所有受支持的，可能发生的事件
            // 由于它使用了联集，所以这些事件并不是并行的，也就意味着
            // 窗口在每一帧只能捕获事件队列中的一个事件
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
