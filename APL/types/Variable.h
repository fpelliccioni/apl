#pragma once

#include <APL/errors/ValueError.h>
#include <APL/types/Settable.h>
#include <APL/Scope.h>
#include <APL/types/Obj.h>
#include <APL/types/Callable.h>
#include <string>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types
{

	using namespace APL;

	class Variable : public Settable
	{

  private:
	  const std::shared_ptr<Scope> sc;
  public:
	  const std::wstring name;

	  Variable(std::shared_ptr<Scope> sc, const std::wstring &name);

	  std::shared_ptr<Obj> get() override;

	  void set(std::shared_ptr<Obj> v, std::shared_ptr<Callable> blame) override;
	  virtual void update(std::shared_ptr<Obj> v);

	  virtual std::wstring toString();

	protected:
		std::shared_ptr<Variable> shared_from_this()
		{
			return std::static_pointer_cast<Variable>(Settable::shared_from_this());
		}
	};
}
