#include <plat/gfx_context.hpp>
#include <exception>
#include <stdexcept>

#if     CRS_ISOS_WIN32
// Platform include.
#include "win32/gl3context.h"
#elif   CRS_ISOS_UNIX
#include "linux/gl3context.h"
#endif


namespace crs {
    namespace plat {
        template class basic_gfx_context<gl_context_impl, opengl_config>;
#if   defined VK_CONTEXT_IMPL
        template class basic_gfx_context<vk_context_impl, vulkan_config>;
#elif defined D3D11_CONTEXT_IMPL
        template class basic_gfx_context<d3d11_context_impl, d3d11_config>;
#elif defined METAL_CONTEXT_IMPL
        template class basic_gfx_context<metal_context_impl, metal_config>;
#endif

        template<class GfxCtxT, class CfgT>
        basic_gfx_context<GfxCtxT, CfgT>::basic_gfx_context(CfgT cfg)
            :m_inst(GfxCtxT(cfg)) {}
        template<class GfxCtxT, class CtxCfgT>
        void basic_gfx_context<GfxCtxT, CtxCfgT>::init_on_handle(void* handle) {
            m_inst.init_on_handle(handle);
        }
        template<class GfxCtxT, class CtxCfgT>
        basic_gfx_context<GfxCtxT, CtxCfgT>::~basic_gfx_context() = default;
    }
}
