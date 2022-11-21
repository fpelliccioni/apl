#pragma once

#include <APL/errors/APLError.h>
#include <APL/types/Tokenable.h>
#include <APL/types/Callable.h>
#include <string>
#include <memory>
#include <helpers/tangible_string_helper.h>

// using namespace APL::types;

namespace APL::errors {


class SyntaxError : public APLError
{
public:
    SyntaxError(std::string const& s);
    SyntaxError(std::string const& s, std::shared_ptr<APL::types::Tokenable> fun);
    SyntaxError(std::string const& s, std::shared_ptr<APL::types::Callable> fun, std::shared_ptr<APL::types::Tokenable> cause);

    static void must(bool b, std::string const& msg);

protected:
    std::shared_ptr<SyntaxError> shared_from_this()
    {
        return std::static_pointer_cast<SyntaxError>(APL::errors::APLError::shared_from_this());
    }
};

}
