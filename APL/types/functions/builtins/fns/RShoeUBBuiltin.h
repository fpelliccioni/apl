#pragma once

#include <APL/types/functions/Builtin.h>
#include <APL/Scope.h>
#include <APL/types/Value.h>
#include <APL/types/Callable.h>
#include <APL/Indexer.h>
#include <APL/types/Obj.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	// using namespace APL;
	// using namespace APL::types;
	// using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;

	class RShoeUBBuiltin : public Builtin
	{
  public:
	  std::string repr() override;

	  RShoeUBBuiltin(std::shared_ptr<Scope> sc);

	  std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	  static std::shared_ptr<APL::types::Value> on(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, int IO, std::shared_ptr<APL::types::Callable> blame);

	  static std::shared_ptr<APL::types::Value> on(std::shared_ptr<Indexer::PosSh> poss, std::shared_ptr<APL::types::Value> w);

	  std::shared_ptr<APL::types::Value> underW(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

	protected:
		std::shared_ptr<RShoeUBBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<RShoeUBBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
