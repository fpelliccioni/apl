#pragma once

#include <APL/Scope.h>
#include <APL/errors/SyntaxError.h>
#include <APL/types/functions/Dop.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/functions/DerivedDop.h>
#include <string>
#include <optional>
#include <memory>

namespace APL::types::dimensions
{

    using Scope = APL::Scope;
    // using namespace APL::types;
    // using namespace APL::types::functions;

    class DervDimDop : public Dop
    {
  private:
      const std::shared_ptr<Dop> f;
      const int dim;

  public:
      std::string repr() override;

      DervDimDop(std::shared_ptr<Dop> f, std::optional<int> &dim, std::shared_ptr<Scope> sc);

      std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv) override;

      std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv) override;

    protected:
        std::shared_ptr<DervDimDop> shared_from_this() {
            return std::static_pointer_cast<DervDimDop>(Dop::shared_from_this());
        }
    };
}
