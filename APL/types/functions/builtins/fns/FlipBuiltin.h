#pragma once

#include <APL/errors/DomainError.h>
#include <APL/types/functions/Builtin.h>
#include <APL/types/dimensions/DimDFn.h>
#include <APL/types/dimensions/DimMFn.h>
#include <APL/types/Value.h>
#include <APL/types/dimensions/DervDimFn.h>
#include <string>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	// using namespace APL::types;
	// using namespace APL::types::dimensions;
	using Builtin = APL::types::functions::Builtin;

	class FlipBuiltin : public Builtin, public DimMFn, public DimDFn
	{
  public:
	  std::string repr() override;


	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w, int dim) override;
	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;
	  std::shared_ptr<APL::types::Value> callInv(std::shared_ptr<APL::types::Value> w) override;

	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DervDimFn> dims) override;

	  std::shared_ptr<APL::types::Value> callInvW(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	protected:
		std::shared_ptr<FlipBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<FlipBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
