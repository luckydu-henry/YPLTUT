#pragma once
#include "config.hpp"
#include <variant>

namespace crs {
    namespace plat {
        // 这四个标识类是用来决定使用哪个 API 来运行
        struct metal_config { static constexpr unsigned long long tag_id = 3; };
        struct vulkan_config { static constexpr unsigned long long tag_id = 1; };
        struct d3d11_config { static constexpr unsigned long long tag_id = 2; };
        struct opengl_config { 
            int major, minor;
        };

        template <class GfxCtxT, typename CfgT>
        class basic_gfx_context {
            GfxCtxT m_inst;
        public:

            basic_gfx_context(CfgT cfg);
            void init_on_handle(void*);
            ~basic_gfx_context();
        };

        using gl_context    = basic_gfx_context<gl_context_impl, opengl_config>;
        using vk_context    = basic_gfx_context<vk_context_impl, vulkan_config>;
#if    CRS_ISOS_WIN32
        using d3d11_context = basic_gfx_context<d3d11_context_impl, d3d11_config>;
#elif  CRS_ISOS_APPLE
        using metal_context = basic_gfx_context<metal_context_impl, metal_config>;
#endif
    }
} //! namespace crs.