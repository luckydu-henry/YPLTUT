#ifndef _WIN32_GL3_CONTEXT_H_
#define _WIN32_GL3_CONTEXT_H_

#include <pltut/context.h>
#include <pltut/except.h>

#include <Windows.h>
#include "wgl.h"

// global namespace.
namespace {
    // WGL attributues.
    constexpr unsigned int WGL_CONTEXT_MAJOR_VERSION_ARB              =  0x2091;
    constexpr unsigned int WGL_CONTEXT_MINOR_VERSION_ARB              =  0x2092;
    constexpr unsigned int WGL_CONTEXT_LAYER_PLANE_ARB                =  0x2093;
    constexpr unsigned int WGL_CONTEXT_FLAGS_ARB                      =  0x2094;
    constexpr unsigned int WGL_CONTEXT_PROFILE_MASK_ARB               =  0x9126;
    constexpr unsigned int WGL_CONTEXT_DEBUG_BIT_ARB                  =  0x0001;
    constexpr unsigned int WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB     =  0x0002;
    constexpr unsigned int WGL_CONTEXT_CORE_PROFILE_BIT_ARB           =  0x00000001;
    constexpr unsigned int WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB  =  0x00000002;
    constexpr unsigned int ERROR_INVALID_VERSION_ARB                  =  0x2095;
    constexpr unsigned int ERROR_INVALID_PROFILE_ARB                  =  0x2096;
}

namespace yan {

    class wgl_exception : public except {
    public:
        wgl_exception(std::source_location _Loc, std::string_view _des) noexcept;
    };

    namespace platform {

        class YAN_API win32_gl_rndr {
        public:
            win32_gl_rndr(int _Major, int _Minor);

            void        init_on_handle(void* _Handle)           ;
            void        swap_frame(void)                        ;
            void        clear_color(float R, float G, float B)  ;

            ~win32_gl_rndr();
        private:
            HWND       _M_hwnd;
            HDC        _M_device;
            HGLRC      _M_GLcontext;

            int _M_ajor, _M_inor;
        };
    }
}
#define WGL_EXCEPT(des) wgl_exception(std::source_location::current(), des)
#endif // !_WIN32_GL_CONTEXT_H_