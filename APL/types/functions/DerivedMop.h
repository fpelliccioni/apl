#pragma once

#include <APL/types/functions/builtins/mops/TableBuiltin.h>
#include <APL/types/Fun.h>
// #include <APL/types/Obj.h>
#include <APL/types/functions/Mop.h>
#include <APL/types/Value.h>
#include <string>
#include <memory>

namespace APL::types {
class Obj;
}


namespace APL::types::functions
{

    // using namespace APL::types;

    class DerivedMop : public Fun
    {
  private:
      const std::shared_ptr<APL::types::Obj> aa;
      const std::shared_ptr<Mop> op;
  public:
      DerivedMop(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<Mop> op);

      std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;
      std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;
      std::shared_ptr<APL::types::Obj> callObj(std::shared_ptr<APL::types::Value> w) override;
      std::shared_ptr<APL::types::Obj> callObj(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;
      std::shared_ptr<APL::types::Value> callInv(std::shared_ptr<APL::types::Value> w) override;
      std::shared_ptr<APL::types::Value> callInvW(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;
      std::shared_ptr<APL::types::Value> callInvA(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

      std::string repr() override;

      std::shared_ptr<APL::types::Value> under(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w) override;
      std::shared_ptr<APL::types::Value> underW(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;
      std::shared_ptr<APL::types::Value> underA(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

    protected:
        std::shared_ptr<DerivedMop> shared_from_this() {
            return std::static_pointer_cast<DerivedMop>(Fun::shared_from_this());
        }
    };
}
