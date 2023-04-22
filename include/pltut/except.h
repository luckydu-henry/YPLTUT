#ifndef _OMI_EXCEPTION_H_
#define _OMI_EXCEPTION_H_

#include "config.h"
#include <exception>
#include <string>
#include <string_view>
#include <source_location> // replace __FILE__ and __LINE__

namespace yan {
    class except : public std::exception {
    public:
        except(std::source_location _Loc) noexcept;

        virtual std::string_view      err_type() const noexcept;
        const char*                   what() const noexcept override;

        virtual ~except() noexcept = default;
    protected:
        std::source_location _M_location;
        mutable std::string  _M_what;
    };
}
#endif //!_OMI_EXCEPTION_H_