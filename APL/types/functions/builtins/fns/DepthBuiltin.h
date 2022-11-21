#pragma once

#include <APL/types/functions/Builtin.h>
#include <APL/types/Value.h>
#include <string>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	// using namespace APL::types;
	// using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;

	class DepthBuiltin : public Builtin
	{
  public:
	  std::string repr() override;


	  static int lazy(std::shared_ptr<APL::types::Value> w);
	  static int full(std::shared_ptr<APL::types::Value> w);

	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;
	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	protected:
		std::shared_ptr<DepthBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<DepthBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
