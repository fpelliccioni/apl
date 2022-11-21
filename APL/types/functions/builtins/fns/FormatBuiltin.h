#pragma once

#include <APL/Main.h>
#include <APL/types/Value.h>
#include <APL/types/arrs/ChrArr.h>
#include <APL/types/functions/Builtin.h>
#include <string>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	using APL::types::Value = APL::types::APL::types::Value;
	using Builtin = APL::types::functions::Builtin;

	class FormatBuiltin : public Builtin
	{
  public:
	  std::string repr() override;



	  virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w);

	protected:
		std::shared_ptr<FormatBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<FormatBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
