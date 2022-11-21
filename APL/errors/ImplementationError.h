#pragma once

#include <APL/errors/APLError.h>
#include <APL/types/Tokenable.h>
#include <APL/types/Callable.h>
#include <string>
#include <stdexcept>
#include <memory>

namespace APL::errors
{

    // using namespace APL::types;

    class ImplementationError : public APLError
    {
  public:
      ImplementationError(std::string const& s);
      ImplementationError(std::string const& s, std::shared_ptr<APL::types::Tokenable> fun);
      ImplementationError(std::string const& s, std::shared_ptr<APL::types::Callable> fun, std::shared_ptr<APL::types::Tokenable> cause);
      ImplementationError(std::runtime_error t);

    protected:
        std::shared_ptr<ImplementationError> shared_from_this() {
            return std::static_pointer_cast<ImplementationError>(APL::errors::APLError::shared_from_this());
        }
    };
}
