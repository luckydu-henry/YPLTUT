#pragma once
#define GL_CONTEXT_IMPL // 让 API 能够使用 OpenGL 实现

#include <plat/gfx_context.hpp>
#include <plat/exception.hpp>

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

namespace crs {
    namespace plat {
        class gl_context_impl {
        public:
            gl_context_impl(const opengl_config& cfg);
            void init_on_handle(void*);
            ~gl_context_impl();
        private:
            HWND       m_hwnd;
            HDC        m_device;
            HGLRC      m_GLcontext;
            // 版本号
            int m_major, m_minor;
        };
    }
}