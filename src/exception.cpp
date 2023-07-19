#include <MDrt/exception.hpp>
#include <format>
namespace CRS {
    namespace MDrt {
        exception::exception(std::source_location loc, std::string_view errStr) noexcept:
        m_location(loc),
        m_what("") {
            m_what = std::format("[VER:{}|{}-{}-{}]{}",
                CRS_plat_version,
                m_location.file_name(),
                m_location.line(),
                m_location.function_name(),
                errStr);
        }
        const char* exception::what() const noexcept {
            return m_what.c_str();
        }
    }
}