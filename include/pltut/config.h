#ifndef _YAN_WINDOWAPI_CONFIG_
#define _YAN_WINDOWAPI_CONFIG_

#define IS_PLATFORM_WIN32   false
#define IS_PLATFORM_LINUX   false
#define IS_PLATFORM_APPLE   false
#define IS_PLATFORM_ANDROID false

#if defined _WIN32 || _WIN64
#define IS_PLATFORM_WIN32 true
#elif defined __linux__
#define IS_PLATFORM_LINUX true
#elif defined __APPLE__
#define IS_PLATFORM_APPLE true
#elif defined __ANDROID__
#define IS_PLATFORM_ANDROID true
#endif

// DEFAULT TO SHARED
#if not defined YAN_LIB_SHARED or not defined YAN_LIB_STATIC
#define YAN_LIB_SHARED
#endif

// LIB TYPE SPECIFIC.
#if defined YAN_LIB_SHARED
#    if IS_PLATFORM_WIN32
#    define YAN_API __declspec(dllexport)
#    else
#    define YAN_API
#    endif
#elif defined YAN_LIB_STATIC
#define YAN_API
#endif

// LIB VERSION -- DATE
constexpr unsigned long long  YAN_LIBVERSION = 202301L;

// WINDOW SPECIFICATION
namespace yan {
    namespace platform {
        class win32_window;
        class x11_window;
        class cocoa_window;
        class android_window;
#if   IS_PLATFORM_WIN32
        using plat_window = win32_window;
#elif IS_PLATFORM_LINUX
        using plat_window = x11_window;
#elif IS_PLATFORM_APPLE
        using plat_window = cocoa_window;
#elif IS_PLATFORM_ANDROID
        using plat_window = android_window£»
#endif
    }
}

#endif //!_YAN_WINDOWAPI_CONFIG_