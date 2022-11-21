#include <APL/CommaBarBuiltin.h>
#include <APL/CatBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using APL::types::Value = APL::types::APL::types::Value;
	using Builtin = APL::types::functions::Builtin;

	std::string CommaBarBuiltin::repr()
	{
	  return L"⍪";
	}

	std::shared_ptr<APL::types::Value> CommaBarBuiltin::call(std::shared_ptr<APL::types::Value> w)
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

	std::shared_ptr<APL::types::Value> CommaBarBuiltin::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  return CatBuiltin::cat(a, w, 0, shared_from_this());
	}
}
