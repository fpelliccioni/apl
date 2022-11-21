#pragma once

#include <APL/Main.h>
#include <APL/types/functions/Builtin.h>
#include <APL/types/dimensions/DimDFn.h>
#include <APL/types/Value.h>
#include <APL/types/dimensions/DervDimFn.h>
#include <APL/types/Callable.h>
#include <APL/types/Obj.h>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::builtins::fns
{

	// using namespace APL::errors;
	// using namespace APL::types;
	// using namespace APL::types::arrs;
	// using namespace APL::types::dimensions;
	using Builtin = APL::types::functions::Builtin;


	class CatBuiltin : public Builtin, public DimDFn
	{
  public:
	  std::string repr() override;


	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;
	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;
	  virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DervDimFn> dims);

	  static std::shared_ptr<APL::types::Value> cat(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, int k, std::shared_ptr<APL::types::Callable> blame);
  private:
	  static void copyChunks(bool scalar, std::vector<std::shared_ptr<APL::types::Value>> &av, std::vector<std::shared_ptr<APL::types::Value>> &rv, int offset, int ad, int rd);

	  static void copyChunksD(bool scalar, std::vector<double> &av, std::vector<double> &rv, int offset, int ad, int rd);



  public:
	  std::shared_ptr<APL::types::Value> under(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w) override;

	  std::shared_ptr<APL::types::Value> underW(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	protected:
		std::shared_ptr<CatBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<CatBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
