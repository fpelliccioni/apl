#pragma once

#include <APL/types/functions/Builtin.h>
#include <APL/types/dimensions/DimDFn.h>
#include <APL/types/Value.h>
#include <APL/types/Tokenable.h>
#include <APL/types/dimensions/DervDimFn.h>
#include <APL/types/Callable.h>
#include <APL/types/Obj.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	// using namespace APL;
	// using namespace APL::errors;
	// using namespace APL::types;
	// using namespace APL::types::arrs;
	// using namespace APL::types::dimensions;
	using Builtin = APL::types::functions::Builtin;

	class UpArrowBuiltin : public Builtin, public DimDFn
	{
  public:
	  std::string repr() override;

	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;

	  static std::shared_ptr<APL::types::Value> merge(std::vector<std::shared_ptr<APL::types::Value>> &vals, std::vector<int> &sh, std::shared_ptr<APL::types::Tokenable> blame);




	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	  virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DervDimFn> dims);

	  static std::shared_ptr<APL::types::Value> on(std::vector<int> &sh, std::vector<int> &off, std::shared_ptr<APL::types::Value> w, std::shared_ptr<APL::types::Callable> blame);




	  std::shared_ptr<APL::types::Value> underW(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;
	  static std::shared_ptr<APL::types::Value> undo(std::vector<int> &e, std::shared_ptr<APL::types::Value> w, std::shared_ptr<APL::types::Value> origW, std::shared_ptr<APL::types::Callable> blame);

	protected:
		std::shared_ptr<UpArrowBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<UpArrowBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
