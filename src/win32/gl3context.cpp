#include "gl3context.h"
#include <gl/gl.h>

// global namespace.
namespace {
    //! wglCreateContextAttribsARB function pointer load.
    typedef HGLRC WINAPI wglCreateContextAttribsARB_type(HDC hdc, HGLRC hShareContext,
        const int* attribList);
    wglCreateContextAttribsARB_type* wglCreateContextAttribsARB;
}

namespace yan {
    using namespace platform;

    win32_gl_rndr::win32_gl_rndr(int _Major, int _Minor)
        :_M_hwnd(nullptr), _M_device(nullptr), _M_GLcontext(nullptr),
        _M_ajor(_Major), _M_inor(_Minor) {}

    void win32_gl_rndr::init_on_handle(void* _Handle) {
        _M_hwnd = static_cast<HWND>(_Handle);
        _M_device = GetDC(_M_hwnd);

        if (_M_device == nullptr) {
            DestroyWindow(_M_hwnd);
            throw WGL_EXCEPT("Failed to open device!");
        }
        // Set the pixel format for the device context:
        PIXELFORMATDESCRIPTOR pfd = { };
        pfd.nSize = sizeof(pfd);
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);  // Set the size of the PFD to the size of the class
        pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;   // Enable double buffering
        pfd.iPixelType = PFD_TYPE_RGBA; // Set our application to use RGBA pixels
        pfd.cColorBits = 32;        // Give 32 bits of color information (the higher, the more colors)
        pfd.cDepthBits = 32;        // Give 32 bits of depth information (the higher, the more depth levels)
        pfd.iLayerType = PFD_MAIN_PLANE;    // Set the layer of the PFD

        int format = ChoosePixelFormat(_M_device, &pfd);
        if (format == 0 || SetPixelFormat(_M_device, format, &pfd) == FALSE) {
            ReleaseDC(_M_hwnd, _M_device);
            DestroyWindow(_M_hwnd);
            throw WGL_EXCEPT("Failed to set a compatible pixel format!");
        }

        if (_M_ajor < 3)
        {
            _M_GLcontext = wglCreateContext(_M_device);
            wglMakeCurrent(_M_device, _M_GLcontext);
            if (!gladLoaderLoadWGL(_M_device))
                throw WGL_EXCEPT("WGL load error!");
            return;
        }

        // Modern OpenGL load.
        // Create and enable a temporary (helper) opengl context:
        HGLRC temp_context = nullptr;
        if (nullptr == (temp_context = wglCreateContext(_M_device))) {
            ReleaseDC(_M_hwnd, _M_device);
            DestroyWindow(_M_hwnd);
            throw WGL_EXCEPT("Failed to create the initial rendering context!");
        }
        wglMakeCurrent(_M_device, temp_context);

        // Load WGL Extensions:
        gladLoaderLoadWGL(_M_device);

        // Set the desired OpenGL version:
        int attributes[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, _M_ajor,
            WGL_CONTEXT_MINOR_VERSION_ARB, _M_inor,
            WGL_CONTEXT_FLAGS_ARB,
            WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };

        wglCreateContextAttribsARB = (wglCreateContextAttribsARB_type*)wglGetProcAddress(
            "wglCreateContextAttribsARB");

        // Create the final opengl context and get rid of the temporary one:
        if (nullptr == (_M_GLcontext = wglCreateContextAttribsARB(_M_device, nullptr, attributes))) {
            wglDeleteContext(temp_context);
            ReleaseDC(_M_hwnd, _M_device);
            DestroyWindow(_M_hwnd);

            throw WGL_EXCEPT("Failed to create the final rendering context!");
        }
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(temp_context);
        wglMakeCurrent(_M_device, _M_GLcontext);
    }

    void win32_gl_rndr::clear_color(float R, float G, float B) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(R, G, B, 1.f);
    }

    void win32_gl_rndr::swap_frame(void) {
        if (!SwapBuffers(_M_device))
            throw WGL_EXCEPT("Can't swap buffers!");
    }

    win32_gl_rndr::~win32_gl_rndr() {
        if (_M_GLcontext)
            wglDeleteContext(_M_GLcontext);
        if (_M_device)
            ReleaseDC(_M_hwnd, _M_device);
    }

    wgl_exception::wgl_exception(std::source_location _Loc, std::string_view _des) noexcept
        :except(_Loc)
    { _M_what += _des;}
}