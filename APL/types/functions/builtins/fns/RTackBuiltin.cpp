#include <APL/RTackBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using DomainError = APL::errors::DomainError;
	using Value = APL::types::Value;
	using Builtin = APL::types::functions::Builtin;

	std::wstring RTackBuiltin::repr()
	{
	  return L"⊢";
	}

	std::shared_ptr<Value> RTackBuiltin::call(std::shared_ptr<Value> w)
	{
		return w;
	}

	std::shared_ptr<Value> RTackBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
		return w;
	}

	std::shared_ptr<Value> RTackBuiltin::callInv(std::shared_ptr<Value> w)
	{
	  return w;
	}

	std::shared_ptr<Value> RTackBuiltin::callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return w;
	}

	std::shared_ptr<Value> RTackBuiltin::callInvA(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  throw DomainError(L"⊢⍨⍣¯1 is impossible", shared_from_this());
	}
}
