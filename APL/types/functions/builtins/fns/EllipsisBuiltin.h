#pragma once

#include <APL/errors/DomainError.h>
#include <APL/Builtin.h>
#include <APL/Value.h>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;


	class EllipsisBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;



	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	protected:
		std::shared_ptr<EllipsisBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<EllipsisBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
