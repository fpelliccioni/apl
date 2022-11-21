#pragma once

#include <APL/errors/DomainError.h>
#include <APL/types/functions/Builtin.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	// using namespace APL::types;
	// using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;


	class EllipsisBuiltin : public Builtin
	{
  public:
	  std::string repr() override;



	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	protected:
		std::shared_ptr<EllipsisBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<EllipsisBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
