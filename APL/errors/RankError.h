#pragma once

#include <APL/errors/APLError.h>
#include <APL/types/Tokenable.h>
#include <APL/types/Callable.h>
#include <string>
#include <memory>

namespace APL::errors
{

    // using namespace APL::types;

    class RankError : public APLError
    {
      // public RankError(String s) {
      //   super(s);
      // }
  public:
      RankError(std::string const& s, std::shared_ptr<APL::types::Tokenable> fun);
      RankError(std::string const& s, std::shared_ptr<APL::types::Callable> fun, std::shared_ptr<APL::types::Tokenable> cause);

    protected:
        std::shared_ptr<RankError> shared_from_this() {
            return std::static_pointer_cast<RankError>(APL::errors::APLError::shared_from_this());
        }
    };
}
