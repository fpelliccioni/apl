#pragma once

#include <APL/errors/SyntaxError.h>
#include <APL/types/functions/VarArr.h>
#include <APL/types/functions/builtins/AbstractSet.h>
#include <APL/types/Obj.h>
#include <APL/types/Fun.h>
#include <APL/types/Value.h>
#include <string>
#include <memory>

namespace APL::types::functions::builtins
{

    // using namespace APL::types;

    class SetBuiltin : public AbstractSet
    {
  public:
      static const std::shared_ptr<APL::types::functions::builtins::SetBuiltin> inst;

      std::string toString() override;




      std::shared_ptr<APL::types::Obj> callObj(std::shared_ptr<APL::types::Obj> a, std::shared_ptr<APL::types::Obj> w, bool update) override;

      virtual std::shared_ptr<APL::types::Obj> callObj(std::shared_ptr<Fun> f, std::shared_ptr<APL::types::Obj> a, std::shared_ptr<APL::types::Value> w);

    protected:
        std::shared_ptr<APL::types::functions::builtins::SetBuiltin> shared_from_this() {
            return std::static_pointer_cast<APL::types::functions::builtins::SetBuiltin>(AbstractSet::shared_from_this());
        }
    };
}
