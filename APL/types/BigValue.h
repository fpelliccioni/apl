#pragma once

#include <APL/errors/DomainError.h>
#include <APL/types/arrs/SingleItemArr.h>
#include <APL/types/Primitive.h>
#include <APL/types/Value.h>
#include <APL/types/Obj.h>
#include <APL/types/Num.h>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types
{


	using BigInteger = java::math::BigInteger;


	class BigValue : public Primitive
	{
  public:
	  static const std::shared_ptr<BigValue> ZERO;
	  static const std::shared_ptr<BigValue> ONE;
	  static const std::shared_ptr<BigValue> MINUS_ONE;
	  static const std::shared_ptr<BigValue> TWO;

	  static const std::shared_ptr<BigInteger> MAX_SAFE_DOUBLE;

	  const std::shared_ptr<BigInteger> i;
	  BigValue(std::shared_ptr<BigInteger> i);
	  BigValue(double d);
	  BigValue(int n);
	  BigValue(long long n);
	  static std::shared_ptr<BigInteger> bigint(std::shared_ptr<Value> w);
	  static std::shared_ptr<BigInteger> bigint(double d);

	  std::shared_ptr<Value> ofShape(std::vector<int> &sh) override;

	  virtual std::wstring toString();
	  virtual bool equals(std::shared_ptr<Obj> o);

	  virtual std::shared_ptr<Num> num();
	  int asInt() override;
	  double asDouble() override;
	  int hashCode() override;

	  std::shared_ptr<Value> safePrototype() override;
	  static const std::shared_ptr<BigInteger> MIN_INT;
	  static const std::shared_ptr<BigInteger> MAX_INT;
	  static int safeInt(std::shared_ptr<BigInteger> b);
	  virtual long long longValue();

	protected:
		std::shared_ptr<BigValue> shared_from_this()
		{
			return std::static_pointer_cast<BigValue>(Primitive::shared_from_this());
		}
	};
}
