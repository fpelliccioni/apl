#pragma once

#include <APL/Settable.h>
#include <APL/Scope.h>
#include <APL/Callable.h>
#include <APL/Obj.h>
#include <APL/Type.h>
#include <string>
#include <memory>

namespace APL::types::functions::builtins
{

	using namespace APL;
	using namespace APL::types;

	class Quad : public Settable
	{
  private:
	  const std::shared_ptr<Scope> sc;
  public:
	  Quad(std::shared_ptr<Scope> sc);

	  void set(std::shared_ptr<Obj> v, std::shared_ptr<Callable> blame) override;

	  std::shared_ptr<Obj> get() override;
	  Type type() override;

	  std::wstring toString() override;

	protected:
		std::shared_ptr<Quad> shared_from_this()
		{
			return std::static_pointer_cast<Quad>(Settable::shared_from_this());
		}
	};
}
