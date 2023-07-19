#include <MDrt/keyboard.hpp>
#include <MDrt/mouse.hpp>
#if    CRS_ISOS_WIN32
#include <windows.h>
#endif  
namespace CRS {
    namespace MDrt {
#if    CRS_ISOS_WIN32
        const bool kybd::is_pressed(kybd::kc key) {
            char32_t vkey = 0;
            switch (key) {

                default:               vkey = 0;             break;
                case kybd::A:          vkey = 'A';           break;
                case kybd::B:          vkey = 'B';           break;
                case kybd::C:          vkey = 'C';           break;
                case kybd::D:          vkey = 'D';           break;
                case kybd::E:          vkey = 'E';           break;
                case kybd::F:          vkey = 'F';           break;
                case kybd::G:          vkey = 'G';           break;
                case kybd::H:          vkey = 'H';           break;
                case kybd::I:          vkey = 'I';           break;
                case kybd::J:          vkey = 'J';           break;
                case kybd::K:          vkey = 'K';           break;
                case kybd::L:          vkey = 'L';           break;
                case kybd::M:          vkey = 'M';           break;
                case kybd::N:          vkey = 'N';           break;
                case kybd::O:          vkey = 'O';           break;
                case kybd::P:          vkey = 'P';           break;
                case kybd::Q:          vkey = 'Q';           break;
                case kybd::R:          vkey = 'R';           break;
                case kybd::S:          vkey = 'S';           break;
                case kybd::T:          vkey = 'T';           break;
                case kybd::U:          vkey = 'U';           break;
                case kybd::V:          vkey = 'V';           break;
                case kybd::W:          vkey = 'W';           break;
                case kybd::X:          vkey = 'X';           break;
                case kybd::Y:          vkey = 'Y';           break;
                case kybd::Z:          vkey = 'Z';           break;
                case kybd::N0:         vkey = '0';           break;
                case kybd::N1:         vkey = '1';           break;
                case kybd::N2:         vkey = '2';           break;
                case kybd::N3:         vkey = '3';           break;
                case kybd::N4:         vkey = '4';           break;
                case kybd::N5:         vkey = '5';           break;
                case kybd::N6:         vkey = '6';           break;
                case kybd::N7:         vkey = '7';           break;
                case kybd::N8:         vkey = '8';           break;
                case kybd::N9:         vkey = '9';           break;
                case kybd::escape:     vkey = VK_ESCAPE;     break;
                case kybd::Lctrl:      vkey = VK_LCONTROL;   break;
                case kybd::Lshift:     vkey = VK_LSHIFT;     break;
                case kybd::Lalt:       vkey = VK_LMENU;      break;
                case kybd::Lsuper:     vkey = VK_LWIN;       break;
                case kybd::Rctrl:      vkey = VK_RCONTROL;   break;
                case kybd::Rshift:     vkey = VK_RSHIFT;     break;
                case kybd::Ralt:       vkey = VK_RMENU;      break;
                case kybd::Rsuper:     vkey = VK_RWIN;       break;
                case kybd::menu:       vkey = VK_APPS;       break;
                case kybd::Lbracket:   vkey = VK_OEM_4;      break;
                case kybd::Rbracket:   vkey = VK_OEM_6;      break;
                case kybd::semicolon:  vkey = VK_OEM_1;      break;
                case kybd::comma:      vkey = VK_OEM_COMMA;  break;
                case kybd::period:     vkey = VK_OEM_PERIOD; break;
                case kybd::quote:      vkey = VK_OEM_7;      break;
                case kybd::slash:      vkey = VK_OEM_2;      break;
                case kybd::backslash:  vkey = VK_OEM_5;      break;
                case kybd::tilde:      vkey = VK_OEM_3;      break;
                case kybd::equal:      vkey = VK_OEM_PLUS;   break;
                case kybd::hyphen:     vkey = VK_OEM_MINUS;  break;
                case kybd::space:      vkey = VK_SPACE;      break;
                case kybd::enter:      vkey = VK_RETURN;     break;
                case kybd::backspace:  vkey = VK_BACK;       break;
                case kybd::tab:        vkey = VK_TAB;        break;
                case kybd::pgup:       vkey = VK_PRIOR;      break;
                case kybd::pgdn:       vkey = VK_NEXT;       break;
                case kybd::end:        vkey = VK_END;        break;
                case kybd::home:       vkey = VK_HOME;       break;
                case kybd::insert:     vkey = VK_INSERT;     break;
                case kybd::del:        vkey = VK_DELETE;     break;
                case kybd::add:        vkey = VK_ADD;        break;
                case kybd::sub:        vkey = VK_SUBTRACT;   break;
                case kybd::mul:        vkey = VK_MULTIPLY;   break;
                case kybd::div:        vkey = VK_DIVIDE;     break;
                case kybd::left:       vkey = VK_LEFT;       break;
                case kybd::right:      vkey = VK_RIGHT;      break;
                case kybd::up:         vkey = VK_UP;         break;
                case kybd::down:       vkey = VK_DOWN;       break;
                case kybd::NP0:        vkey = VK_NUMPAD0;    break;
                case kybd::NP1:        vkey = VK_NUMPAD1;    break;
                case kybd::NP2:        vkey = VK_NUMPAD2;    break;
                case kybd::NP3:        vkey = VK_NUMPAD3;    break;
                case kybd::NP4:        vkey = VK_NUMPAD4;    break;
                case kybd::NP5:        vkey = VK_NUMPAD5;    break;
                case kybd::NP6:        vkey = VK_NUMPAD6;    break;
                case kybd::NP7:        vkey = VK_NUMPAD7;    break;
                case kybd::NP8:        vkey = VK_NUMPAD8;    break;
                case kybd::NP9:        vkey = VK_NUMPAD9;    break;
                case kybd::F1:         vkey = VK_F1;         break;
                case kybd::F2:         vkey = VK_F2;         break;
                case kybd::F3:         vkey = VK_F3;         break;
                case kybd::F4:         vkey = VK_F4;         break;
                case kybd::F5:         vkey = VK_F5;         break;
                case kybd::F6:         vkey = VK_F6;         break;
                case kybd::F7:         vkey = VK_F7;         break;
                case kybd::F8:         vkey = VK_F8;         break;
                case kybd::F9:         vkey = VK_F9;         break;
                case kybd::F10:        vkey = VK_F10;        break;
                case kybd::F11:        vkey = VK_F11;        break;
                case kybd::F12:        vkey = VK_F12;        break;
                case kybd::F13:        vkey = VK_F13;        break;
                case kybd::F14:        vkey = VK_F14;        break;
                case kybd::F15:        vkey = VK_F15;        break;
                case kybd::pause:      vkey = VK_PAUSE;      break;
            }
            return (GetAsyncKeyState(vkey) & 0x8000) != 0;
        }
        const bool mouz::is_pressed(mouz::btn bt) {
            char32_t vkey = 0;
            switch (bt) {
                case mouz::left:      vkey = GetSystemMetrics(SM_SWAPBUTTON) ? VK_RBUTTON : VK_LBUTTON; break;
                case mouz::right:     vkey = GetSystemMetrics(SM_SWAPBUTTON) ? VK_LBUTTON : VK_RBUTTON; break;
                case mouz::middle:    vkey = VK_MBUTTON;  break;
                case mouz::xbtn1:     vkey = VK_XBUTTON1; break;
                case mouz::xbtn2:     vkey = VK_XBUTTON2; break;
                default:              vkey = 0;           break;
            }
            return (GetAsyncKeyState(vkey) & 0x8000) != 0;
        }
#endif
    }
}