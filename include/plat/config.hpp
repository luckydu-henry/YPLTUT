#pragma once
#include <utility>
// Vulkan ����Ϊ��չ��Ⱦ API �ģ���Ϊ��������ƽ̨��֧�� Vulkan
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

// ��汾ʹ�õ�������������ʶ
constexpr unsigned long long  CRS_plat_version = 202301L;

// �ر�� size_t & int ���͵� pair ׼���ģ���Ϊ��Щ�ǳ�����
namespace _Detail { 
    using pairsz = std::pair<std::size_t, std::size_t>; 
    using pairi  = std::pair<std::int32_t, std::int32_t>;
}
// �����ռ��ڲ�������һЩ�����࣬��Щ��ͨ������ġ�ģ���װ��������ʹ��
// �޹�ƽ̨�����飬�ӿ�Ҳ���������Ľӿڣ����� C++20 �����µ�"α�ӿ�"
namespace crs {
    namespace plat {
        // ��������ģ������Ĵ�������
        class win32_window;
        class x11_window;
        class cocoa_window;
        class android_window;
// ���ƽ̨��Ԥ�������ͣ�Ҳ�ǵ�ǰƽ̨Ĭ��hi�õ�
#if   CRS_ISOS_WIN32
        using plat_window = win32_window;
#elif CRS_ISOS_UNIX
        using plat_window = x11_window;
#elif CRS_ISOS_APPLE
        using plat_window = cocoa_window;
#elif CRS_ISOS_ANDROID
        using plat_window = android_window��
#endif
        // ��Ⱦ API ���ͣ���Щ���Ϳ��Զ����ϣ����Ǳ�����ͬһƽ̨��֧ͬ�ֵġ�
        // ��Ȼѹ������ͨ������
        class gl_context_impl;
        class vk_context_impl;
    }
}
