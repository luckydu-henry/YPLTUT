#ifndef _YAN_CONTEXT_H_
#define _YAN_CONTEXT_H_

#include "config.h"

namespace yan {

    namespace platform {
        // platform and context list;
        class win32_gl_rndr;
        class win32_d3d11_rndr;
        class win32_vk_rndr;
        class x11_gl_rndr;
        class x11_vk_rndr;
#if   IS_PLATFORM_WIN32
        using plat_gl_rndr = win32_gl_rndr;
        using plat_vk_rndr = win32_vk_rndr;
#elif IS_PLATFORM_LINUX
        using plat_gl_rndr = x11_gl_rndr;
        using plat_vk_rndr = x11_vk_rndr;
#endif
    }

    template <class _Sub_rndr>
    class YAN_API basic_rndr_context {
        _Sub_rndr* _M_inst;
    public:

        basic_rndr_context(int _Major, int _Minor);
        basic_rndr_context(const basic_rndr_context<_Sub_rndr>&) = delete;
        basic_rndr_context(basic_rndr_context<_Sub_rndr>&&)      = delete;

        void        init_on_handle(void* _Handle);
        void        swap_frame(void);
        void        clear_color(float R, float G, float B);

        ~basic_rndr_context();
    };

    using gl_rndr_context = basic_rndr_context<platform::plat_gl_rndr>;
    using vk_rndr_context = basic_rndr_context<platform::plat_vk_rndr>;
    // platform specific renderer.
#if IS_PLATFORM_WIN32
    using pl_rndr_context = basic_rndr_context<platform::win32_d3d11_rndr>;
#endif

} //! namespace yan.
#endif // !_OMI_CONTEXT_H_