#pragma once

#include <APL/types/Value.h>
#include <APL/types/functions/Builtin.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::fns {

// using Value = APL::types::Value;
// using Builtin = APL::types::functions::Builtin;

class CommaBarBuiltin : public Builtin
{
public:
    std::string repr() override;

    virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w);
    virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);

protected:
    std::shared_ptr<CommaBarBuiltin> shared_from_this() {
        return std::static_pointer_cast<CommaBarBuiltin>(APL::types::functions::Builtin::shared_from_this());
    }
};

}
