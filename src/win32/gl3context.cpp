#include "gl3context.h"
#include <gl/gl.h>
namespace {
    static void init_OpenGL_extensions(void) {
        // Before we can load extensions, we need a dummy OpenGL context, created using a dummy window.
        // We use a dummy window because you can only set the pixel format for a window once. For the
        // real window, we want to use wglChoosePixelFormatARB (so we can potentially specify options
        // that aren't available in PIXELFORMATDESCRIPTOR), but we can't load and use that before we
        // have a context.
        WNDCLASSA window_class = {};
        window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        window_class.lpfnWndProc = DefWindowProcA;
        window_class.hInstance = GetModuleHandle(0);
        window_class.lpszClassName = "Dummy_WGL_djuasiodwa";

        if (!RegisterClassA(&window_class))
            throw CRS_EXCEPTION("Failed to register dummy OpenGL window.");

        HWND dummy_window = CreateWindowExA(
            0,
            window_class.lpszClassName,
            "Dummy OpenGL Window",
            0,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            0,
            0,
            window_class.hInstance,
            0);

        if (!dummy_window)
            throw CRS_EXCEPTION("Failed to create dummy OpenGL window.");

        HDC dummy_dc = GetDC(dummy_window);

        PIXELFORMATDESCRIPTOR pfd{};
        pfd.nSize        = sizeof(pfd);
        pfd.nSize        = sizeof(PIXELFORMATDESCRIPTOR);  
        pfd.dwFlags      = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
        pfd.iPixelType   = PFD_TYPE_RGBA;                 
        pfd.cColorBits   = 32;                            
        pfd.cDepthBits   = 24;         
        pfd.cStencilBits = 8;
        pfd.iLayerType   = PFD_MAIN_PLANE;

        int pixel_format = ChoosePixelFormat(dummy_dc, &pfd);

        if (!pixel_format)
            throw CRS_EXCEPTION("Failed to find a suitable pixel format.");

        if (!SetPixelFormat(dummy_dc, pixel_format, &pfd))
            throw CRS_EXCEPTION("Failed to set the pixel format.");

        HGLRC dummy_context = wglCreateContext(dummy_dc);
        if (!dummy_context)
            throw CRS_EXCEPTION("Failed to create a dummy OpenGL rendering context.");

        if (!wglMakeCurrent(dummy_dc, dummy_context))
            throw CRS_EXCEPTION("Failed to activate dummy OpenGL rendering context.");

        wglCreateContextAttribsARB = (wglCreateContextAttribsARB_type*)wglGetProcAddress("wglCreateContextAttribsARB");
        wglChoosePixelFormatARB =    (wglChoosePixelFormatARB_type*)   wglGetProcAddress("wglChoosePixelFormatARB");

        wglMakeCurrent(dummy_dc, 0);
        wglDeleteContext(dummy_context);
        ReleaseDC(dummy_window, dummy_dc);
        DestroyWindow(dummy_window);
    }
    static HGLRC init_OpenGL(HDC real_dc, const CRS::MDrt::OpenGL_config& cfg) {
        init_OpenGL_extensions();

        int pixel_format_attribs[] = {
            WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
            WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
            WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
            WGL_COLOR_BITS_ARB,         32,
            WGL_DEPTH_BITS_ARB,         24,
            WGL_STENCIL_BITS_ARB,       8,
            0
        };

        int pixel_format;
        UINT num_formats;
        wglChoosePixelFormatARB(real_dc, pixel_format_attribs, 0, 1, &pixel_format, &num_formats);
        if (!num_formats)
            throw CRS_EXCEPTION("Failed to set the OpenGL pixel format.");

        PIXELFORMATDESCRIPTOR pfd;
        DescribePixelFormat(real_dc, pixel_format, sizeof(pfd), &pfd);
        if (!SetPixelFormat(real_dc, pixel_format, &pfd))
            throw CRS_EXCEPTION("Failed to set the OpenGL pixel format.");

        int gl33_attribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, cfg.major,
            WGL_CONTEXT_MINOR_VERSION_ARB, cfg.minor,
            WGL_CONTEXT_FLAGS_ARB       ,  cfg.flags,
            WGL_CONTEXT_PROFILE_MASK_ARB,  cfg.mask,
            0,
        };

        HGLRC gl33_context = wglCreateContextAttribsARB(real_dc, 0, gl33_attribs);
        if (!gl33_context)
            throw CRS_EXCEPTION("Failed to create OpenGL context.");

        if (!wglMakeCurrent(real_dc, gl33_context))
            throw CRS_EXCEPTION("Failed to activate OpenGL rendering context.");

        return gl33_context;
    }
}

namespace CRS {
    namespace MDrt {
        GL_context_impl::GL_context_impl(const OpenGL_config& cfg) :
            m_hwnd     (nullptr), 
            m_device   (nullptr), 
            m_GLcontext(nullptr),
            m_cfg      (cfg) {}
        void GL_context_impl::init_on_handle(void* Handle) {
            m_hwnd      = reinterpret_cast<HWND>(Handle);
            m_device    = GetDC(m_hwnd);
            m_GLcontext = init_OpenGL(m_device, m_cfg);
        }
        void GL_context_impl::swap_buffers() {
            SwapBuffers(m_device);
        }
        void GL_context_impl::clear_color(float r, float g, float b) {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(r, g, b, 1.f);
        }
        const char* GL_context_impl::version() {
            return (char*)glGetString(GL_VERSION);
        }
        GL_context_impl::~GL_context_impl() {
            if (m_GLcontext) wglDeleteContext(m_GLcontext);
            if (m_device)    ReleaseDC(m_hwnd, m_device);
        }
    }
}