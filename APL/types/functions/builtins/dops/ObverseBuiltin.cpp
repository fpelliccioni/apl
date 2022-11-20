#include <APL/ObverseBuiltin.h>
#include <APL/types/Fun.h>

namespace APL::types::functions::builtins::dops
{
	using namespace APL::types;
	using namespace APL::types::functions;

	std::wstring ObverseBuiltin::repr()
	{
	  return L"⍫";
	}

	std::shared_ptr<Value> ObverseBuiltin::call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  return aaf->call(w);
	}

	std::shared_ptr<Value> ObverseBuiltin::call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  return aaf->call(a, w);
	}

	std::shared_ptr<Value> ObverseBuiltin::callInv(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w)
	{
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  return wwf->call(w);
	}

	std::shared_ptr<Value> ObverseBuiltin::callInvW(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  return wwf->call(a, w);
	}

	std::shared_ptr<Value> ObverseBuiltin::callInvA(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{ // fall-back to ⍶
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  return aaf->callInvA(a, w);
	}
}
