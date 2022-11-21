//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/RepeatBuiltin.h>
#include <APL/Main.h>
#include <APL/types/Num.h>
#include <APL/errors/SyntaxError.h>
#include <APL/errors/DomainError.h>

namespace APL::types::functions::builtins::dops
{
	// using namespace APL;
	// using namespace APL::errors;
	// using namespace APL::types;
	// using namespace APL::types::functions;

	std::string RepeatBuiltin::repr()
	{
	  return L"⍣";
	}

	RepeatBuiltin::RepeatBuiltin(std::shared_ptr<Scope> sc) : Dop(sc)
	{
	}

	std::shared_ptr<APL::types::Value> RepeatBuiltin::call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  if (std::dynamic_pointer_cast<Fun>(ww) != nullptr)
	  {
		std::shared_ptr<Fun> g = std::static_pointer_cast<Fun>(ww);
		std::shared_ptr<APL::types::Value> prev = w;
		std::shared_ptr<APL::types::Value> curr = aaf->call(w);
		while (!Main::bool_Keyword(g->call(prev, curr)))
		{
		  std::shared_ptr<APL::types::Value> next = aaf->call(curr);
		  prev = curr;
		  curr = next;
		}
		return curr;
	  }
	  else
	  {
		if (!(std::dynamic_pointer_cast<Num>(ww) != nullptr))
		{
			throw SyntaxError(L"⍣: ⍹ must be either a function or scalar number");
		}
		int am = (std::static_pointer_cast<Num>(ww))->asInt();
		if (am < 0)
		{
		  for (int i = 0; i < -am; i++)
		  {
			w = aaf->callInv(w);
		  }
		}
		else
		{
			for (int i = 0; i < am; i++)
			{
		  w = aaf->call(w);
			}
		}
		return w;
	  }
	}

	std::shared_ptr<APL::types::Value> RepeatBuiltin::callInv(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> w)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  if (!(std::dynamic_pointer_cast<Num>(ww) != nullptr))
	  {
		  throw DomainError(L"(f⍣g)A cannot be inverted", shared_from_this());
	  }
	  int am = (std::static_pointer_cast<Num>(ww))->asInt();
	  if (am < 0)
	  {
		for (int i = 0; i < -am; i++)
		{
		  w = aaf->call(w);
		}
	  }
	  else
	  {
		  for (int i = 0; i < am; i++)
		  {
		w = aaf->callInv(w);
		  }
	  }
	  return w;
	}

	std::shared_ptr<APL::types::Value> RepeatBuiltin::call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  if (std::dynamic_pointer_cast<Fun>(ww) != nullptr)
	  {
		std::shared_ptr<Fun> g = std::static_pointer_cast<Fun>(ww);
		std::shared_ptr<APL::types::Value> prev = w;
		std::shared_ptr<APL::types::Value> curr = aaf->call(a, w);
		while (!Main::bool_Keyword(g->call(prev, curr)))
		{
		  std::shared_ptr<APL::types::Value> next = aaf->call(a, curr);
		  prev = curr;
		  curr = next;
		}
		return curr;
	  }
	  else
	  {
		if (!(std::dynamic_pointer_cast<Num>(ww) != nullptr))
		{
			throw SyntaxError(L"⍣: ⍹ must be either a function or scalar number");
		}
		int am = (std::static_pointer_cast<Num>(ww))->asInt();
		if (am < 0)
		{
		  for (int i = 0; i < -am; i++)
		  {
			w = aaf->callInvW(a, w);
		  }
		}
		else
		{
			for (int i = 0; i < am; i++)
			{
		  w = aaf->call(a, w);
			}
		}
		return w;
	  }
	}

	std::shared_ptr<APL::types::Value> RepeatBuiltin::callInvW(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  if (!(std::dynamic_pointer_cast<Num>(ww) != nullptr))
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"⍣: expected ⍹ to be a number, got " + ww->humanType(true), shared_from_this(), ww));
	  }
	  int am = (std::static_pointer_cast<Num>(ww))->asInt();
	  if (am < 0)
	  {
		for (int i = 0; i < -am; i++)
		{
		  w = aaf->call(a, w);
		}
	  }
	  else
	  {
		  for (int i = 0; i < am; i++)
		  {
		w = aaf->callInvW(a, w);
		  }
	  }
	  return w;
	}

	std::shared_ptr<APL::types::Value> RepeatBuiltin::callInvA(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  if (!(std::dynamic_pointer_cast<Num>(ww) != nullptr))
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"⍣: expected ⍹ to be a number, got " + ww->humanType(true), shared_from_this(), ww));
	  }
	  int am = (std::static_pointer_cast<Num>(ww))->asInt();
	  if (am == 1)
	  {
		  return aaf->callInvA(a, w);
	  }
	  if (am == -1)
	  {
		  return aaf->callInvA(w, a);
	  }

	  throw DomainError(L"f⍣N: ⍺-inverting is only possible when N∊¯1 1", shared_from_this(), ww);
	}

	std::shared_ptr<APL::types::Value> RepeatBuiltin::under(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  std::shared_ptr<Fun> aaf = isFn(aa, L'⍶');
	  if (!(std::dynamic_pointer_cast<APL::types::Value>(ww) != nullptr))
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"⍣: expected ⍹ to be a number, got " + ww->humanType(true), shared_from_this(), ww));
	  }
	  int n = (std::static_pointer_cast<APL::types::Value>(ww))->asInt();
	  return repeat(aaf, n, o, w);
	}

	std::shared_ptr<APL::types::Value> RepeatBuiltin::repeat(std::shared_ptr<Fun> aa, int n, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w)
	{ // todo don't do recursion?
	  if (n == 0)
	  {
		return std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(w) : std::static_pointer_cast<APL::types::Value>(o);
	  }

	  return repeat(aa, n - 1, std::make_shared<FunAnonymousInnerClass>(shared_from_this(), aa, o)
	 , w);
	}

	RepeatBuiltin::FunAnonymousInnerClass::FunAnonymousInnerClass(std::shared_ptr<RepeatBuiltin> outerInstance, std::shared_ptr<APL::types::Fun> aa, std::shared_ptr<APL::types::Obj> o) : outerInstance(outerInstance)
	{
		this->aa = aa;
		this->o = o;
	}

	std::string RepeatBuiltin::FunAnonymousInnerClass::repr()
	{
		return aa->repr();
	}

	std::shared_ptr<APL::types::Value> RepeatBuiltin::FunAnonymousInnerClass::call(std::shared_ptr<APL::types::Value> w)
	{
		return aa->under(o, w);
	}
}
