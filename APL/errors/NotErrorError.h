#pragma once

#include <APL/types/Obj.h>
#include <APL/errors/APLError.h>
#include <string>
#include <memory>

namespace APL::errors
{

    using Obj = APL::types::Obj;

    class NotErrorError : public APLError
    {

  public:
      NotErrorError(std::string const& msg, std::shared_ptr<APL::types::Obj> cause);

    protected:
        std::shared_ptr<NotErrorError> shared_from_this() {
            return std::static_pointer_cast<NotErrorError>(APL::errors::APLError::shared_from_this());
        }
    };
}
