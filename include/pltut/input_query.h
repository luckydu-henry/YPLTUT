#ifndef _ODK_WINDOWAPI_INPUTQ_HPP_
#define _ODK_WINDOWAPI_INPUTQ_HPP_

#include "config.h"

namespace yan {

    enum class scancode_e : unsigned char {
        null = 0,
        // number keys
        _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
        // backspace and tap
        backspace, tap,
        // characters
        A, B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        // home left up right down.
        home, left, up, right, down,
        // others
        end, escape, capslock, enter, space
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
        lshift, rshift, lctrl, rctrl, lalt,
    };


    // scan trans to keys
    template <typename _TransType>
    struct scan_trans {};

    template <>
    struct scan_trans<unsigned char> {
        using trans_type = unsigned char;

        static constexpr unsigned char max_queue_size = 0xff;
        static constexpr unsigned char scan_to_key(scancode_e _Scan) {
            return key_table[static_cast<unsigned char>(_Scan)];
        }
    private:
        static constexpr unsigned char key_table[256] = {
            '\0',
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
            // backspace and tab.
            0x08, 0x09,
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
            // home left up right down.
            0x24, 0x25, 0x26, 0x27, 0x28,
            // others
            0x23, 0x18, 0x14, 0x0d, 0x20
        };
    };

    template <>
    struct scan_trans<unsigned short> {
        using trans_type = unsigned short;

        static constexpr unsigned short max_queue_size = 0xffff;
        static constexpr unsigned short scan_to_key(scancode_e _Scan) {
            return key_table[static_cast<unsigned short>(_Scan)];
        }
    private:
        static constexpr unsigned short key_table[65536] = {
            0,
            // 0 - 9
            0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039,
            // backspace and tab
            0xff08, 0xff09,
            // A - Z
            0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067,
            0x0068, 0x0069, 0x006a, 0x006b, 0x006c, 0x006d, 0x006e,
            0x006f, 0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075,
            0x0076, 0x0077, 0x0078, 0x0079, 0x007a,
            // home left up right down.
            0xff50, 0xff51, 0xff52, 0xff53, 0xff54,
            // others
            0xff57, 0xff1b, 0xffe5, 0xff8d, 0x0020
        };
    };

#if   IS_PLATFORM_WIN32
    using plat_scan_trans = scan_trans<unsigned char>;
#elif IS_PLATFORM_LINUX
    using plat_scan_trans = scan_trans<unsigned short>;
#endif
}

#endif //! _ODK_WINDOWAPI_KEYMAPPING_HPP_