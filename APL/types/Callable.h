#pragma once

// #include <APL/Scope.h>
#include <APL/types/Obj.h>
#include <memory>

// using Scope = APL::Scope;

namespace APL {
class Scope;
}


namespace APL::types {

class Callable : public APL::types::Obj {
public:
    const std::shared_ptr<Scope> sc;
protected:
    Callable(std::shared_ptr<Scope> sc);

protected:
    std::shared_ptr<Callable> shared_from_this()
    {
        return std::static_pointer_cast<Callable>(APL::types::Obj::shared_from_this());
    }
};

}
