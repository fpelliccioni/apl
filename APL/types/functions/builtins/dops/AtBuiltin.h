#pragma once

#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/functions/builtins/fns/RShoeUBBuiltin.h>
#include <APL/types/functions/Dop.h>
#include <APL/Scope.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/functions/DerivedDop.h>
#include <APL/types/Callable.h>
#include <APL/Indexer.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::dops
{

	// using namespace APL;
	// using namespace APL::types;
	// using namespace APL::types::functions;

	class AtBuiltin : public Dop
	{
  public:
	  std::string repr() override;

	  AtBuiltin(std::shared_ptr<Scope> sc);

	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv) override;

	  static std::shared_ptr<APL::types::Value> at(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> w, int IO, std::shared_ptr<APL::types::Callable> blame);

	  static std::shared_ptr<APL::types::Value> with(std::shared_ptr<APL::types::Value> o, std::shared_ptr<Indexer::PosSh> poss, std::shared_ptr<APL::types::Value> n, std::shared_ptr<APL::types::Callable> blame);

	protected:
		std::shared_ptr<AtBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<AtBuiltin>(Dop::shared_from_this());
		}
	};
}
