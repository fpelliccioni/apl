#pragma once

#include <APL/Builtin.h>
#include <APL/Value.h>
#include <string>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;

	class DepthBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;


	  static int lazy(std::shared_ptr<Value> w);
	  static int full(std::shared_ptr<Value> w);

	  std::shared_ptr<Value> call(std::shared_ptr<Value> w) override;
	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	protected:
		std::shared_ptr<DepthBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<DepthBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
