#pragma once

#include <APL/errors/APLError.h>
#include <APL/types/Tokenable.h>
#include <APL/types/Callable.h>
#include <string>
#include <memory>

namespace APL::errors
{

    // using namespace APL::types;

    class NYIError : public APLError
    { // AKA LazyError
  public:
      NYIError(std::string const& s);
      NYIError(std::string const& s, std::shared_ptr<APL::types::Tokenable> fun);
      NYIError(std::string const& s, std::shared_ptr<APL::types::Callable> fun, std::shared_ptr<APL::types::Tokenable> cause);

    protected:
        std::shared_ptr<NYIError> shared_from_this() {
            return std::static_pointer_cast<NYIError>(APL::errors::APLError::shared_from_this());
        }
    };
}
