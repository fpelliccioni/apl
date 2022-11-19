#pragma once

#include <APL/errors/DomainError.h>
#include <APL/arrs/DoubleArr.h>
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
	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;


	class MergeBuiltin : public Builtin
	{

  public:
	  MergeBuiltin(std::shared_ptr<Scope> sc);

	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  std::wstring repr() override;

	protected:
		std::shared_ptr<MergeBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<MergeBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
