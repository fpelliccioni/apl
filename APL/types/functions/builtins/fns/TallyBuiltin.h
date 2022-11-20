#pragma once

#include <APL/types/functions/Builtin.h>
#include <APL/types/Value.h>
#include <string>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	class TallyBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;


	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	protected:
		std::shared_ptr<TallyBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<TallyBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
