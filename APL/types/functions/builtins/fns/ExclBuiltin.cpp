#include <APL/ExclBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using DomainError = APL::errors::DomainError;
	// using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;
	// using BigInteger = java::math::BigInteger;

	std::string ExclBuiltin::repr()
	{
	  return L"!";
	}

const std::vector<double> ExclBuiltin::cache = std::vector<double>(172);

	ExclBuiltin::StaticConstructor::StaticConstructor()
	{
				double r = 1;
				cache[0] = cache[1] = r;
				for (int i = 2; i < 172; i++)
				{
	r *= i;
	cache[i] = r;
				}
	}

ExclBuiltin::StaticConstructor ExclBuiltin::staticConstructor;
const std::shared_ptr<NumMV> ExclBuiltin::NF = std::make_shared<NumMVAnonymousInnerClass>();

	std::shared_ptr<APL::types::Value> ExclBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<Num> w)
	{
	  return std::make_shared<Num>(cache[std::min(w->asInt(), 171)]);
	}

	void ExclBuiltin::NumMVAnonymousInnerClass::call(std::vector<double> &res, std::vector<double> &a)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		res[i] = cache[std::min(static_cast<int>(a[i]), 171)];
	  }
	}

	std::shared_ptr<APL::types::Value> ExclBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<APL::types::BigValue> w)
	{
	  if (w->i->bitLength() > 30)
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"!: argument too big (⍵ ≡ " + w + L")", w)); // otherwise intValue might ignore those!
	  }
	  int am = w->i->intValue();
	  std::shared_ptr<BigInteger> res = BigInteger::ONE;
	  for (int i = 2; i <= am; i++)
	  {
		res = res->multiply(static_cast<BigInteger>(i));
	  }
	  return std::make_shared<APL::types::BigValue>(res);
	}

	std::shared_ptr<APL::types::Value> ExclBuiltin::call(std::shared_ptr<APL::types::Value> w)
	{
	  return numM(NF, w);
	}

	std::shared_ptr<APL::types::Value> ExclBuiltin::call(std::shared_ptr<APL::types::Value> a0, std::shared_ptr<APL::types::Value> w0)
	{
	  return allD([&] (a, w)
	  {
	  if (std::dynamic_pointer_cast<APL::types::BigValue>(a) != nullptr || std::dynamic_pointer_cast<APL::types::BigValue>(w) != nullptr)
	  {
		  std::shared_ptr<BigInteger> res = BigInteger::ONE;
		  std::shared_ptr<BigInteger> al = APL::types::BigValue::bigint(w);
		  std::shared_ptr<BigInteger> bl = APL::types::BigValue::bigint(a);
		  if (al->compareTo(bl) < 0)
		  {
			  return Num::ZERO;
		  }
		  if (bl->compareTo(al->subtract(bl)) > 0)
		  {
			  bl = al->subtract(bl);
		  }
		  if (bl->bitLength() > 30)
		  {
			  throw DomainError(StringHelper::wstring_to_string(L"!: arguments too big (⍺ ≡ " + a + L"; ⍵ ≡ " + w + L")", w));
		  }
		  int ri = bl->intValue();
		  for (int i = 0; i < ri; i++)
		  {
			  res = res->multiply(al->subtract(static_cast<BigInteger>(i)));
		  }
		  for (int i = 0; i < ri; i++)
		  {
			  res = res->divide(static_cast<BigInteger>(i + 1));
		  }
		  return std::make_shared<APL::types::BigValue>(res);
	  }
	  return (std::static_pointer_cast<Num>(w))->binomial(std::static_pointer_cast<Num>(a));
	  }, a0, w0);
	}
}
