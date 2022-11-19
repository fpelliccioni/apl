#include <APL/TallyBuiltin.h>
#include <APL/Num.h>

namespace APL::types::functions::builtins::fns
{
	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	std::wstring TallyBuiltin::repr()
	{
	  return L"≢";
	}

	std::shared_ptr<Value> TallyBuiltin::call(std::shared_ptr<Value> w)
	{
	  if (w->rank == 0)
	  {
		  return Num::ONE;
	  }
	  return Num::of(w->shape[0]);
	}

	std::shared_ptr<Value> TallyBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return a->equals(w)? Num::ZERO : Num::ONE;
	}
}
