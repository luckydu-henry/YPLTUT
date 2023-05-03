#ifndef _ODK_WINDOWAPI_INPUTQ_HPP_
#define _ODK_WINDOWAPI_INPUTQ_HPP_

#include "config.h"

namespace yan {

    enum class scancode_e : unsigned short {
        null = 0,
#if IS_PLATFORM_WIN32
        // number keys
        _0 = '0', _1, _2, _3, _4, _5, _6, _7, _8, _9,
        // backspace and tap
        backspace = 0x08, tap = 0x09,
        // characters
        A = 'A', B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        // home left up right down.
        home = 0x24, left, up, right, down,
        // others
        end = 0x23, escape = 0x1b, capslock = 0x14, enter = 0x0d, space = 0x20
#elif IS_PLATFORM_LINUX
        _0 = 0x0030, _1, _2, _3, _4, _5, _6, _7, _8, _9,
        // backspace and tap
        backspace = 0xff08, tap,
        // characters
        A = 0x0061, B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        // home left up right down.
        home = 0xff50, left, up, right, down,
        // others
        end = 0xff57, escape = 0xff1b, capslock = 0xffe5, enter = 0xff8d, space = 0x0020
#endif
    };

    /// Mouse buttons enum class.
    enum class button_e : unsigned char {
        null = 0,
        left, right, cancel, middle
    };

    enum class mouse_e : unsigned char {
        null = 0,
        wup, wdown, move, enter, leave
    };

    enum class mod_e : unsigned char {
        null = 0x9f,
        lshift, rshift, lctrl, rctrl, lalt,ralt
    };


    // scan trans to keys
    template <typename _TransType>
    struct scan_trans {};

    template <>
    struct scan_trans<unsigned char> {
        using trans_type = unsigned char;
        static constexpr unsigned char max_queue_size = 0xff + 1;
    };

    template <>
    struct scan_trans<unsigned short> {
        using trans_type = unsigned short;
        static constexpr unsigned short max_queue_size = 0xffff + 1;
    };


#if   IS_PLATFORM_WIN32
    using plat_scan_trans = scan_trans<unsigned char>;
#elif IS_PLATFORM_LINUX
    using plat_scan_trans = scan_trans<unsigned short>;
#endif

}
#endif //! _ODK_WINDOWAPI_KEYMAPPING_HPP_