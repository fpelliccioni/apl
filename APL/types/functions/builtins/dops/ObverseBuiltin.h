#pragma once

#include <APL/types/functions/Dop.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/functions/DerivedDop.h>
#include <string>
#include <memory>

namespace APL::types::functions::builtins::dops
{

	using namespace APL::types;
	using namespace APL::types::functions;

	class ObverseBuiltin : public Dop
	{
  public:
	  std::wstring repr() override;


	  std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv) override;
	  std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv) override;

	  std::shared_ptr<Value> callInv(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> callInvW(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> callInvA(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	protected:
		std::shared_ptr<ObverseBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<ObverseBuiltin>(Dop::shared_from_this());
		}
	};
}
