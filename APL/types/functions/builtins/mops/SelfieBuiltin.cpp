#include <APL/SelfieBuiltin.h>
#include <APL/Fun.h>

namespace APL::types::functions::builtins::mops
{
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;
	using namespace APL::types::functions;

	std::wstring SelfieBuiltin::repr()
	{
	  return L"⍨";
	}

	std::shared_ptr<Value> SelfieBuiltin::call(std::shared_ptr<Obj> f, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv)
	{
	  if (std::dynamic_pointer_cast<Fun>(f) != nullptr)
	  {
		  return (std::static_pointer_cast<Fun>(f))->call(w, w);
	  }
	  return std::static_pointer_cast<Value>(f);
	}

	std::shared_ptr<Value> SelfieBuiltin::call(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedMop> derv)
	{
	  if (std::dynamic_pointer_cast<Fun>(f) != nullptr)
	  {
		  return (std::static_pointer_cast<Fun>(f))->call(w, a);
	  }
	  return std::static_pointer_cast<Value>(f);
	}

	std::shared_ptr<Value> SelfieBuiltin::callInvW(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  if (std::dynamic_pointer_cast<Fun>(f) != nullptr)
	  {
		  return (std::static_pointer_cast<Fun>(f))->callInvA(w, a);
	  }
	  throw DomainError(L"A⍨ cannot be inverted", shared_from_this());
	}

	std::shared_ptr<Value> SelfieBuiltin::callInvA(std::shared_ptr<Obj> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  if (std::dynamic_pointer_cast<Fun>(f) != nullptr)
	  {
		  return (std::static_pointer_cast<Fun>(f))->callInvW(w, a);
	  }
	  throw DomainError(L"A⍨ cannot be inverted", shared_from_this());
	}
}
