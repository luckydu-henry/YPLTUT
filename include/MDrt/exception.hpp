#pragma once
#include "config.hpp"
#include <exception>
#include <string>
#include <string_view>
#include <source_location>

namespace CRS {
    namespace MDrt {
        class exception : public std::exception {
        public:
            exception(std::source_location loc, std::string_view errStr) noexcept;
            const char* what() const noexcept;
            virtual ~exception() = default;
        protected:
            std::source_location m_location;
            mutable std::string  m_what;
        };
    }
}
// 宏可以让问题变简单
#define CRS_EXCEPTION(errStr) ::CRS::MDrt::exception(std::source_location::current(), errStr);