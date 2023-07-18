#pragma once
#include "config.hpp"
#include <variant>

namespace crs {
    namespace plat {
        // 这四个标识类是用来决定使用哪个 API 来运行
        struct vulkan_config { 
            std::size_t major, minor;
        };
        struct opengl_config { 
            std::size_t major, minor;
        };

        template <class GfxCtxT, typename CfgT>
        class basic_gfx_context {
            GfxCtxT* m_inst;
        public:

            basic_gfx_context(CfgT cfg);
            void init_on_handle(void*);
            void swap_buffers();
            void clear_color(float r, float g, float b);
            ~basic_gfx_context();
        };

        using gl_context    = basic_gfx_context<gl_context_impl, opengl_config>;
        using vk_context    = basic_gfx_context<vk_context_impl, vulkan_config>;
    }
} //! namespace crs.