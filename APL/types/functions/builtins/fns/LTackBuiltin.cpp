#include <APL/LTackBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using DomainError = APL::errors::DomainError;
	using Value = APL::types::Value;
	using Builtin = APL::types::functions::Builtin;

	std::wstring LTackBuiltin::repr()
	{
	  return L"⊣";
	}

	std::shared_ptr<Value> LTackBuiltin::call(std::shared_ptr<Value> w)
	{
		return w;
	}

	std::shared_ptr<Value> LTackBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
		return a;
	}

	std::shared_ptr<Value> LTackBuiltin::callInv(std::shared_ptr<Value> w)
	{
	  return w;
	}

	std::shared_ptr<Value> LTackBuiltin::callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  throw DomainError(L"⊣⍣¯1 is impossible", shared_from_this());
	}

	std::shared_ptr<Value> LTackBuiltin::callInvA(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return a;
	}
}
