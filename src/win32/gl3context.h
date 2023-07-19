#pragma once
#define GL_CONTEXT_IMPL // 让 API 能够使用 OpenGL 实现

#include <MDrt/gfx_context.hpp>
#include <MDrt/exception.hpp>
#include <Windows.h>

// global namespace.
namespace {
    // WGL 扩展函数
    typedef HGLRC WINAPI wglCreateContextAttribsARB_type(HDC hdc, HGLRC hShareContext, const int* attribList);
    wglCreateContextAttribsARB_type* wglCreateContextAttribsARB;

    typedef BOOL  WINAPI wglChoosePixelFormatARB_type(HDC hdc,
                                                      const int* iattribList,
                                                      const FLOAT* fattribList,
                                                      UINT MaxFormats, int* iFormats, UINT* NumFormats);

    wglChoosePixelFormatARB_type*    wglChoosePixelFormatARB;
    // WGL 上下文常量
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
    // WGL 像素格式常量
    constexpr unsigned int WGL_NUMBER_PIXEL_FORMATS_ARB               =  0x2000;
    constexpr unsigned int WGL_DRAW_TO_WINDOW_ARB                     =  0x2001;
    constexpr unsigned int WGL_DRAW_TO_BITMAP_ARB                     =  0x2002;
    constexpr unsigned int WGL_ACCELERATION_ARB                       =  0x2003;
    constexpr unsigned int WGL_NEED_PALETTE_ARB                       =  0x2004;
    constexpr unsigned int WGL_NEED_SYSTEM_PALETTE_ARB                =  0x2005;
    constexpr unsigned int WGL_SWAP_LAYER_BUFFERS_ARB                 =  0x2006;
    constexpr unsigned int WGL_SWAP_METHOD_ARB                        =  0x2007;
    constexpr unsigned int WGL_NUMBER_OVERLAYS_ARB                    =  0x2008;
    constexpr unsigned int WGL_NUMBER_UNDERLAYS_ARB                   =  0x2009;
    constexpr unsigned int WGL_TRANSPARENT_ARB                        =  0x200A;
    constexpr unsigned int WGL_TRANSPARENT_RED_VALUE_ARB              =  0x2037;
    constexpr unsigned int WGL_TRANSPARENT_GREEN_VALUE_ARB            =  0x2038;
    constexpr unsigned int WGL_TRANSPARENT_BLUE_VALUE_ARB             =  0x2039;
    constexpr unsigned int WGL_TRANSPARENT_ALPHA_VALUE_ARB            =  0x203A;
    constexpr unsigned int WGL_TRANSPARENT_INDEX_VALUE_ARB            =  0x203B;
    constexpr unsigned int WGL_SHARE_DEPTH_ARB                        =  0x200C;
    constexpr unsigned int WGL_SHARE_STENCIL_ARB                      =  0x200D;
    constexpr unsigned int WGL_SHARE_ACCUM_ARB                        =  0x200E;
    constexpr unsigned int WGL_SUPPORT_GDI_ARB                        =  0x200F;
    constexpr unsigned int WGL_SUPPORT_OPENGL_ARB                     =  0x2010;
    constexpr unsigned int WGL_DOUBLE_BUFFER_ARB                      =  0x2011;
    constexpr unsigned int WGL_STEREO_ARB                             =  0x2012;
    constexpr unsigned int WGL_PIXEL_TYPE_ARB                         =  0x2013;
    constexpr unsigned int WGL_COLOR_BITS_ARB                         =  0x2014;
    constexpr unsigned int WGL_RED_BITS_ARB                           =  0x2015;
    constexpr unsigned int WGL_RED_SHIFT_ARB                          =  0x2016;
    constexpr unsigned int WGL_GREEN_BITS_ARB                         =  0x2017;
    constexpr unsigned int WGL_GREEN_SHIFT_ARB                        =  0x2018;
    constexpr unsigned int WGL_BLUE_BITS_ARB                          =  0x2019;
    constexpr unsigned int WGL_BLUE_SHIFT_ARB                         =  0x201A;
    constexpr unsigned int WGL_ALPHA_BITS_ARB                         =  0x201B;
    constexpr unsigned int WGL_ALPHA_SHIFT_ARB                        =  0x201C;
    constexpr unsigned int WGL_ACCUM_BITS_ARB                         =  0x201D;
    constexpr unsigned int WGL_ACCUM_RED_BITS_ARB                     =  0x201E;
    constexpr unsigned int WGL_ACCUM_GREEN_BITS_ARB                   =  0x201F;
    constexpr unsigned int WGL_ACCUM_BLUE_BITS_ARB                    =  0x2020;
    constexpr unsigned int WGL_ACCUM_ALPHA_BITS_ARB                   =  0x2021;
    constexpr unsigned int WGL_DEPTH_BITS_ARB                         =  0x2022;
    constexpr unsigned int WGL_STENCIL_BITS_ARB                       =  0x2023;
    constexpr unsigned int WGL_AUX_BUFFERS_ARB                        =  0x2024;

    constexpr unsigned int WGL_FULL_ACCELERATION_ARB                  = 0x2027;
    constexpr unsigned int WGL_TYPE_RGBA_ARB                          =  0x202B;
}

namespace CRS {
    namespace MDrt {
        class GL_context_impl {
        public:
            GL_context_impl(const OpenGL_config& cfg);
            void         init_on_handle(void*);
            void         swap_buffers();
            void         clear_color(float r, float g, float b);
            const char*  version();
            ~GL_context_impl();
        private:
            HWND          m_hwnd;
            HDC           m_device;
            HGLRC         m_GLcontext;
            // 版本号
            OpenGL_config m_cfg;
        };
    }
}