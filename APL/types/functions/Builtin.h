#pragma once

#include <APL/Scope.h>
#include <APL/Fun.h>
#include <memory>

namespace APL::types::functions
{

	using Scope = APL::Scope;
	using Fun = APL::types::Fun;

	class Builtin : public Fun
	{
  protected:
	  Builtin(std::shared_ptr<Scope> sc);
	  Builtin();

	protected:
		std::shared_ptr<Builtin> shared_from_this()
		{
			return std::static_pointer_cast<Builtin>(APL::types::Fun::shared_from_this());
		}
	};
}
