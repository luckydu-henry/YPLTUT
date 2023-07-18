#pragma once
#include "config.hpp"
#include <exception>
#include <string>
#include <string_view>
#include <source_location>

namespace crs {
    namespace plat {
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
// �������������
#define CRS_EXCEPTION(errStr) ::crs::plat::exception(std::source_location::current(), errStr);