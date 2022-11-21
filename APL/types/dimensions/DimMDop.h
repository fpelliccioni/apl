#pragma once

#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <memory>

namespace APL::types::dimensions
{

    // using namespace APL::types;

    class DimMDop
    {
  public:
      virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> w, int dim) = 0;
    };
}
