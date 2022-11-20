#include <APL/EllipsisBuiltin.h>
#include <APL/types/BigValue.h>
#include <APL/types/arrs/HArr.h>
#include <APL/types/arrs/DoubleArr.h>

namespace APL::types::functions::builtins::fns
{
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;
	using BigInteger = java::math::BigInteger;

	std::wstring EllipsisBuiltin::repr()
	{
	  return L"…";
	}

	std::shared_ptr<Value> EllipsisBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  if (std::dynamic_pointer_cast<BigValue>(a) != nullptr || std::dynamic_pointer_cast<BigValue>(w) != nullptr)
	  {
		std::shared_ptr<BigInteger> al = BigValue::bigint(a);
		std::shared_ptr<BigInteger> wl = BigValue::bigint(w);
		std::shared_ptr<BigInteger> size = al->subtract(wl).abs()->add(BigInteger::ONE);
		int isize = BigValue::safeInt(size);
		if (isize == std::numeric_limits<int>::max())
		{
			throw DomainError(StringHelper::wstring_to_string(L"…: expected range too large (" + a + L"…" + w + L")", shared_from_this(), w));
		}

		std::vector<std::shared_ptr<Value>> arr(isize);
		std::shared_ptr<BigInteger> c = al;
		std::shared_ptr<BigInteger> dir = al->compareTo(wl) < 0? BigInteger::ONE : BigValue::MINUS_ONE->i;
		for (int i = 0; i < isize; i++)
		{
		  arr[i] = std::make_shared<BigValue>(c);
		  c = c->add(dir);
		}
		return std::make_shared<HArr>(arr);
	  }
	  int ai = a->asInt();
	  int wi = w->asInt();
	  std::vector<double> arr(std::abs(ai - wi) + 1);
	  if (ai > wi)
	  {
		for (int i = 0; i < arr.size(); i++)
		{
		  arr[i] = ai - i;
		}
	  }
	  else
	  {
		for (int i = 0; i < arr.size(); i++)
		{
		  arr[i] = ai + i;
		}
	  }
	  return std::make_shared<DoubleArr>(arr);
	}
}
