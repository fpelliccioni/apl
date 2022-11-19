#pragma once

#include <APL/Scope.h>
#include <APL/functions/builtins/dops/AtBuiltin.h>
#include <APL/functions/builtins/fns/RShoeUBBuiltin.h>
#include <APL/Settable.h>
#include <APL/Variable.h>
#include <APL/Value.h>
#include <APL/Brackets.h>
#include <APL/Callable.h>
#include <APL/Obj.h>
#include <string>
#include <memory>

namespace APL::types::dimensions
{

	using Scope = APL::Scope;
	using namespace APL::types;

	class Pick : public Settable
	{
  private:
	  const std::shared_ptr<Variable> var;
	  const std::shared_ptr<Value> val;
	  const std::shared_ptr<Value> idx;
	  const int IO;
	  const std::shared_ptr<Brackets> obj;

  public:
	  Pick(std::shared_ptr<Variable> var, std::shared_ptr<Brackets> where, std::shared_ptr<Scope> sc);

	  void set(std::shared_ptr<Obj> v, std::shared_ptr<Callable> blame) override;

	  std::shared_ptr<Obj> get() override;

	  std::shared_ptr<Obj> getOrThis() override;

	  virtual std::wstring toString();

	protected:
		std::shared_ptr<Pick> shared_from_this()
		{
			return std::static_pointer_cast<Pick>(Settable::shared_from_this());
		}
	};
}
