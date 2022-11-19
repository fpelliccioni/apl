#pragma once

#include <APL/Builtin.h>
#include <APL/Scope.h>
#include <APL/Value.h>
#include <APL/Callable.h>
#include <APL/Indexer.h>
#include <APL/Obj.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types::functions::builtins::fns
{

	using namespace APL;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;

	class RShoeUBBuiltin : public Builtin
	{
  public:
	  std::wstring repr() override;

	  RShoeUBBuiltin(std::shared_ptr<Scope> sc);

	  std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	  static std::shared_ptr<Value> on(std::shared_ptr<Value> a, std::shared_ptr<Value> w, int IO, std::shared_ptr<Callable> blame);

	  static std::shared_ptr<Value> on(std::shared_ptr<Indexer::PosSh> poss, std::shared_ptr<Value> w);

	  std::shared_ptr<Value> underW(std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w) override;

	protected:
		std::shared_ptr<RShoeUBBuiltin> shared_from_this()
		{
			return std::static_pointer_cast<RShoeUBBuiltin>(APL::types::functions::Builtin::shared_from_this());
		}
	};
}
