#include <APL/JotBuiltin.h>

namespace APL::types::functions::builtins::dops
{
	using SyntaxError = APL::errors::SyntaxError;
	using namespace APL::types;
	using namespace APL::types::functions;

	std::wstring JotBuiltin::repr()
	{
	  return L"∘";
	}

	std::shared_ptr<Value> JotBuiltin::call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  if (std::dynamic_pointer_cast<Fun>(ww) != nullptr)
	  {
		if (std::dynamic_pointer_cast<Fun>(aa) != nullptr)
		{
		  return (std::static_pointer_cast<Fun>(aa))->call((std::static_pointer_cast<Fun>(ww))->call(w));
		}
		else
		{
		  return (std::static_pointer_cast<Fun>(ww))->call(std::static_pointer_cast<Value>(aa), w);
		}
	  }
	  else
	  {
		if (std::dynamic_pointer_cast<Fun>(aa) != nullptr)
		{
			return (std::static_pointer_cast<Fun>(aa))->call(w, std::static_pointer_cast<Value>(ww));
		}
		throw SyntaxError(L"arr∘arr makes no sense", shared_from_this());
	  }
	}

	std::shared_ptr<Value> JotBuiltin::callInv(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w)
	{
	  if (std::dynamic_pointer_cast<Fun>(ww) != nullptr)
	  {
		if (std::dynamic_pointer_cast<Fun>(aa) != nullptr)
		{
		  return (std::static_pointer_cast<Fun>(ww))->callInv((std::static_pointer_cast<Fun>(aa))->callInv(w));
		}
		else
		{
		  return (std::static_pointer_cast<Fun>(ww))->callInvW(std::static_pointer_cast<Value>(aa), w);
		}
	  }
	  else
	  {
		if (std::dynamic_pointer_cast<Fun>(aa) != nullptr)
		{
			return (std::static_pointer_cast<Fun>(aa))->callInvA(w, std::static_pointer_cast<Value>(ww));
		}
		throw SyntaxError(L"arr∘arr makes no sense", shared_from_this());
	  }
	}

	std::shared_ptr<Value> JotBuiltin::call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  if (!(std::dynamic_pointer_cast<Fun>(aa) != nullptr))
	  {
		throw SyntaxError(StringHelper::wstring_to_string(L"operands of dyadically applied ∘ must be functions, but ⍶ is " + aa->humanType(true), shared_from_this(), aa));
	  }
	  if (!(std::dynamic_pointer_cast<Fun>(ww) != nullptr))
	  {
		throw SyntaxError(StringHelper::wstring_to_string(L"operands of dyadically applied ∘ must be functions, but ⍹ is " + ww->humanType(true), shared_from_this(), ww));
	  }
	  return (std::static_pointer_cast<Fun>(aa))->call(a, (std::static_pointer_cast<Fun>(ww))->call(w));
	}

	std::shared_ptr<Value> JotBuiltin::callInvW(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  return wwf->callInv(aaf->callInvW(a, w));
	}

	std::shared_ptr<Value> JotBuiltin::callInvA(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  std::shared_ptr<Fun> wwf = isFn(ww, L'⍹');
	  return aaf->callInvA(a, wwf->call(w));
	}

	std::shared_ptr<Value> JotBuiltin::under(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Obj> o, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  if (std::dynamic_pointer_cast<Fun>(ww) != nullptr)
	  {
		std::shared_ptr<Fun> wwf = std::static_pointer_cast<Fun>(ww);
		if (std::dynamic_pointer_cast<Fun>(aa) != nullptr)
		{
		  std::shared_ptr<Fun> gf = std::static_pointer_cast<Fun>(aa);
		  return wwf->under(std::make_shared<FunAnonymousInnerClass>(shared_from_this(), o, gf)
		 , w);
		}
		else
		{
		  return wwf->underW(o, std::static_pointer_cast<Value>(aa), w);
		}
	  }
	  else
	  {
		if (std::dynamic_pointer_cast<Fun>(aa) != nullptr)
		{
		  return (std::static_pointer_cast<Fun>(aa))->underA(o, w, std::static_pointer_cast<Value>(ww));
		}
		else
		{
		  throw SyntaxError(L"arr∘arr makes no sense", shared_from_this());
		}
	  }
	}

	JotBuiltin::FunAnonymousInnerClass::FunAnonymousInnerClass(std::shared_ptr<JotBuiltin> outerInstance, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Fun> gf) : outerInstance(outerInstance)
	{
		this->o = o;
		this->gf = gf;
	}

	std::wstring JotBuiltin::FunAnonymousInnerClass::repr()
	{
		return gf->repr();
	}

	std::shared_ptr<Value> JotBuiltin::FunAnonymousInnerClass::call(std::shared_ptr<Value> w)
	{
		return gf->under(o, w);
	}
}
