#include <pltut/d3d11context.h>

namespace yan {
    using namespace platform;

    win32_d3d11_rndr::win32_d3d11_rndr(int _Major, int _Minor) {}

    void win32_d3d11_rndr::init_on_handle(void* _Handle) {
        // Settings for swapchain.
        DXGI_SWAP_CHAIN_DESC swapDesc = {};
        swapDesc.BufferDesc.Width = 0;
        swapDesc.BufferDesc.Height = 0;
        swapDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        swapDesc.BufferDesc.RefreshRate.Numerator = 0;
        swapDesc.BufferDesc.RefreshRate.Denominator = 0;
        swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        swapDesc.SampleDesc.Count = 1;
        swapDesc.SampleDesc.Quality = 0;
        swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapDesc.BufferCount = 1;
        // Need to do a cast because param can't use platform specific.
        swapDesc.OutputWindow = static_cast<HWND>(_Handle);
        swapDesc.Windowed = true;
        swapDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
        swapDesc.Flags = 0;

        D3D11CTX_CHECK(D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            D3D11_CREATE_DEVICE_DEBUG,
            nullptr,
            0,
            D3D11_SDK_VERSION,
            &swapDesc,
            &_M_swap,
            &_M_device,
            nullptr,
            &_M_context
        ));

        Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer = nullptr;
        _M_swap->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
        _M_device->CreateRenderTargetView(
            pBackBuffer.Get(),
            nullptr,
            &_M_target
        );
    }

    void win32_d3d11_rndr::swap_frame(void) {
        _M_swap->Present(1u, 0u);
    }

    void win32_d3d11_rndr::clear_color(float R, float G, float B) {
        // Must use three scalar.
        const float color[] = { R, G, B, 1.0f };
        _M_context->ClearRenderTargetView(_M_target.Get(), color);
    }

    ///////////////////////////////////////////////////
    ////////////////// Error Handling /////////////////
    ///////////////////////////////////////////////////

    d3d11_exception::d3d11_exception(std::source_location _Loc, HRESULT hr) noexcept
        :yan::except(_Loc), _M_result(hr) {}

    const char* d3d11_exception::what() const noexcept {
        return _M_what.c_str();
    }

    std::string_view d3d11_exception::err_type() const noexcept {
        return "win32 d3d11 error";
    }

    void d3d11_exception::trans_hresult() {
        char* pMsgBuf = nullptr;
        DWORD nMsgLen = FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM
            | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr, _M_result, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
        );
        if (nMsgLen == 0) return;
        _M_what += pMsgBuf;
        LocalFree(pMsgBuf);
    }
}