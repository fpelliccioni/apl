#pragma once

#include <APL/Obj.h>
#include <APL/Value.h>
#include <memory>

namespace APL::types::dimensions
{

	using namespace APL::types;

	class DimMMop
	{
  public:
	  virtual std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Value> w, int dim) = 0;
	};
}
