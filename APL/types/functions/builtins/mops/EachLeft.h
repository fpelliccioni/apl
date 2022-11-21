#pragma once

#include <APL/types/arrs/Rank0Arr.h>
#include <APL/types/functions/Mop.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/functions/DerivedMop.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::mops
{

    // using namespace APL::types;
    // using namespace APL::types::functions;

    class EachLeft : public Mop
    {
  public:
      std::string repr() override;

      std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv) override;

      std::shared_ptr<APL::types::Value> underW(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv) override;

    protected:
        std::shared_ptr<EachLeft> shared_from_this() {
            return std::static_pointer_cast<EachLeft>(Mop::shared_from_this());
        }
    };
}
