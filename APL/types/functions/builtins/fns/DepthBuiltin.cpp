#include <APL/types/functions/builtins/fns/DepthBuiltin.h>
#include <APL/types/Primitive.h>
#include <APL/types/arrs/BitArr.h>
#include <APL/types/arrs/ChrArr.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/Num.h>

namespace APL::types::functions::builtins::fns
{
	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;

	std::wstring DepthBuiltin::repr()
	{
	  return L"≡";
	}

	int DepthBuiltin::lazy(std::shared_ptr<Value> w)
	{
	  int depth = 0;
	  while (!(std::dynamic_pointer_cast<Primitive>(w) != nullptr))
	  {
		w = w->first();
		depth++;
	  }
	  return depth;
	}

	int DepthBuiltin::full(std::shared_ptr<Value> w)
	{
	  if (std::dynamic_pointer_cast<Primitive>(w) != nullptr)
	  {
		  return 0;
	  }
	  if (std::dynamic_pointer_cast<DoubleArr>(w) != nullptr || std::dynamic_pointer_cast<ChrArr>(w) != nullptr || std::dynamic_pointer_cast<BitArr>(w) != nullptr)
	  {
		  return 1;
	  }
	  bool first = true;
	  bool uneven = false;
	  int sub = 0;
	  for (auto v : w)
	  {
		int cd = full(v);
		if (cd < 0)
		{
		  uneven = true;
		  cd = -cd;
		}
		if (first)
		{
		  first = false;
		  sub = cd;
		}
		else if (sub != cd)
		{
		  sub = std::max(sub, cd);
		  uneven = true;
		}
	  }
	  sub++;
	  return uneven? -sub : sub;
	}

	std::shared_ptr<Value> DepthBuiltin::call(std::shared_ptr<Value> w)
	{
	  return Num::of(full(w));
	}

	std::shared_ptr<Value> DepthBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return a->equals(w)? Num::ONE : Num::ZERO;
	}
}
