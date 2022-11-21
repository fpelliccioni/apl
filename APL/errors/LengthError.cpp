#include <APL/LengthError.h>

namespace APL::errors
{
    // using namespace APL::types;

    LengthError::LengthError(std::string const& s, std::shared_ptr<APL::types::Tokenable> fun) : APLError(s, fun)
    {
    }

    LengthError::LengthError(std::string const& s, std::shared_ptr<APL::types::Callable> fun, std::shared_ptr<APL::types::Tokenable> cause) : APLError(s, fun, cause)
    {
    }
}
