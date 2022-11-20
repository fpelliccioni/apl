#pragma once

#include <APL/types/arrs/Rank0Arr.h>
#include <APL/types/functions/Mop.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/functions/DerivedMop.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::mops
{

	using namespace APL::types;
	using namespace APL::types::functions;

	class EachRight : public Mop
	{
  public:
	  std::wstring repr() override;

	  std::shared_ptr<Value> call(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv) override;

	  std::shared_ptr<Value> underW(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv) override;

	protected:
		std::shared_ptr<EachRight> shared_from_this()
		{
			return std::static_pointer_cast<EachRight>(Mop::shared_from_this());
		}
	};
}
