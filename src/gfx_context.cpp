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
        // 只有跨平台渲染 API 才受到该支持
        template class basic_gfx_context<gl_context_impl, opengl_config>;
#if defined VK_CONTEXT_IMPL
        template class basic_gfx_context<vk_context_impl, vulkan_config>;
#endif
        template<class GfxCtxT, class CfgT>
        basic_gfx_context<GfxCtxT, CfgT>::basic_gfx_context(CfgT cfg):
            m_inst(new GfxCtxT(cfg)) {}
        template<class GfxCtxT, class CtxCfgT>
        void basic_gfx_context<GfxCtxT, CtxCfgT>::init_on_handle(void* handle) {
            m_inst->init_on_handle(handle);
        }
        template<class GfxCtxT, typename CfgT>
        void basic_gfx_context<GfxCtxT, CfgT>::swap_buffers() {
            m_inst->swap_buffers();
        }
        template<class GfxCtxT, typename CfgT>
        void basic_gfx_context<GfxCtxT, CfgT>::clear_color(float r, float g, float b) {
            m_inst->clear_color(r,g,b);
        }
        template<class GfxCtxT, class CtxCfgT>
        basic_gfx_context<GfxCtxT, CtxCfgT>::~basic_gfx_context() {
            delete m_inst;
        };
    }
}
