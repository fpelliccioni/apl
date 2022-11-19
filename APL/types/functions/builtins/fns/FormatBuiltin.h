#pragma once

#include <APL/Main.h>
#include <APL/Value.h>
#include <APL/arrs/ChrArr.h>
#include <APL/Builtin.h>
#include <string>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	using Value = APL::types::Value;
	using Builtin = APL::types::functions::Builtin;

	class FormatBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;



	  virtual std::shared_ptr<Value> call(std::shared_ptr<Value> w);

	protected:
		std::shared_ptr<FormatBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<FormatBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
