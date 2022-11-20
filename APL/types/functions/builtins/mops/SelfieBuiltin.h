#pragma once

#include <APL/errors/DomainError.h>
#include <APL/types/functions/Mop.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/functions/DerivedMop.h>
#include <string>
#include <memory>

namespace APL::types::functions::builtins::mops
{

	using namespace APL::types;
	using namespace APL::types::functions;

	class SelfieBuiltin : public Mop
	{
  public:
	  std::wstring repr() override;



	  std::shared_ptr<Value> call(std::shared_ptr<Obj> f, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv) override;
	  std::shared_ptr<Value> call(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv) override;

	  std::shared_ptr<Value> callInvW(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> callInvA(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	protected:
		std::shared_ptr<SelfieBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<SelfieBuiltin>(Mop::shared_from_this());
		}
	};
}
