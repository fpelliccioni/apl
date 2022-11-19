#include <APL/DualBuiltin.h>

namespace APL::types::functions::builtins::dops
{
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;
	using namespace APL::types::functions;
	using InvertBuiltin = APL::types::functions::builtins::mops::InvertBuiltin;

	std::wstring DualBuiltin::repr()
	{
	  return L"⍢";
	}

	std::shared_ptr<Value> DualBuiltin::call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  return wwf->under(aa, w);
	}

	std::shared_ptr<Value> DualBuiltin::callInv(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  return wwf->under(InvertBuiltin::invertM(aaf), w);
	}

	std::shared_ptr<Value> DualBuiltin::call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  return wwf->under(std::make_shared<BindA>(wwf->call(a), aaf), w);
	}

	std::shared_ptr<Value> DualBuiltin::callInvW(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  return wwf->under(std::make_shared<BindA>(wwf->call(a), InvertBuiltin::invertW(aaf)), w);
	}

	std::shared_ptr<Value> DualBuiltin::callInvA(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{ // structural inverse is not possible; fall back to computational inverse
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  std::shared_ptr<Value> a1 = wwf->call(a);
	  std::shared_ptr<Value> w1 = wwf->call(w);
	  try
	  {
		return wwf->callInv(aaf->callInvA(a1, w1));
	  }
	  catch (const DomainError &e)
	  { // but add a nice warning about it if a plausible error was received (todo better error management to not require parsing the message?)
		std::wstring msg = e->what();
		if (msg.find(L"doesn't support") != std::wstring::npos && msg.find(L"inverting") != std::wstring::npos)
		{
		  throw DomainError(StringHelper::wstring_to_string(msg + L" (possibly caused by using f⍢g⍨⍣¯1, which only allows computational inverses)", e->cause));
		}
		throw e;
	  }
	}

	DualBuiltin::BindA::BindA(std::shared_ptr<Value> a, std::shared_ptr<Fun> f) : a(a), f(f)
	{
	}

	std::shared_ptr<Value> DualBuiltin::BindA::call(std::shared_ptr<Value> w)
	{
	  return f->call(a, w);
	}

	std::shared_ptr<Value> DualBuiltin::BindA::callInv(std::shared_ptr<Value> w)
	{
	  return f->callInvW(a, w);
	}

	std::wstring DualBuiltin::BindA::repr()
	{
	  return f->repr();
	}
}
