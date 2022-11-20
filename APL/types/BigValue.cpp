#include <APL/types/BigValue.h>

namespace APL::types
{
	using DomainError = APL::errors::DomainError;
	using SingleItemArr = APL::types::arrs::SingleItemArr;
	using BigInteger = java::math::BigInteger;
const std::shared_ptr<BigValue> BigValue::ZERO = std::make_shared<BigValue>(java::math::BigInteger::ZERO);
const std::shared_ptr<BigValue> BigValue::ONE = std::make_shared<BigValue>(java::math::BigInteger::ONE);
const std::shared_ptr<BigValue> BigValue::MINUS_ONE = std::make_shared<BigValue>(static_cast<java::math::BigInteger>(-1));
const std::shared_ptr<BigValue> BigValue::TWO = std::make_shared<BigValue>(static_cast<java::math::BigInteger>(2));
const std::shared_ptr<java::math::BigInteger> BigValue::MAX_SAFE_DOUBLE = static_cast<java::math::BigInteger>(Num::MAX_SAFE_INT);

	BigValue::BigValue(std::shared_ptr<BigInteger> i) : i(i)
	{
	}

	BigValue::BigValue(double d) : i(bigint(d))
	{
	}

	BigValue::BigValue(int n) : i(static_cast<BigInteger>(n))
	{
	}

	BigValue::BigValue(long long n) : i(static_cast<BigInteger>(n))
	{
	}

	std::shared_ptr<BigInteger> BigValue::bigint(std::shared_ptr<Value> w)
	{
	  if (std::dynamic_pointer_cast<Num>(w) != nullptr)
	  {
		  return bigint((std::static_pointer_cast<Num>(w))->num);
	  }
	  if (std::dynamic_pointer_cast<BigValue>(w) != nullptr)
	  {
		  return (std::static_pointer_cast<BigValue>(w))->i;
	  }
	  throw DomainError(StringHelper::wstring_to_string(L"Using " + w->humanType(true) + L" as biginteger", w));
	}

	std::shared_ptr<BigInteger> BigValue::bigint(double d)
	{
	  if (std::abs(d) > Num::MAX_SAFE_INT)
	  {
		  throw DomainError(L"creating biginteger from possibly rounded value");
	  }
	  if (d % 1 != 0)
	  {
		  throw DomainError(L"creating biginteger from non-integer");
	  }
	  return static_cast<BigInteger>(static_cast<long long>(d));
	}

	std::shared_ptr<Value> BigValue::ofShape(std::vector<int> &sh)
	{
	  return SingleItemArr::maybe(shared_from_this(), sh);
	}

	std::wstring BigValue::toString()
	{
	  if (i->signum() == -1)
	  {
		  return L"¯" + i->negate() + L"L";
	  }
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
	  return i->toString() + L"L";
	}

	bool BigValue::equals(std::shared_ptr<Obj> o)
	{
	  return std::dynamic_pointer_cast<BigValue>(o) != nullptr && i->equals((std::static_pointer_cast<BigValue>(o))->i);
	}

	std::shared_ptr<Num> BigValue::num()
	{
	  return std::make_shared<Num>(i->doubleValue());
	}

	int BigValue::asInt()
	{
	  int n = i->intValue();
	  if (!static_cast<BigInteger>(n).equals(i))
	  {
		  throw DomainError(L"Using biginteger as integer", shared_from_this());
	  }
	  return n;
	}

	double BigValue::asDouble()
	{
	  if (i->abs()->compareTo(MAX_SAFE_DOUBLE) > 0)
	  {
		  throw DomainError(L"Using biginteger as double", shared_from_this());
	  }
	  return i->doubleValue();
	}

	int BigValue::hashCode()
	{
	  return i->hashCode();
	}

	std::shared_ptr<Value> BigValue::safePrototype()
	{
	  return ZERO;
	}

const std::shared_ptr<java::math::BigInteger> BigValue::MIN_INT = static_cast<java::math::BigInteger>(std::numeric_limits<int>::min());
const std::shared_ptr<java::math::BigInteger> BigValue::MAX_INT = static_cast<java::math::BigInteger>(std::numeric_limits<int>::max());

	int BigValue::safeInt(std::shared_ptr<BigInteger> b)
	{
	  if (b->signum() == -1)
	  {
		if (b->compareTo(MIN_INT) <= 0)
		{
			return std::numeric_limits<int>::min();
		}
	  }
	  else
	  {
		if (b->compareTo(MAX_INT) >= 0)
		{
			return std::numeric_limits<int>::max();
		}
	  }
	  return b->intValue();
	}

	long long BigValue::longValue()
	{
	  if (i->bitLength() > 64)
	  {
		  throw DomainError(L"Using a biginteger with more than 64 bits as long", shared_from_this());
	  }
	  return i->longValue();
	}
}
