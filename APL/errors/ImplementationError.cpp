#include <APL/ImplementationError.h>

namespace APL::errors
{
    // using namespace APL::types;

    ImplementationError::ImplementationError(std::string const& s) : APLError(s)
    {
    }

    ImplementationError::ImplementationError(std::string const& s, std::shared_ptr<APL::types::Tokenable> fun) : APLError(s, fun)
    {
    }

    ImplementationError::ImplementationError(std::string const& s, std::shared_ptr<APL::types::Callable> fun, std::shared_ptr<APL::types::Tokenable> cause) : APLError(s, fun, cause)
    {
    }

    ImplementationError::ImplementationError(std::runtime_error t) : APLError(t.what())
    {
      initCause(t);
    }
}
