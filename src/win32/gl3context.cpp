#include "gl3context.h"
#include <gl/gl.h>

// global namespace.
namespace {
    //! wglCreateContextAttribsARB function pointer load.
    typedef HGLRC WINAPI wglCreateContextAttribsARB_type(HDC hdc, HGLRC hShareContext,
        const int* attribList);
    wglCreateContextAttribsARB_type* wglCreateContextAttribsARB;
}

namespace crs {
    namespace plat {

        gl_context_impl::gl_context_impl(const opengl_config& cfg)
            :m_hwnd(nullptr), m_device(nullptr), m_GLcontext(nullptr),
            m_major(cfg.major), m_minor(cfg.minor) {}

        void gl_context_impl::init_on_handle(void* _Handle) {
            m_hwnd = static_cast<HWND>(_Handle);
            m_device = GetDC(m_hwnd);

            if (m_device == nullptr) {
                DestroyWindow(m_hwnd);
                throw CRS_EXCEPTION("Failed to open device!");
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

            int format = ChoosePixelFormat(m_device, &pfd);
            if (format == 0 || SetPixelFormat(m_device, format, &pfd) == FALSE) {
                ReleaseDC(m_hwnd, m_device);
                DestroyWindow(m_hwnd);
                throw CRS_EXCEPTION("Failed to set a compatible pixel format!");
            }

            if (m_major < 3)
            {
                m_GLcontext = wglCreateContext(m_device);
                wglMakeCurrent(m_device, m_GLcontext);
                if (!gladLoaderLoadWGL(m_device))
                    throw CRS_EXCEPTION("WGL load error!");
                return;
            }

            // Modern OpenGL load.
            // Create and enable a temporary (helper) opengl context:
            HGLRC temp_context = nullptr;
            if (nullptr == (temp_context = wglCreateContext(m_device))) {
                ReleaseDC(m_hwnd, m_device);
                DestroyWindow(m_hwnd);
                throw CRS_EXCEPTION("Failed to create the initial rendering context!");
            }
            wglMakeCurrent(m_device, temp_context);

            // Load WGL Extensions:
            gladLoaderLoadWGL(m_device);

            // Set the desired OpenGL version:
            int attributes[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB, m_major,
                WGL_CONTEXT_MINOR_VERSION_ARB, m_minor,
                WGL_CONTEXT_FLAGS_ARB,
                WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                0
            };

            wglCreateContextAttribsARB = (wglCreateContextAttribsARB_type*)wglGetProcAddress(
                "wglCreateContextAttribsARB");

            // Create the final opengl context and get rid of the temporary one:
            if (nullptr == (m_GLcontext = wglCreateContextAttribsARB(m_device, nullptr, attributes))) {
                wglDeleteContext(temp_context);
                ReleaseDC(m_hwnd, m_device);
                DestroyWindow(m_hwnd);

                throw CRS_EXCEPTION("Failed to create the final rendering context!");
            }
            wglMakeCurrent(nullptr, nullptr);
            wglDeleteContext(temp_context);
            wglMakeCurrent(m_device, m_GLcontext);
        }

        gl_context_impl::~gl_context_impl() {
            if (m_GLcontext)
                wglDeleteContext(m_GLcontext);
            if (m_device)
                ReleaseDC(m_hwnd, m_device);
        }
    }
}