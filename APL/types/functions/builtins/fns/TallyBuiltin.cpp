#include <APL/TallyBuiltin.h>
#include <APL/types/Num.h>

namespace APL::types::functions::builtins::fns
{
	// using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	std::string TallyBuiltin::repr()
	{
	  return L"≢";
	}

	std::shared_ptr<APL::types::Value> TallyBuiltin::call(std::shared_ptr<APL::types::Value> w)
	{
	  if (w->rank == 0)
	  {
		  return Num::ONE;
	  }
	  return Num::of(w->shape[0]);
	}

	std::shared_ptr<APL::types::Value> TallyBuiltin::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  return a->equals(w)? Num::ZERO : Num::ONE;
	}
}
