#pragma once

#include <APL/types/arrs/HArr.h>
#include <APL/types/functions/Mop.h>
#include <APL/Scope.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/functions/DerivedMop.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::mops
{

	using namespace APL;
	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::functions;


	class KeyBuiltin : public Mop
	{
  public:
	  std::wstring repr() override;

	  KeyBuiltin(std::shared_ptr<Scope> sc);

	  std::shared_ptr<Value> call(std::shared_ptr<Obj> f, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv) override;
	  std::shared_ptr<Obj> callObj(std::shared_ptr<Obj> aa, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv) override;

	  std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv) override;

	protected:
		std::shared_ptr<KeyBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<KeyBuiltin>(Mop::shared_from_this());
		}
	};
}
