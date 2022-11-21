#include <APL/EvalBuiltin.h>
#include <APL/ArrFun.h>
#include <APL/Main.h>
#include <APL/types/Fun.h>

namespace APL::types::functions::builtins::fns
{
	// using namespace APL;
	using DomainError = APL::errors::DomainError;
	// using namespace APL::types;
	// using namespace APL::types::functions;

	std::string EvalBuiltin::repr()
	{
	  return L"⍎";
	}

	EvalBuiltin::EvalBuiltin(std::shared_ptr<Scope> sc) : Builtin(sc)
	{
	}

	std::shared_ptr<APL::types::Value> EvalBuiltin::call(std::shared_ptr<APL::types::Value> w)
	{
	  std::shared_ptr<APL::types::Obj> o = callObj(w);
	  if (std::dynamic_pointer_cast<APL::types::Value>(o) != nullptr)
	  {
		  return std::static_pointer_cast<APL::types::Value>(o);
	  }
	  throw DomainError(StringHelper::wstring_to_string(L"⍎: was expected to return an array, got " + o->humanType(true), shared_from_this()));
	}

	std::shared_ptr<APL::types::Obj> EvalBuiltin::callObj(std::shared_ptr<APL::types::Value> w)
	{
	  if (std::dynamic_pointer_cast<ArrFun>(w) != nullptr)
	  {
		  return (std::static_pointer_cast<ArrFun>(w))->obj();
	  }
	  return Main::exec(w->asString(), sc);
	}

	std::shared_ptr<APL::types::Value> EvalBuiltin::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  std::shared_ptr<APL::types::Obj> o = callObj(a, w);
	  if (std::dynamic_pointer_cast<APL::types::Value>(o) != nullptr)
	  {
		  return std::static_pointer_cast<APL::types::Value>(o);
	  }
	  throw DomainError(StringHelper::wstring_to_string(L"⍎: was expected to return an array, got " + o->humanType(true), shared_from_this()));
	}

	std::shared_ptr<APL::types::Obj> EvalBuiltin::callObj(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  if (std::dynamic_pointer_cast<ArrFun>(a) != nullptr)
	  {
		std::shared_ptr<APL::types::Obj> obj = (std::static_pointer_cast<ArrFun>(a))->obj();
		if (!(std::dynamic_pointer_cast<Fun>(obj) != nullptr))
		{
			throw DomainError(StringHelper::wstring_to_string(L"⍎: ⍺ must be `function, was " + obj->humanType(true), shared_from_this()));
		}
		return (std::static_pointer_cast<Fun>(obj))->callObj(w);
	  }
	  else
	  {
		throw DomainError(L"⍎: Expected ⍺ to be an arrayified function", shared_from_this(), a);
	  }
	}
}
