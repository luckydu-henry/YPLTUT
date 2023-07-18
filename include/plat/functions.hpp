#pragma once
#include "config.hpp"
namespace crs {
    namespace plat {
        // 这个函数可以改变屏幕分辨率
        void            resolution(_Detail::pairsz, std::size_t depth);
        // 这个函数可以获取屏幕当前的分辨率
        _Detail::pairsz resolution();
    }
}