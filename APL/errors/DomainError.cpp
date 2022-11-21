#include <APL/DomainError.h>

namespace APL::errors
{
    // using namespace APL::types;

    DomainError::DomainError(std::string const& s) : APLError(s)
    {
    }

    DomainError::DomainError(std::string const& s, std::shared_ptr<APL::types::Tokenable> fun) : APLError(s, fun)
    {
    }

    DomainError::DomainError(std::string const& s, std::shared_ptr<APL::types::Callable> fun, std::shared_ptr<APL::types::Tokenable> cause) : APLError(s, fun, cause)
    {
    }
}
