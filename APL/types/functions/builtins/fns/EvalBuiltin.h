#pragma once

#include <APL/errors/DomainError.h>
#include <APL/Builtin.h>
#include <APL/Scope.h>
#include <APL/Value.h>
#include <APL/Obj.h>
#include <string>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	using namespace APL;
	using namespace APL::types;
	using namespace APL::types::functions;

	class EvalBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;

	  EvalBuiltin(std::shared_ptr<Scope> sc);

	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;
	  std::shared_ptr<Obj> callObj(std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;
	  std::shared_ptr<Obj> callObj(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	protected:
		std::shared_ptr<EvalBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<EvalBuiltin>(Builtin::shared_from_this());
		}
	};
}
