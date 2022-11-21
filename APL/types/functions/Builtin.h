#pragma once

//NOTE(fernando)
// #include <APL/Scope.h>
#include <APL/types/Fun.h>
#include <memory>

//NOTE(fernando)
namespace APL {
    class Scope;
}

namespace APL::types::functions {

    //NOTE(fernando)
    // using Scope = APL::Scope;
    // using Fun = APL::types::Fun;

class Builtin : public APL::types::Fun {
protected:
    Builtin(std::shared_ptr<Scope> sc);
    Builtin();

protected:
    std::shared_ptr<Builtin> shared_from_this()
    {
        return std::static_pointer_cast<Builtin>(APL::types::Fun::shared_from_this());
    }
};

}
