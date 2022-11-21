#pragma once

#include <APL/types/functions/Builtin.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <cmath>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	// using namespace APL::errors;
	// using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	class ExpandBuiltin : public Builtin
	{
  public:
	  std::string repr() override;

	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	protected:
		std::shared_ptr<ExpandBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<ExpandBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
