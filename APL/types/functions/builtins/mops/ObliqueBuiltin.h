#pragma once

#include <APL/fns/UpArrowBuiltin.h>
#include <APL/Mop.h>
#include <APL/Obj.h>
#include <APL/Value.h>
#include <APL/DerivedMop.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::mops
{

	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using namespace APL::types::functions;

	class ObliqueBuiltin : public Mop
	{
  public:
	  std::wstring repr() override;



	  std::shared_ptr<Value> call(std::shared_ptr<Obj> f, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv) override;

	protected:
		std::shared_ptr<ObliqueBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<ObliqueBuiltin>(Mop::shared_from_this());
		}
	};
}
