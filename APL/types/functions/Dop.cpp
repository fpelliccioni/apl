#include <APL/Dop.h>
#include <APL/errors/IncorrectArgsError.h>
#include <APL/errors/DomainError.h>
#include <APL/errors/SyntaxError.h>

namespace APL::types::functions
{
	using namespace APL;
	using namespace APL::errors;
	using namespace APL::types;

	Dop::Dop(std::shared_ptr<Scope> sc) : Callable(sc)
	{
	}

	Dop::Dop() : Callable(nullptr)
	{
	}

	APL::Type Dop::type()
	{
	  return Type::dop;
	}

	std::shared_ptr<DerivedDop> Dop::derive(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww)
	{
	  return std::make_shared<DerivedDop>(aa, ww, shared_from_this());
	}

	std::shared_ptr<Value> Dop::call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  throw IncorrectArgsError(StringHelper::wstring_to_string(repr() + L" can't be called monadically", derv, w));
	}

	std::shared_ptr<Value> Dop::call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  throw IncorrectArgsError(StringHelper::wstring_to_string(repr() + L" can't be called dyadically", derv, a));
	}

	std::shared_ptr<Obj> Dop::callObj(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv)
	{ // if overridden, call(aa, ww, w, derv) must be overridden too!
	  return call(aa, ww, w, derv);
	}

	std::shared_ptr<Obj> Dop::callObj(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv)
	{ // if overridden, call(aa, ww, a, w, derv) must be overridden too!
	  return call(aa, ww, a, w, derv);
	}

	std::shared_ptr<Value> Dop::callInv(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w)
	{
	  throw DomainError(shared_from_this() + L" doesn't support monadic inverting", shared_from_this(), w);
	}

	std::shared_ptr<Value> Dop::callInvW(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  throw DomainError(shared_from_this() + L" doesn't support dyadic inverting of ⍵", shared_from_this(), w);
	}

	std::shared_ptr<Value> Dop::callInvA(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  throw DomainError(shared_from_this() + L" doesn't support dyadic inverting of ⍺", shared_from_this(), w);
	}

	std::shared_ptr<Value> Dop::under(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Obj> o, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  std::shared_ptr<Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(aa, ww, w, derv)) : std::static_pointer_cast<Value>(o);
	  return callInv(aa, ww, v);
	}

	std::shared_ptr<Value> Dop::underW(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  std::shared_ptr<Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(aa, ww, a, w, derv)) : std::static_pointer_cast<Value>(o);
	  return callInvW(aa, ww, a, v);
	}

	std::shared_ptr<Value> Dop::underA(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv)
	{
	  std::shared_ptr<Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(aa, ww, a, w, derv)) : std::static_pointer_cast<Value>(o);
	  return callInvA(aa, ww, v, w);
	}

	std::wstring Dop::toString()
	{
	  return repr();
	}

	std::shared_ptr<Fun> Dop::isFn(std::shared_ptr<Obj> o, wchar_t c)
	{
	  if (!(std::dynamic_pointer_cast<Fun>(o) != nullptr))
	  {
		  throw SyntaxError(StringHelper::wstring_to_string(repr() + L": " + StringHelper::toString(c) + L" must be a function", shared_from_this()));
	  }
	  return std::static_pointer_cast<Fun>(o);
	}

	int Dop::hashCode()
	{
	  return actualHashCode();
	}

	bool Dop::equals(std::shared_ptr<Obj> o)
	{
	  return shared_from_this() == o;
	}
}
