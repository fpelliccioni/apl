#pragma once

#include <APL/types/Value.h>
#include <memory>

namespace APL::types::dimensions
{

	using Value = APL::types::Value;

	class DimMFn
	{
  public:
	  virtual std::shared_ptr<Value> call(std::shared_ptr<Value> w, int dim) = 0;
	};
}
