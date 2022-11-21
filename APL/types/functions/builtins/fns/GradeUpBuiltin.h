#pragma once

#include <APL/Scope.h>
#include <APL/types/Value.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/functions/Builtin.h>
#include <string>
#include <vector>
#include <optional>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	using Scope = APL::Scope;
	using APL::types::Value = APL::types::APL::types::Value;
	using Builtin = APL::types::functions::Builtin;

	class GradeUpBuiltin : public Builtin
	{
  public:
	  std::string repr() override;

	  GradeUpBuiltin(std::shared_ptr<Scope> sc);

	  virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w);

	  // TODO dyadic ⍋ & ⍒

	protected:
		std::shared_ptr<GradeUpBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<GradeUpBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
