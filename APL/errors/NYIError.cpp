#include <APL/APL::errors::NYIError.h>

namespace APL::errors
{
    // using namespace APL::types;

    APL::errors::NYIError::APL::errors::NYIError(std::string const& s) : APLError(s)
    {
    }

    APL::errors::NYIError::APL::errors::NYIError(std::string const& s, std::shared_ptr<APL::types::Tokenable> fun) : APLError(s, fun)
    {
    }

    APL::errors::NYIError::APL::errors::NYIError(std::string const& s, std::shared_ptr<APL::types::Callable> fun, std::shared_ptr<APL::types::Tokenable> cause) : APLError(s, fun, cause)
    {
    }
}
