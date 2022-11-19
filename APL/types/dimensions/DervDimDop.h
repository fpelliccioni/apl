#pragma once

#include <APL/Scope.h>
#include <APL/errors/SyntaxError.h>
#include <APL/functions/Dop.h>
#include <APL/Obj.h>
#include <APL/Value.h>
#include <APL/functions/DerivedDop.h>
#include <string>
#include <optional>
#include <memory>

namespace APL::types::dimensions
{

	using Scope = APL::Scope;
	using namespace APL::types;
	using namespace APL::types::functions;

	class DervDimDop : public Dop
	{
  private:
	  const std::shared_ptr<Dop> f;
	  const int dim;

  public:
	  std::wstring repr() override;

	  DervDimDop(std::shared_ptr<Dop> f, std::optional<int> &dim, std::shared_ptr<Scope> sc);

	  std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv) override;

	  std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv) override;

	protected:
		std::shared_ptr<DervDimDop> shared_from_this()
		{
			return std::static_pointer_cast<DervDimDop>(Dop::shared_from_this());
		}
	};
}
