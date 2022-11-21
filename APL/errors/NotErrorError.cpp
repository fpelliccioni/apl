#include <APL/NotErrorError.h>

namespace APL::errors
{
    using Obj = APL::types::Obj;

    NotErrorError::NotErrorError(std::string const& msg, std::shared_ptr<APL::types::Obj> cause) : APLError(msg)
    {
      this->cause = cause;
    }
}
