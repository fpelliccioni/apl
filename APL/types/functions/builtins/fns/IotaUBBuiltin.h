#pragma once

#include <APL/errors/DomainError.h>
#include <APL/types/functions/Builtin.h>
#include <APL/types/functions/builtins/mops/ReduceBuiltin.h>
#include <APL/types/Fun.h>
#include <APL/Scope.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_rectangular_vectors.h>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	// using namespace APL;
	// using namespace APL::types;
	// using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;
	using ReduceBuiltin = APL::types::functions::builtins::mops::ReduceBuiltin;

	class IotaUBBuiltin : public Builtin
	{
  private:
	  static const std::shared_ptr<Fun> fn;
  public:
	  std::string repr() override;

	  IotaUBBuiltin(std::shared_ptr<Scope> sc);
	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;
	  std::shared_ptr<APL::types::Value> callInv(std::shared_ptr<APL::types::Value> w) override;

	protected:
		std::shared_ptr<IotaUBBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<IotaUBBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
