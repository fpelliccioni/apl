#include <APL/SemiUBBuiltin.h>
#include <APL/types/arrs/Shape1Arr.h>
#include <APL/types/Num.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/Char.h>
#include <APL/types/arrs/ChrArr.h>
#include <APL/types/Arr.h>

namespace APL::types::functions::builtins::fns
{
	using DomainError = APL::errors::DomainError;
	// using namespace APL::types;
	// using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;

	std::string SemiUBBuiltin::repr()
	{
	  return L"⍮";
	}

	std::shared_ptr<APL::types::Value> SemiUBBuiltin::call(std::shared_ptr<APL::types::Value> w)
	{
	  return std::make_shared<Shape1Arr>(w);
	}

	std::shared_ptr<APL::types::Value> SemiUBBuiltin::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  if (std::dynamic_pointer_cast<Num>(a) != nullptr && std::dynamic_pointer_cast<Num>(w) != nullptr)
	  {
		return std::make_shared<DoubleArr>(std::vector<double>{(std::static_pointer_cast<Num>(a))->num, (std::static_pointer_cast<Num>(w))->num});
	  }
	  if (std::dynamic_pointer_cast<Char>(a) != nullptr && std::dynamic_pointer_cast<Char>(w) != nullptr)
	  {
		return std::make_shared<APL::types::arrs::ChrArr>(StringHelper::toString((std::static_pointer_cast<Char>(a))->chr) + L"" + StringHelper::toString((std::static_pointer_cast<Char>(w))->chr));
	  }
	  return Arr::create(std::vector<std::shared_ptr<APL::types::Value>>{a, w});
	}

	std::shared_ptr<APL::types::Value> SemiUBBuiltin::callInv(std::shared_ptr<APL::types::Value> w)
	{
	  if (w->rank != 1 || w->shape[0] != 1)
	  {
		  throw DomainError(L"monadic ⍮⍣¯1 only works on shape 1 arrays", shared_from_this(), w);
	  }
	  return w->first();
	}

	std::shared_ptr<APL::types::Value> SemiUBBuiltin::callInvW(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  if (w->rank != 1 || w->shape[0] != 2)
	  {
		  throw DomainError(L"dyadic ⍮⍣¯1 only works on shape 2 arrays", shared_from_this(), w);
	  }
	  if (!w[0].equals(a))
	  {
		  throw DomainError(L"dyadic ⍮⍣¯1 expected ⍺≡⊃⍵", shared_from_this(), w);
	  }
	  return w[1];
	}

	std::shared_ptr<APL::types::Value> SemiUBBuiltin::callInvA(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  if (a->rank != 1 || a->shape[0] != 2)
	  {
		  throw DomainError(L"dyadic ⍮⍨⍣¯1 only works on shape 2 ⍺ arrays", shared_from_this(), a);
	  }
	  if (!a[1].equals(w))
	  {
		  throw DomainError(L"dyadic ⍮⍨⍣¯1 expected ⍵≡⊃⌽⍺", shared_from_this(), a);
	  }
	  return a[0];
	}
}
