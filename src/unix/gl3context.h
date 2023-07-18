#ifndef _ODK_GLX_CONTEXT_
#define _ODK_GLX_CONTEXT_

#include <odk/windowapi/context.h>
#include <odk/windowapi/except.h>
#include "glx.h"
#include "header.h"

// glx enum
namespace {
    constexpr unsigned int GLX_CONTEXT_MAJOR_VERSION_ARB          = 0x2091;
    constexpr unsigned int GLX_CONTEXT_MINOR_VERSION_ARB          = 0x2092;
    constexpr unsigned int GLX_CONTEXT_FLAGS_ARB                  = 0x2094;
    constexpr unsigned int GLX_CONTEXT_PROFILE_MASK_ARB           = 0x9126;

    constexpr unsigned int GLX_CONTEXT_DEBUG_BIT_ARB              = 0x0001;
    constexpr unsigned int GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB = 0x0002;

    constexpr unsigned int GLX_CONTEXT_CORE_PROFILE_BIT_ARB          = 0x0001;
    constexpr unsigned int GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB = 0x0002;
}


namespace odk {
    class glx_exception : public except {
    public:
        glx_exception(std::source_location _Loc, std::string_view _Descript);

        const char* what() const throw() override;

        ~glx_exception() noexcept = default;
    };    
    namespace platform {
        class x11_gl_rndr {    
            x11_gl_rndr(const x11_gl_rndr&) = delete;
            x11_gl_rndr(x11_gl_rndr&&)      = delete;
        public:    
            x11_gl_rndr(int _Major, int _Minor);    

            void         init_on_handle(void* _Handle);
            void         swap_frame(void);
            void         clear_color(float R, float G, float B);    

            ~x11_gl_rndr();    
        private:
            int        _M_major, _M_minor;

            x11_hwnd*          _M_handle;
            GLXContext         _M_ctx;    
        };
    }
} // namespace odk.
#define GLX_EXCEPT(description) glx_exception(std::source_location::current(), description)
#endif //!_ODK_GLX_CONTEXT_