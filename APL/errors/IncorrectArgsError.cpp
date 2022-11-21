#include <APL/IncorrectArgsError.h>

namespace APL::errors
{
    // using namespace APL::types;

    IncorrectArgsError::IncorrectArgsError(std::string const& s, std::shared_ptr<APL::types::Callable> fun, std::shared_ptr<APL::types::Tokenable> cause) : APLError(s, fun, cause)
    {
    }
}
