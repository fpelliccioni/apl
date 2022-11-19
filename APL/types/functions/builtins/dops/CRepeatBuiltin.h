#pragma once

#include <APL/Dop.h>
#include <APL/Scope.h>
#include <APL/Obj.h>
#include <APL/Value.h>
#include <APL/DerivedDop.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::dops
{

	using namespace APL;
	using namespace APL::types;
	using namespace APL::types::functions;


	class CRepeatBuiltin : public Dop
	{
  public:
	  std::wstring repr() override;

	  CRepeatBuiltin(std::shared_ptr<Scope> sc);

	  std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv) override;

	protected:
		std::shared_ptr<CRepeatBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<CRepeatBuiltin>(Dop::shared_from_this());
		}
	};
}
