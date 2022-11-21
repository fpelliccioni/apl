#pragma once

#include <APL/types/functions/Dop.h>
#include <APL/Scope.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/functions/DerivedDop.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::dops
{

	// using namespace APL;
	// using namespace APL::types;
	// using namespace APL::types::functions;


	class CRepeatBuiltin : public Dop
	{
  public:
	  std::string repr() override;

	  CRepeatBuiltin(std::shared_ptr<Scope> sc);

	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv) override;

	protected:
		std::shared_ptr<CRepeatBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<CRepeatBuiltin>(Dop::shared_from_this());
		}
	};
}
