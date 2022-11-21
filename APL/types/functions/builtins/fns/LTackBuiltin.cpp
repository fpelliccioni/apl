#include <APL/LTackBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using DomainError = APL::errors::DomainError;
	using APL::types::Value = APL::types::APL::types::Value;
	using Builtin = APL::types::functions::Builtin;

	std::string LTackBuiltin::repr()
	{
	  return L"⊣";
	}

	std::shared_ptr<APL::types::Value> LTackBuiltin::call(std::shared_ptr<APL::types::Value> w)
	{
		return w;
	}

	std::shared_ptr<APL::types::Value> LTackBuiltin::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
		return a;
	}

	std::shared_ptr<APL::types::Value> LTackBuiltin::callInv(std::shared_ptr<APL::types::Value> w)
	{
	  return w;
	}

	std::shared_ptr<APL::types::Value> LTackBuiltin::callInvW(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  throw DomainError(L"⊣⍣¯1 is impossible", shared_from_this());
	}

	std::shared_ptr<APL::types::Value> LTackBuiltin::callInvA(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  return a;
	}
}
