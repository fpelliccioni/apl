#pragma once

#include <APL/Main.h>
#include <APL/types/dimensions/DimMMop.h>
#include <APL/types/functions/Mop.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/functions/DerivedMop.h>
#include <APL/types/Fun.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::mops
{

	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using DimMMop = APL::types::dimensions::DimMMop;
	using namespace APL::types::functions;
	using namespace APL::types::functions::builtins::fns;

	class ReduceBuiltin : public Mop, public DimMMop
	{
  public:
	  std::wstring repr() override;



	  std::shared_ptr<Value> call(std::shared_ptr<Obj> f, std::shared_ptr<Value> w, int dim) override;

	  std::shared_ptr<Value> call(std::shared_ptr<Obj> f, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv) override;

	  std::shared_ptr<Value> call(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv) override;

  private:
	  std::shared_ptr<Value> ngnReduce(std::shared_ptr<Value> x, int axis, std::shared_ptr<Fun> f);

	protected:
		std::shared_ptr<ReduceBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<ReduceBuiltin>(Mop::shared_from_this());
		}
	};
}
