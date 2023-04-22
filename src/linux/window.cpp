#include "window.h"
#include <xcb/xcb.h>

// global namespace.
namespace {
    // For keyboard event handles.
    static KeySym   _S_sym = 0;
    static char     _S_buf = 0;
    static uint32_t _S_len = 0;
    // For mouse event handles.
    static uint32_t _S_posx = 0;
    static uint32_t _S_posy = 0;
}

namespace odk {
    using namespace platform;
    x11_window::x11_window(const wndconfig& _cfg)
        :_M_is_should_close(false), 
         _M_wnd_size(_cfg.width, _cfg.height),
         _M_is_fullscrenn(_cfg.is_fullscreen),
         _M_is_cursor_display(true) {
            
        _M_wnd.display = XOpenDisplay(nullptr);
        if (_M_wnd.display == nullptr)
            throw X11_EXCEPT("Could not open display!");

        _M_wnd.screen      = DefaultScreen(_M_wnd.display);
        Visual* visual     = DefaultVisual(_M_wnd.display, _M_wnd.screen);

        _M_wnd.cmap = XCreateColormap(_M_wnd.display, 
                           RootWindow(_M_wnd.display, _M_wnd.screen), visual, AllocNone);

        XSetWindowAttributes attr;
        attr.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask |
                          PointerMotionMask | ButtonPressMask | ButtonReleaseMask |
                          ExposureMask | FocusChangeMask | VisibilityChangeMask |
                          EnterWindowMask | LeaveWindowMask | PropertyChangeMask;
        attr.colormap = _M_wnd.cmap;

        // Open the window.
        _M_wnd.window = XCreateWindow(_M_wnd.display, RootWindow(_M_wnd.display, _M_wnd.screen),
         0, 0, _Width, _Height, 0, DefaultDepth(_M_wnd.display, _M_wnd.screen), 
         InputOutput, visual, CWColormap|CWEventMask, &attr);

        if (_M_is_fullscrenn == true) {
            Atom wm_state   = XInternAtom (_M_wnd.display, "_NET_WM_STATE", _M_is_fullscrenn );
            Atom wm_fullscreen = XInternAtom (_M_wnd.display, "_NET_WM_STATE_FULLSCREEN", _M_is_fullscrenn );

            XChangeProperty(_M_wnd.display, _M_wnd.window, wm_state, XA_ATOM, 32,
                        PropModeReplace, (unsigned char *)&wm_fullscreen, 1);
        }

        set_title(_Title);
    }

    void x11_window::show(void) {
        XClearWindow(_M_wnd.display, _M_wnd.window);
        XMapWindow(_M_wnd.display, _M_wnd.window);
    }

    void x11_window::set_title(const char* _Title) {
        XStoreName(_M_wnd.display, _M_wnd.window, _Title);
    }

    void x11_window::cursor_display(bool _IsDisplay)  {
        if (_IsDisplay == true && _M_is_cursor_display == false) {
            XFixesShowCursor(_M_wnd.display, DefaultRootWindow(_M_wnd.display));
            _M_is_cursor_display = true;
        }
        else if (_IsDisplay == false && _M_is_cursor_display == true) {
            XFixesHideCursor(_M_wnd.display, DefaultRootWindow(_M_wnd.display));
            _M_is_cursor_display = false;
        }
        XFlush(_M_wnd.display);
        return;
    }
    bool x11_window::cursor_display(void) const {
        return _M_is_cursor_display;
    }

    void x11_window::full_screen(bool _IsFullScreen)  {
        bool exp = (_M_is_fullscrenn == false && _IsFullScreen == true) || 
        (_M_is_fullscrenn == true && _IsFullScreen == false);

        if (exp) {
            XEvent e;
            e.xclient.type         = ClientMessage;
            e.xclient.window       = _M_wnd.window;
            e.xclient.message_type = XInternAtom(_M_wnd.display, "_NET_WM_STATE", _IsFullScreen);
            e.xclient.format       = 32;
            e.xclient.data.l[0]    = 2;    // _NET_WM_STATE_TOGGLE
            e.xclient.data.l[1]    = XInternAtom(_M_wnd.display, "_NET_WM_STATE_FULLSCREEN", _IsFullScreen);
            e.xclient.data.l[2]    = 0;    // no second property to toggle
            e.xclient.data.l[3]    = 1;
            e.xclient.data.l[4]    = 0;

            XSendEvent(_M_wnd.display, DefaultRootWindow(_M_wnd.display), False,
            SubstructureRedirectMask | SubstructureNotifyMask, &e);

            XMoveResizeWindow(_M_wnd.display, DefaultRootWindow(_M_wnd.display),
            0, 0, _M_wnd_size.first, _M_wnd_size.second);
            // Flip the bool value.
            _M_is_fullscrenn = !_M_is_fullscrenn;
        }
        return;
    }

    bool x11_window::full_screen(void) const {
        return _M_is_fullscrenn;
    }

    void x11_window::close(bool _Value)  {
        _M_is_should_close = _Value;
    }

    bool x11_window::close(void) const  {
        return _M_is_should_close;
    }

    void x11_window::poll_events(void) {
        if (XPending(_M_wnd.display) > 0) {

        XNextEvent(_M_wnd.display, &_M_wnd.event);
        switch (_M_wnd.event.type) {
            /////////////////////////////////
            /////////// Keyboard stuff //////
            /////////////////////////////////
            default: break;
            case DestroyNotify: this->~x11_window(); break;
            case KeymapNotify : XRefreshKeyboardMapping(&_M_wnd.event.xmapping); break;
            case KeyPress:
                // Key mod settings.
                switch (_M_wnd.event.xkey.keycode) {
                case 50:
                    km_handle._M_mod_state[0] = false;
                    km_handle._M_mod_state[1] = true;
                    break;
                case 62:
                    km_handle._M_mod_state[0] = false;
                    km_handle._M_mod_state[2] = true;
                    break;
                case 37:
                    km_handle._M_mod_state[0] = false;
                    km_handle._M_mod_state[3] = true;
                    break;
                case 105:
                    km_handle._M_mod_state[0] = false;
                    km_handle._M_mod_state[4] = true;
                    break;
                case 64:
                    km_handle._M_mod_state[0] = false;
                    km_handle._M_mod_state[5] = true;
                    break;
                case 108:
                    km_handle._M_mod_state[0] = false;
                    km_handle._M_mod_state[6] = true;
                    break;
                default:
                    km_handle._M_mod_state[0] = true;
                    _S_sym = XLookupKeysym(&_M_wnd.event.xkey, 0);
                    if (_S_sym  == XK_Escape) {
                        km_handle._M_escape_event.is_pressed  = true;
                        km_handle._M_escape_event.is_released = false;
                        break;
                    }
                    km_handle._M_on_key(_G_press, _S_sym);
                    break;
                } // KeyPress's switch.
                break;
            case KeyRelease:
                // Key mod settings.
                switch (_M_wnd.event.xkey.keycode) {
                // For modifiers.
                    case 50:
                    case 62:
                    case 37:
                    case 105:
                    case 64:
                    case 108:
                        km_handle._M_mod_state.reset();
                        km_handle._M_mod_state[0] = true;
                        break;
                    default:
                        _S_sym = XLookupKeysym(&_M_wnd.event.xkey, 0);
                        if (_S_sym == XK_Escape) {
                            km_handle._M_escape_event.is_pressed  = true;
                            km_handle._M_escape_event.is_released = false;
                            break;
                        }
                        km_handle._M_on_key(_G_release, _S_sym);
                        break;
                }
                break;
            //! =============================
            //! ======= Mouse stuff =========
            //! =============================
            case ButtonPress:
                switch(_M_wnd.event.xbutton.button) {
                    case 1: km_handle._M_on_button(_G_press, button_e::left); break;
                    case 2: km_handle._M_on_button(_G_press, button_e::middle); break;
                    case 3: km_handle._M_on_button(_G_press, button_e::right); break;
                    case 4: km_handle._M_on_mouse(mouse_e::wup); break;
                    case 5: km_handle._M_on_mouse(mouse_e::wdown); break;
                }
                break;
            case ButtonRelease:
                switch(_M_wnd.event.xbutton.button) {
                    case 1: km_handle._M_on_button(_G_release, button_e::left); break;
                    case 2: km_handle._M_on_button(_G_release, button_e::middle); break;
                    case 3: km_handle._M_on_button(_G_release, button_e::right); break;
                }
                break;
            case MotionNotify:
                km_handle._M_on_mouse(mouse_e::move, 
                {_M_wnd.event.xmotion.x, _M_wnd.event.xmotion.y});
                break;
            case EnterNotify:
                km_handle._M_on_mouse(mouse_e::enter); break;
            case LeaveNotify:
                km_handle._M_on_mouse(mouse_e::leave); break;
            } //switch
        } // if (xpending)
    } // poll_events

    std::size_t x11_window::get_size(screen_prop _Enum) {
        XWindowAttributes attr;
        XGetWindowAttributes(_M_wnd.display, _M_wnd.window, &attr);

        switch (_Enum) {
            case screen_prop::scrwidth:  return attr.width;
            case screen_prop::scrheight: return attr.height;
        }
        return 0;
    }

    void* x11_window::native_handle(void) {
        return &_M_wnd;
    }

    kminput& x11_window::kmhandle() {
        return km_handle;
    }

    x11_window::~x11_window() {
        XFree(_M_wnd.visualinfo);
        XDestroyWindow(_M_wnd.display, _M_wnd.window);
        XFreeColormap(_M_wnd.display, _M_wnd.cmap);
        XCloseDisplay(_M_wnd.display);
    }

    const std::uint32_t x11_window::get_screenprop(screen_prop _Enum) {
        // Open the connection to the X server. Use the DISPLAY environment variable

        int i, screenNum;
        xcb_connection_t* const connection = xcb_connect(NULL, &screenNum);

        // Get the screen whose number is screenNum
        const xcb_setup_t* setup = xcb_get_setup(connection);
        xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);

        // we want the screen at index screenNum of the iterator
        for (i = 0; i < screenNum; ++i) {
            xcb_screen_next(&iter);
        }

        xcb_screen_t* screen = iter.data;

        switch (_Enum) {
            case 1: return screen->width_in_pixels;
            case 2: return screen->height_in_pixels;
        }

        return 0;
    }
    /////////////////////
    /// error handling 
    /////////////////////

    x11_exception::x11_exception(std::source_location _Loc, std::string_view _ErrStr) noexcept
        :except(_Loc) {
            _M_what += _ErrStr;
        }
    const char* x11_exception::what() const throw() {
        return _M_what.c_str();
    }
} // namespace odk;