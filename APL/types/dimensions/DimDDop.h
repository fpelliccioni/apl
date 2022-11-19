#pragma once

#include <APL/Obj.h>
#include <APL/Value.h>
#include <memory>

namespace APL::types::dimensions
{

	using namespace APL::types;

	class DimDDop
	{
  public:
	  virtual std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w, int dim) = 0;
	};
}
