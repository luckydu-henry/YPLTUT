#ifndef _ODK_LINUX_H_
#define _ODK_LINUX_H_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/cursorfont.h>
#include <X11/Sunkeysym.h>
#include <X11/extensions/Xfixes.h>

namespace odk {
    // This is a simple wrapper to make data transfer easier.
    // For GetHandle function to get Linux handle.
    // These are very important information.
    struct x11_hwnd {
        ::Display*     display;
        ::Window       window;
        ::XEvent       event;
        ::Colormap     cmap;
        ::XVisualInfo* visualinfo;
        int            screen;
    };
}
#endif //! _ODK_LINUX_H_