#include <pltut/except.h>

#if defined _MSC_VER
#include <format>
#elif defined __GNUC__
#include <sstream>
#endif

namespace yan {
    except::except(std::source_location _Loc) noexcept
        :_M_location(_Loc) { }
    const char* except::what() const noexcept {
#if defined _MSC_VER
        _M_what = std::format("[VER:{}|{}-{}-{}]",
            YAN_LIBVERSION,
            _M_location.file_name(),
            _M_location.line(),
            _M_location.function_name());
#elif defined __GNUC__
        std::stringstream ss;
        ss << '[' << "VER:" << YAN_LIBVERSION 
           << '|' << _M_location.file_name()
           << '-' << _M_location.line()
           << '-' << _M_location.function_name();
        _M_what = ss.str();
#endif        
        return _M_what.c_str();
    }
    std::string_view except::err_type() const noexcept {
        return "omi.windowapi error";
    }
}