#pragma once

#include <APL/Scope.h>
#include <APL/errors/SyntaxError.h>
#include <APL/types/functions/Mop.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/functions/DerivedMop.h>
#include <string>
#include <optional>
#include <memory>

namespace APL::types::dimensions
{

    using Scope = APL::Scope;
    // using namespace APL::types;
    // using namespace APL::types::functions;

    class DervDimMop : public Mop
    {
  private:
      const std::shared_ptr<Mop> f;
      const int dim;

  public:
      DervDimMop(std::shared_ptr<Mop> f, std::optional<int> &dim, std::shared_ptr<Scope> sc);

      std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv) override;

      std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv) override;

      std::string repr() override;

    protected:
        std::shared_ptr<DervDimMop> shared_from_this() {
            return std::static_pointer_cast<DervDimMop>(Mop::shared_from_this());
        }
    };
}
