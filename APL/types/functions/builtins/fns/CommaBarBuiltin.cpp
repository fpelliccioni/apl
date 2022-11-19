#include <APL/CommaBarBuiltin.h>
#include <APL/CatBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using Value = APL::types::Value;
	using Builtin = APL::types::functions::Builtin;

	std::wstring CommaBarBuiltin::repr()
	{
	  return L"⍪";
	}

	std::shared_ptr<Value> CommaBarBuiltin::call(std::shared_ptr<Value> w)
	{
	  if (w->rank == 1)
	  {
		  return w->ofShape(std::vector<int>{w->shape[0], 1});
	  }
	  if (w->rank == 0)
	  {
		  return w->ofShape(std::vector<int>{1, 1});
	  }
	  int tsz = 1;
	  for (int i = 1; i < w->shape.size(); i++)
	  {
		  tsz *= w->shape[i];
	  }
	  return w->ofShape(std::vector<int>{w->shape[0], tsz});
	}

	std::shared_ptr<Value> CommaBarBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return CatBuiltin::cat(a, w, 0, shared_from_this());
	}
}
