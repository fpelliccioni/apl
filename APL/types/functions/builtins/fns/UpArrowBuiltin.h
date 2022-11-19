#pragma once

#include <APL/Builtin.h>
#include <APL/dimensions/DimDFn.h>
#include <APL/Value.h>
#include <APL/Tokenable.h>
#include <APL/dimensions/DervDimFn.h>
#include <APL/Callable.h>
#include <APL/Obj.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	using namespace APL;
	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using namespace APL::types::dimensions;
	using Builtin = APL::types::functions::Builtin;

	class UpArrowBuiltin : public Builtin, public DimDFn
	{
  public:
	  std::wstring repr() override;

	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  static std::shared_ptr<Value> merge(std::vector<std::shared_ptr<Value>> &vals, std::vector<int> &sh, std::shared_ptr<Tokenable> blame);




	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  virtual std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DervDimFn> dims);

	  static std::shared_ptr<Value> on(std::vector<int> &sh, std::vector<int> &off, std::shared_ptr<Value> w, std::shared_ptr<Callable> blame);




	  std::shared_ptr<Value> underW(std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;
	  static std::shared_ptr<Value> undo(std::vector<int> &e, std::shared_ptr<Value> w, std::shared_ptr<Value> origW, std::shared_ptr<Callable> blame);

	protected:
		std::shared_ptr<UpArrowBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<UpArrowBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
