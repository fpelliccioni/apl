#pragma once

#include <APL/types/Value.h>
#include <memory>

namespace APL::types::dimensions
{

    using APL::types::Value = APL::types::APL::types::Value;

    class DimMFn
    {
  public:
      virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w, int dim) = 0;
    };
}
