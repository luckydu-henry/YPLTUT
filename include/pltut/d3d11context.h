# if defined _WIN32 || _WIN64
# pragma once

#include "context.h"
#include "except.h"

#include <Windows.h>
#include <d3d11.h>
#include <wrl.h> // for com pointers.

namespace yan {

    class d3d11_exception : public except {
        HRESULT _M_result;
    public:
        d3d11_exception(std::source_location _Loc, HRESULT hr) noexcept;

        const char* what() const noexcept override;
        std::string_view        err_type() const noexcept override;
        void                    trans_hresult();

        ~d3d11_exception() noexcept = default;
    };

    namespace platform {

        // On a win32 platform, inheritage this class to extend your own renderer
        class YAN_API win32_d3d11_rndr{

            win32_d3d11_rndr(const win32_d3d11_rndr&) = delete;
            win32_d3d11_rndr(win32_d3d11_rndr&&) = delete;
            win32_d3d11_rndr& operator=(const win32_d3d11_rndr&) = delete;
        public:
            win32_d3d11_rndr(int, int);

            void         init_on_handle(void* _Handle);
            void         swap_frame(void);
            void         clear_color(float R, float G, float B);

            virtual ~win32_d3d11_rndr() = default;
        protected:
            // Can be inheritage to support more functionality.
            // Check document.
            Microsoft::WRL::ComPtr<ID3D11Device>           _M_device;
            Microsoft::WRL::ComPtr<IDXGISwapChain>         _M_swap;
            Microsoft::WRL::ComPtr<ID3D11DeviceContext>    _M_context;
            Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _M_target;
        };
    }
}
// error macros
#define D3D11CTX_LASTERR()  d3d11_exception(std::source_location::current(), GetLastError())
#define D3D11CTX_CHECK(hr)  if (FAILED(hr)) throw D3D11CTX_LASTERR()

#endif //! _D3D11_CONTEXT_H_