#pragma once
#include "config.hpp"
namespace crs {
    namespace plat {
        // (Keyboard) 键盘类
        // 用来处理与键盘输入还有按键编码的相关功能
        // 这个类并不适合做文本处理，如果需要做文本处理，还有其它类提供了额外的输入功能。
        class kybd {
        public:
            // (KeyCode) 存储案件编码
            // 所有按键编号都只写了一种状态，按下 CapsLock 之后这些键就不能使了
            enum kc : char16_t {
                undef = 0, // 未编码按键
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
                N0,        // 主键盘 0 // 就是 ~ 右边那一行的
                N1,        // 主键盘 1
                N2,        // 主键盘 2
                N3,        // 主键盘 3
                N4,        // 主键盘 4
                N5,        // 主键盘 5
                N6,        // 主键盘 6
                N7,        // 主键盘 7
                N8,        // 主键盘 8
                N9,        // 主键盘 9
                escape,    // 退出
                Lctrl,     // 左控制
                Lshift,    // 左上档
                Lalt,      // 左交替
                Lsuper,    // 左超控 —— Windows 下是视窗键 Mac 下是四叶草（左控制右边那个键）
                Rctrl,     // 右控制
                Rshift,    // 右上档
                Ralt,      // 右交替
                Rsuper,    // 右超控 —— 一般的键盘是没有这个键的
                menu,      // 菜单键 (有些键盘可能需要 Fn 才能使用)
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
                hyphen,    // - 连字符（小键盘加号上面那个）
                space,     // 空格 
                enter,     // 回车
                backspace, // 退格
                tab,       // 制表
                pgup,      // 上页
                pgdn,      // 下页
                end,       // 末页
                home,      // 主页
                insert,    // 插入
                del,       // 删除
                add,       // + 
                sub,       // -
                mul,       // * 
                div,       // / 
                left,      // 左箭头
                right,     // 右箭头
                up,        // 上箭头
                down,      // 下箭头
                NP0,       // 数字板 0
                NP1,       // 数字板 1
                NP2,       // 数字板 2
                NP3,       // 数字板 3
                NP4,       // 数字板 4
                NP5,       // 数字板 5
                NP6,       // 数字板 6
                NP7,       // 数字板 7
                NP8,       // 数字板 8
                NP9,       // 数字板 9
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
                pause,     // 暂停
            };
            // 键盘按键的总数量
            static constexpr auto kcount = static_cast<std::size_t>(pause);
            // 异步获取按键状态，这个函数支持通过逻辑 and 进行组合
            // 不要直接在枚举之间使用 | 或 & 这不是个状态机
            // 该函数无关窗口状态，不是事件处理，可以在任何情况下直接获取任何按键的信息
            // 例子：游戏人物的移动
            // if (is_pressed(W)) walk();
            // if (is_pressed(W) && is_pressed_async(Lshift)) run();
            static const bool is_pressed(kc k);
        };

    }
}