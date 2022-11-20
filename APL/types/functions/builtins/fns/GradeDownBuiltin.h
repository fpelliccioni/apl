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
	using Value = APL::types::Value;
	using Builtin = APL::types::functions::Builtin;

	class GradeDownBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;

	  GradeDownBuiltin(std::shared_ptr<Scope> sc);

	  virtual std::shared_ptr<Value> call(std::shared_ptr<Value> w);

	protected:
		std::shared_ptr<GradeDownBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<GradeDownBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
