#pragma once

#include <APL/errors/APLError.h>
#include <APL/types/Callable.h>
#include <APL/types/Tokenable.h>
#include <string>
#include <memory>

namespace APL::errors
{

    // using namespace APL::types;

    class IncorrectArgsError : public APLError
    {
  public:
      IncorrectArgsError(std::string const& s, std::shared_ptr<APL::types::Callable> fun, std::shared_ptr<APL::types::Tokenable> cause);

    protected:
        std::shared_ptr<IncorrectArgsError> shared_from_this() {
            return std::static_pointer_cast<IncorrectArgsError>(APL::errors::APLError::shared_from_this());
        }
    };
}
