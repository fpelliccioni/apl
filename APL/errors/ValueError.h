#pragma once

#include <APL/errors/APLError.h>
#include <APL/types/Tokenable.h>
#include <APL/types/Callable.h>
#include <string>
#include <memory>

namespace APL::errors
{

    // using namespace APL::types;

    class ValueError : public APLError
    {
  public:
      ValueError(std::string const& s);
      ValueError(std::string const& s, std::shared_ptr<APL::types::Tokenable> fun);
      ValueError(std::string const& s, std::shared_ptr<APL::types::Callable> fun, std::shared_ptr<APL::types::Tokenable> cause);

    protected:
        std::shared_ptr<ValueError> shared_from_this() {
            return std::static_pointer_cast<ValueError>(APL::errors::APLError::shared_from_this());
        }
    };
}
