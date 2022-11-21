#pragma once

#include <APL/types/Value.h>
#include <APL/types/dimensions/DervDimFn.h>
#include <memory>

namespace APL::types::dimensions
{

    using APL::types::Value = APL::types::APL::types::Value;

    class DimDFn
    {
  public:
      virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DervDimFn> dim) = 0;
    };
}
