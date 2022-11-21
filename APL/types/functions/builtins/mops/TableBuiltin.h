#pragma once

#include <APL/types/functions/Mop.h>
// #include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/functions/DerivedMop.h>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

namespace APL::types {
class Obj;
}

namespace APL::types::functions::builtins::mops
{

    // using namespace APL::types;
    // using namespace APL::types::arrs;
    // using namespace APL::types::functions;

    class TableBuiltin final : public Mop
    {
  public:
      std::string repr() override;


      std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv) override;

    protected:
        std::shared_ptr<TableBuiltin> shared_from_this() {
            return std::static_pointer_cast<TableBuiltin>(Mop::shared_from_this());
        }
    };
}
