#include <pltut/context.h>
#include <exception>
#include <stdexcept>

#if defined _WIN32
// Platform include.
#include <pltut/d3d11context.h>
#include "win32/gl3context.h"
#elif defined __linux__
#include "linux/gl3context.h"
#endif

#define SUPPORT_VULKAN 0

namespace yan {

    template class basic_rndr_context<platform::plat_gl_rndr>;
#if SUPPORT_VULKAN
    template class basic_rndr_context<platform::plat_vk_rndr>;
#endif
#if IS_PLATFORM_WIN32
    template class basic_rndr_context<platform::win32_d3d11_rndr>;
#endif

    template <class _Sub_rndr>
    basic_rndr_context<_Sub_rndr>::basic_rndr_context(int _Major, int _Minor)
        :_M_inst(new _Sub_rndr(_Major, _Minor)) {}

    template <class _Sub_rndr>
    void basic_rndr_context<_Sub_rndr>::init_on_handle(void* _Handle) {
        _M_inst->init_on_handle(_Handle);
    }
    template <class _Sub_rndr>
    void basic_rndr_context<_Sub_rndr>::clear_color(float R, float G, float B) {
        _M_inst->clear_color(R, G, B);
    }
    template <class _Sub_rndr>
    void basic_rndr_context<_Sub_rndr>::swap_frame() {
        _M_inst->swap_frame();
    }
    template <class _Sub_rndr>
    basic_rndr_context<_Sub_rndr>::~basic_rndr_context() {
        delete _M_inst;
    }
}
