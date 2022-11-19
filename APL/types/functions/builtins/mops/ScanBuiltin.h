#pragma once

#include <APL/Main.h>
#include <APL/arrs/DoubleArr.h>
#include <APL/Mop.h>
#include <APL/Obj.h>
#include <APL/Value.h>
#include <APL/DerivedMop.h>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::mops
{

	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::functions;

	class ScanBuiltin : public Mop
	{
  public:
	  std::wstring repr() override;

	  std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv) override;

	  std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv) override;

	protected:
		std::shared_ptr<ScanBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<ScanBuiltin>(Mop::shared_from_this());
		}
	};
}
