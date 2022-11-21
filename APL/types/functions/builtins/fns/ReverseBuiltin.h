#pragma once

#include <APL/types/functions/Builtin.h>
#include <APL/types/dimensions/DimDFn.h>
#include <APL/types/dimensions/DimMFn.h>
#include <APL/types/Value.h>
#include <APL/types/dimensions/DervDimFn.h>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	// using namespace APL::errors;
	// using namespace APL::types;
	// using namespace APL::types::arrs;
	// using namespace APL::types::dimensions;
	using Builtin = APL::types::functions::Builtin;

	class ReverseBuiltin : public Builtin, public DimMFn, public DimDFn
	{
  public:
	  std::string repr() override;


	  virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w, int dim);
	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;
	  static std::shared_ptr<APL::types::Value> on(std::shared_ptr<APL::types::Value> w);
	  std::shared_ptr<APL::types::Value> callInv(std::shared_ptr<APL::types::Value> w) override;


	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DervDimFn> dims) override;

	  std::shared_ptr<APL::types::Value> callInvW(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;



	  static std::shared_ptr<APL::types::Value> on(int a, int dim, std::shared_ptr<APL::types::Value> w);

	protected:
		std::shared_ptr<ReverseBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<ReverseBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
