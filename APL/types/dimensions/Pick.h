#pragma once

#include <APL/Scope.h>
#include <APL/types/functions/builtins/dops/AtBuiltin.h>
#include <APL/types/functions/builtins/fns/RShoeUBBuiltin.h>
#include <APL/types/Settable.h>
#include <APL/types/Variable.h>
#include <APL/types/Value.h>
#include <APL/types/dimensions/Brackets.h>
#include <APL/types/Callable.h>
#include <APL/types/Obj.h>
#include <string>
#include <memory>

namespace APL::types::dimensions
{

    using Scope = APL::Scope;
    // using namespace APL::types;

    class Pick : public Settable
    {
  private:
      const std::shared_ptr<Variable> var;
      const std::shared_ptr<APL::types::Value> val;
      const std::shared_ptr<APL::types::Value> idx;
      const int IO;
      const std::shared_ptr<Brackets> obj;

  public:
      Pick(std::shared_ptr<Variable> var, std::shared_ptr<Brackets> where, std::shared_ptr<Scope> sc);

      void set(std::shared_ptr<APL::types::Obj> v, std::shared_ptr<APL::types::Callable> blame) override;

      std::shared_ptr<APL::types::Obj> get() override;

      std::shared_ptr<APL::types::Obj> getOrThis() override;

      virtual std::string toString();

    protected:
        std::shared_ptr<Pick> shared_from_this() {
            return std::static_pointer_cast<Pick>(Settable::shared_from_this());
        }
    };
}
