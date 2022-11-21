#pragma once

#include <APL/types/functions/builtins/mops/ReduceBuiltin.h>
#include <APL/types/functions/Dop.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/functions/DerivedDop.h>
#include <string>
#include <memory>

namespace APL::types::functions::builtins::dops
{

	// using namespace APL::types;
	// using namespace APL::types::functions;

	class DotBuiltin : public Dop
	{
  public:
	  std::string repr() override;

	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv) override;

	protected:
		std::shared_ptr<DotBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<DotBuiltin>(Dop::shared_from_this());
		}
	};
}
