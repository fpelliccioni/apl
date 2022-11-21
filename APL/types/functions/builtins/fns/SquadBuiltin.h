#pragma once

#include <APL/types/functions/Builtin.h>
#include <APL/Scope.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	// using namespace APL;
	// using namespace APL::errors;
	// using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;


	class SquadBuiltin : public Builtin
	{
  public:
	  std::string repr() override;

	  SquadBuiltin(std::shared_ptr<Scope> sc);

	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;

	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	protected:
		std::shared_ptr<SquadBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<SquadBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
