#pragma once

#include <APL/errors/APLError.h>
#include <APL/types/Tokenable.h>
#include <APL/types/Callable.h>
#include <string>
#include <memory>

namespace APL::errors
{

    // using namespace APL::types;

    class LengthError : public APLError
    {
      // public LengthError(String s) {
      //   super(s);
      // }
  public:
      LengthError(std::string const& s, std::shared_ptr<APL::types::Tokenable> fun);
      LengthError(std::string const& s, std::shared_ptr<APL::types::Callable> fun, std::shared_ptr<APL::types::Tokenable> cause);

    protected:
        std::shared_ptr<LengthError> shared_from_this() {
            return std::static_pointer_cast<LengthError>(APL::errors::APLError::shared_from_this());
        }
    };
}
