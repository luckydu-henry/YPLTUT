#include "gl3context.h"

// global namespace.
namespace {
    // function ptr
    typedef GLXContext glXCreateContextAttribsARB_type(
                            Display *dpy,
                            GLXFBConfig config,
                            GLXContext share_context,
                            Bool direct,
                            const int *attrib_list);
    glXCreateContextAttribsARB_type* glXCreateContextAttribsARB;
}

namespace odk {
    using namespace platform;

    x11_gl_rndr::x11_gl_rndr(int _Major, int _Minor)
        :_M_major(_Major), _M_minor(_Minor), _M_ctx(nullptr), _M_handle(nullptr){}
    
    void x11_gl_rndr::init_on_handle(void* M_handle) {
        // Need to do some casting before actual operations.
        _M_handle = reinterpret_cast<x11_hwnd*>(M_handle);
    
        if (!gladLoaderLoadGLX(_M_handle->display, _M_handle->screen))
            throw GLX_EXCEPT("Faild to load GLX!");
    
        GLint glxAttribs[] = {
    		GLX_RGBA,
    		GLX_DOUBLEBUFFER,
    		GLX_DEPTH_SIZE,     24,
    		GLX_STENCIL_SIZE,   8,
    		GLX_RED_SIZE,       8,
    		GLX_GREEN_SIZE,     8,
    		GLX_BLUE_SIZE,      8,
    		GLX_SAMPLE_BUFFERS, 0,
    		GLX_SAMPLES,        0,
    		None
    	};
    
        if (_M_major < 3) {
            _M_handle->visualinfo = glXChooseVisual(_M_handle->display, _M_handle->screen, glxAttribs);
            GLXContext context = glXCreateContext(_M_handle->display, _M_handle->visualinfo, nullptr, true);
            if (!context)
                throw GLX_EXCEPT("Unable to create OpenGL context.");
            glXMakeCurrent(_M_handle->display, _M_handle->window, context);
            if (!gladLoaderLoadGL())
                throw GLX_EXCEPT("Unable to load GL function ptrs.");
            return;
        }
    }
    
    void x11_gl_rndr::clear_color(float R, float G, float B) {
        glClearColor(R, G, B, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void x11_gl_rndr::swap_frame(void) {
        glXSwapBuffers(_M_handle->display, _M_handle->window);
    }
    
    x11_gl_rndr::~x11_gl_rndr() {
        glXDestroyContext(_M_handle->display, _M_ctx);
    }

    ///////////////////
    // exception
    ///////////////////
    glx_exception::glx_exception(std::source_location _Loc, std::string_view _Descript)
        : except(_Loc) {
            _M_what += _Descript;
        }
    const char* glx_exception::what() const throw() {
        return _M_what.c_str();
    }
} // namespace odk.