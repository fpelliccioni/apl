#pragma once

#include <APL/Scope.h>
#include <APL/types/Obj.h>
#include <memory>

namespace APL::types
{

	using Scope = APL::Scope;

	class Callable : public Obj
	{
  public:
	  const std::shared_ptr<Scope> sc;
  protected:
	  Callable(std::shared_ptr<Scope> sc);

	protected:
		std::shared_ptr<Callable> shared_from_this()
		{
			return std::static_pointer_cast<Callable>(Obj::shared_from_this());
		}
	};
}
