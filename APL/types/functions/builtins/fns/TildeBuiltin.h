#pragma once

#include <APL/Main.h>
#include <APL/errors/DomainError.h>
#include <APL/types/functions/Builtin.h>
#include <APL/types/Value.h>
#include <APL/types/arrs/BitArr.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;

	class TildeBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;
	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> callInv(std::shared_ptr<Value> w) override;

  private:
	  std::shared_ptr<Value> rec(std::shared_ptr<Value> w);

  public:
	  static std::shared_ptr<BitArr> call(std::shared_ptr<BitArr> w);

	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	protected:
		std::shared_ptr<TildeBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<TildeBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
