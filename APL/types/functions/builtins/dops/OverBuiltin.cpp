#include <APL/OverBuiltin.h>
#include <APL/types/Arr.h>

namespace APL::types::functions::builtins::dops
{
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;
	using namespace APL::types::functions;
	using DepthBuiltin = APL::types::functions::builtins::fns::DepthBuiltin;

	std::wstring OverBuiltin::repr()
	{
	  return L"⍥";
	}

	std::shared_ptr<Value> OverBuiltin::call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  if (std::dynamic_pointer_cast<Value>(ww) != nullptr)
	  {
		int d = (std::static_pointer_cast<Value>(ww))->asInt();
		return on(derv, aaf, d, w);
	  }
	  else
	  {
		std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
		return aaf->call(wwf->call(w));
	  }
	}

	std::shared_ptr<Value> OverBuiltin::callInvW(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  std::shared_ptr<Fun> f = isFn(aa, L'⍶');
	  std::shared_ptr<Fun> g = isFn(ww, L'⍹');
	  return g->callInv(f->callInvW(g->call(a), w));
	}

	std::shared_ptr<Value> OverBuiltin::callInvA(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  std::shared_ptr<Fun> f = isFn(aa, L'⍶');
	  std::shared_ptr<Fun> g = isFn(ww, L'⍹');
	  return g->callInv(f->callInvA(a, g->call(w)));
	}

	std::shared_ptr<Value> OverBuiltin::on(std::shared_ptr<Fun> caller, std::shared_ptr<Fun> f, int d, std::shared_ptr<Value> w)
	{
	  int ld = DepthBuiltin::lazy(w);
	  if (ld == d || ld <= -d)
	  {
		int fd = DepthBuiltin::full(w);
		if (d > 0 && d != fd)
		{
			throw DomainError(caller + L": can't match a depth " + std::to_wstring(fd) + L" array", caller, w);
		}
		if (d <= fd)
		{
		  return f->call(w);
		}
	  }
	  if (d > 0 && ld < d)
	  {
		  throw DomainError(caller + L": can't match a depth " + std::to_wstring(DepthBuiltin::full(w)) + L" array", caller, w);
	  }
	  std::vector<std::shared_ptr<Value>> res(w->ia);
	  for (int i = 0; i < res.size(); i++)
	  {
		res[i] = on(caller, f, d, w[i]);
	  }
	  return Arr::createL(res, w->shape);
	}

	std::shared_ptr<Value> OverBuiltin::call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  return aaf->call(wwf->call(a), wwf->call(w));
	}
}
