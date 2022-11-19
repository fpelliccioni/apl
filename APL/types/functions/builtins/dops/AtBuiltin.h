#pragma once

#include <APL/arrs/DoubleArr.h>
#include <APL/fns/RShoeUBBuiltin.h>
#include <APL/Dop.h>
#include <APL/Scope.h>
#include <APL/Obj.h>
#include <APL/Value.h>
#include <APL/DerivedDop.h>
#include <APL/Callable.h>
#include <APL/Indexer.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::dops
{

	using namespace APL;
	using namespace APL::types;
	using namespace APL::types::functions;

	class AtBuiltin : public Dop
	{
  public:
	  std::wstring repr() override;

	  AtBuiltin(std::shared_ptr<Scope> sc);

	  std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv) override;

	  static std::shared_ptr<Value> at(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, int IO, std::shared_ptr<Callable> blame);

	  static std::shared_ptr<Value> with(std::shared_ptr<Value> o, std::shared_ptr<Indexer::PosSh> poss, std::shared_ptr<Value> n, std::shared_ptr<Callable> blame);

	protected:
		std::shared_ptr<AtBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<AtBuiltin>(Dop::shared_from_this());
		}
	};
}
