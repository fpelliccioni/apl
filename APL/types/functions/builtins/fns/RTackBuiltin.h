#pragma once

#include <APL/errors/DomainError.h>
#include <APL/types/Value.h>
#include <APL/types/functions/Builtin.h>
#include <string>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	using Value = APL::types::Value;
	using Builtin = APL::types::functions::Builtin;

	class RTackBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;



	  virtual std::shared_ptr<Value> call(std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w);

	  virtual std::shared_ptr<Value> callInv(std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Value> callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Value> callInvA(std::shared_ptr<Value> a, std::shared_ptr<Value> w);

	protected:
		std::shared_ptr<RTackBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<RTackBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
