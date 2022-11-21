#pragma once

#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <memory>

namespace APL::types::dimensions
{

    // using namespace APL::types;

    class DimDMop
    {
  public:
      virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, int dim) = 0;
    };
}
