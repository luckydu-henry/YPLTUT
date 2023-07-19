#pragma once
#include "config.hpp"
#include <variant>

namespace CRS {
    namespace MDrt {
        // 这四个标识类是用来决定使用哪个 API 来运行
        struct vulkan_config { 
            std::size_t major, minor;
        };
        struct OpenGL_config { 
            typedef enum {
                // 这个给 flags
                DEBUG_BIT_ARB                 = 1,
                // 这个给 flags
                FORWARD_COMPATIBLE_BIT_ARB    = 2,
                // 这个给 mask
                CORE_PROFILE_BIT_ARB          = 1,
                // 这个给 mask
                COMPATIBILITY_PROFILE_BIT_ARB = 2
            } ctx_settings;

            int major, minor;
            // 上下文设置枚举可以应用到这两个变量
            ctx_settings flags, mask;
        };

        template <class GfxCtxT, typename CfgT>
        class basic_gfx_context {
            GfxCtxT* m_inst;
        public:

            basic_gfx_context(CfgT cfg);
            void        init_on_handle(void*);
            void        swap_buffers();
            void        clear_color(float r, float g, float b);
            const char* version();
            ~basic_gfx_context();
        };

        using GL_context    = basic_gfx_context<GL_context_impl, OpenGL_config>;
        using vk_context    = basic_gfx_context<vk_context_impl, vulkan_config>;
    }
} //! namespace CRS.