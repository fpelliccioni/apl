#pragma once

#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/functions/Builtin.h>
#include <APL/types/Value.h>
#include <APL/types/Callable.h>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	using namespace APL::errors;
	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;


	class UTackBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;



	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> callInv(std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  static std::shared_ptr<Value> on(std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<Callable> blame);

	protected:
		std::shared_ptr<UTackBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<UTackBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
