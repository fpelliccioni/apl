#pragma once

#include <APL/errors/DomainError.h>
#include <APL/types/functions/builtins/fns/DepthBuiltin.h>
#include <APL/types/functions/Dop.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/functions/DerivedDop.h>
#include <APL/types/Fun.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::dops
{

	using namespace APL::types;
	using namespace APL::types::functions;

	class OverBuiltin : public Dop
	{
  public:
	  std::wstring repr() override;

	  std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv) override;
	  std::shared_ptr<Value> callInvW(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> callInvA(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  static std::shared_ptr<Value> on(std::shared_ptr<Fun> caller, std::shared_ptr<Fun> f, int d, std::shared_ptr<Value> w);
	  std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv) override;

	protected:
		std::shared_ptr<OverBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<OverBuiltin>(Dop::shared_from_this());
		}
	};
}
