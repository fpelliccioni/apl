#include <APL/ValueError.h>

namespace APL::errors
{
    // using namespace APL::types;

    ValueError::ValueError(std::string const& s) : APLError(s)
    {
    }

    ValueError::ValueError(std::string const& s, std::shared_ptr<APL::types::Tokenable> fun) : APLError(s, fun)
    {
    }

    ValueError::ValueError(std::string const& s, std::shared_ptr<APL::types::Callable> fun, std::shared_ptr<APL::types::Tokenable> cause) : APLError(s, fun, cause)
    {
    }
}
