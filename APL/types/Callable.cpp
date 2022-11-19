#include <APL/Callable.h>

namespace APL::types
{
	using Scope = APL::Scope;

	Callable::Callable(std::shared_ptr<Scope> sc) : sc(sc)
	{
	}
}
