#pragma once

#include <APL/errors/DomainError.h>
#include <APL/types/Value.h>
#include <APL/types/functions/Builtin.h>
#include <string>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	using APL::types::Value = APL::types::APL::types::Value;
	using Builtin = APL::types::functions::Builtin;

	class LTackBuiltin : public Builtin
	{
  public:
	  std::string repr() override;



	  virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w);
	  virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);

	  virtual std::shared_ptr<APL::types::Value> callInv(std::shared_ptr<APL::types::Value> w);
	  virtual std::shared_ptr<APL::types::Value> callInvW(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);
	  virtual std::shared_ptr<APL::types::Value> callInvA(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);

	protected:
		std::shared_ptr<LTackBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<LTackBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
