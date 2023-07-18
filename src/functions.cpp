#include <plat/functions.hpp>
#include <utility>
#if  CRS_ISOS_WIN32
#    include <windows.h>
#endif

namespace crs {
    namespace plat {
#if CRS_ISOS_WIN32
        void resolution(_Detail::pairsz sz) {
            DEVMODE devMode{};
            devMode.dmSize       = sizeof(devMode);
            devMode.dmPelsWidth  = sz.first;
            devMode.dmPelsHeight = sz.second;
            devMode.dmBitsPerPel = 32;
            devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

            if (ChangeDisplaySettingsA(&devMode, 0) != DISP_CHANGE_SUCCESSFUL)
                throw "Failed to change resolution";
        }
        _Detail::pairsz resolution() {
            return std::make_pair(
                GetSystemMetrics(SM_CXSCREEN),
                GetSystemMetrics(SM_CYSCREEN));
        }
#endif
    }
}