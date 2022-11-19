#pragma once

#include <APL/Builtin.h>
#include <APL/Value.h>
#include <APL/Callable.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;


	class DTackBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;



	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> callInv(std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  static std::shared_ptr<Value> on(std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<Callable> blame);

	protected:
		std::shared_ptr<DTackBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<DTackBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
