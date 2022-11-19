#pragma once

#include <APL/Builtin.h>
#include <APL/Scope.h>
#include <APL/Value.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	using namespace APL;
	using namespace APL::errors;
	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;


	class SquadBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;

	  SquadBuiltin(std::shared_ptr<Scope> sc);

	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	protected:
		std::shared_ptr<SquadBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<SquadBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
