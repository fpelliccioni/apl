#pragma once

#include <APL/Type.h>
#include <APL/types/Callable.h>
#include <APL/types/Obj.h>
#include <memory>

namespace APL::types::functions::builtins
{

	using Type = APL::Type;
	using namespace APL::types;

	class AbstractSet : public Callable
	{
  public:
	  AbstractSet();

	  virtual std::shared_ptr<Obj> callObj(std::shared_ptr<Obj> a, std::shared_ptr<Obj> w, bool update) = 0;

	  Type type() override;

	protected:
		std::shared_ptr<AbstractSet> shared_from_this()
		{
			return std::static_pointer_cast<AbstractSet>(Callable::shared_from_this());
		}
	};
}
