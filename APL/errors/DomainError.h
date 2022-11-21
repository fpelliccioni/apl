#pragma once

#include <APL/errors/APLError.h>
#include <APL/types/Tokenable.h>
// #include <APL/types/Callable.h>

#include <string>
#include <memory>

// using namespace APL::types;


namespace APL::types {
class Callable;
}


namespace APL::errors {

class DomainError : public APL::errors::APLError {
public:
    DomainError(std::string const& s);
    DomainError(std::string const& s, std::shared_ptr<APL::types::Tokenable> fun);
    DomainError(std::string const& s, std::shared_ptr<APL::types::Callable> fun, std::shared_ptr<APL::types::Tokenable> cause);

protected:
    std::shared_ptr<DomainError> shared_from_this()
    {
        return std::static_pointer_cast<DomainError>(APL::errors::APLError::shared_from_this());
    }
};

}
