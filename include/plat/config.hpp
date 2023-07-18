#pragma once
#include <utility>
// Vulkan 是作为扩展渲染 API 的，因为不是所有平台都支持 Vulkan
#define USE_VULKAN false

#define CRS_ISOS_WIN32   false
#define CRS_ISOS_UNIX    false
#define CRS_ISOS_APPLE   false
#define CRS_ISOS_ANDROID false

#if     defined _WIN32 or _WIN64
#undef  CRS_ISOS_WIN32
#define CRS_ISOS_WIN32 true
#elif   defined __unix__
#undef  CRS_ISOS_UNIX
#define CRS_ISOS_UNIX true
#elif   defined __APPLE__
#undef  CRS_ISOS_APPLE
#define CRS_ISOS_APPLE true
#elif   defined __ANDROID__
#undef  CRS_ISOS_ANDROID
#define CRS_ISOS_ANDROID true
#endif

// 库版本使用的是日期来做标识
constexpr unsigned long long  CRS_plat_version = 202301L;

// 特别给 size_t & int 类型的 pair 准备的，因为这些非常常用
namespace _Detail { 
    using pairsz = std::pair<std::size_t, std::size_t>; 
    using pairi  = std::pair<std::int32_t, std::int32_t>;
}
// 命名空间内部声明了一些基础类，这些类通过特殊的“模板封装”技术来使用
// 无关平台的体验，接口也不是真正的接口，而是 C++20 特性下的"伪接口"
namespace crs {
    namespace plat {
        // 用来进行模板操作的窗口类型
        class win32_window;
        class x11_window;
        class cocoa_window;
        class android_window;
// 针对平台的预定义类型，也是当前平台默认hi用的
#if   CRS_ISOS_WIN32
        using plat_window = win32_window;
#elif CRS_ISOS_UNIX
        using plat_window = x11_window;
#elif CRS_ISOS_APPLE
        using plat_window = cocoa_window;
#elif CRS_ISOS_ANDROID
        using plat_window = android_window；
#endif
        // 渲染 API 类型，这些类型可以多个混合，但是必须是同一平台共同支持的。
        // 不然压根不能通过编译
        class gl_context_impl;
        class vk_context_impl;
    }
}
