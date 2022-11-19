#pragma once

#include <APL/Value.h>
#include <APL/DervDimFn.h>
#include <memory>

namespace APL::types::dimensions
{

	using Value = APL::types::Value;

	class DimDFn
	{
  public:
	  virtual std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DervDimFn> dim) = 0;
	};
}
