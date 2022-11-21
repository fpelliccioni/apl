#pragma once

#include <APL/Main.h>
#include <APL/types/functions/Builtin.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	// using namespace APL::errors;
	// using namespace APL::types;
	// using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;


	class LShoeBuiltin : public Builtin
	{
  public:
	  std::string repr() override;



	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;
	  static std::shared_ptr<APL::types::Value> on(std::shared_ptr<APL::types::Value> w);

	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	protected:
		std::shared_ptr<LShoeBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<LShoeBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
