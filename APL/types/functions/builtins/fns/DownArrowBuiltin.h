#pragma once

#include <APL/Main.h>
#include <APL/Builtin.h>
#include <APL/dimensions/DimDFn.h>
#include <APL/Value.h>
#include <APL/dimensions/DervDimFn.h>
#include <APL/Obj.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using namespace APL::types::dimensions;
	using Builtin = APL::types::functions::Builtin;


	class DownArrowBuiltin : public Builtin, public DimDFn
	{
  public:
	  std::wstring repr() override;


	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  virtual std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DervDimFn> dims);

	  std::shared_ptr<Value> underW(std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> under(std::shared_ptr<Obj> o, std::shared_ptr<Value> w) override;

	protected:
		std::shared_ptr<DownArrowBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<DownArrowBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
