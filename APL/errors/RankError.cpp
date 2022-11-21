#include <APL/RankError.h>

namespace APL::errors
{
    // using namespace APL::types;

    RankError::RankError(std::string const& s, std::shared_ptr<APL::types::Tokenable> fun) : APLError(s, fun)
    {
    }

    RankError::RankError(std::string const& s, std::shared_ptr<APL::types::Callable> fun, std::shared_ptr<APL::types::Tokenable> cause) : APLError(s, fun, cause)
    {
    }
}
