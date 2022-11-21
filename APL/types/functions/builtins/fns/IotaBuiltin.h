#pragma once

#include <APL/types/functions/Builtin.h>
#include <APL/Scope.h>
#include <APL/types/Value.h>
#include <APL/types/Callable.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <optional>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	// using namespace APL;
	// using namespace APL::errors;
	// using namespace APL::types;
	// using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;



	class IotaBuiltin : public Builtin
	{
  public:
	  std::string repr() override;

	  IotaBuiltin(std::shared_ptr<Scope> sc);

	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;

	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	  static std::shared_ptr<APL::types::Value> on(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, int IO, std::shared_ptr<APL::types::Callable> blame);

	protected:
		std::shared_ptr<IotaBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<IotaBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
