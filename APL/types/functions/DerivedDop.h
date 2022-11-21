#pragma once

#include <APL/types/Fun.h>
// #include <APL/types/Obj.h>
#include <APL/types/functions/Dop.h>
#include <APL/types/Value.h>
#include <string>
#include <memory>

namespace APL::types {
class Obj;
}


namespace APL::types::functions
{

    // using namespace APL::types;

    class DerivedDop : public Fun
    {
  private:
      const std::shared_ptr<APL::types::Obj> aa, ww;
      const std::shared_ptr<Dop> op;
  public:
      DerivedDop(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<Dop> op);

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
        std::shared_ptr<DerivedDop> shared_from_this() {
            return std::static_pointer_cast<DerivedDop>(Fun::shared_from_this());
        }
    };
}
