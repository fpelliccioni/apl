#include <APL/StarBuiltin.h>
#include <APL/LogBuiltin.h>
#include <APL/RootBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;
	using BigInteger = java::math::BigInteger;

	std::wstring StarBuiltin::repr()
	{
	  return L"*";
	}

const std::shared_ptr<NumMV> StarBuiltin::NF = std::make_shared<NumMVAnonymousInnerClass>();

	std::shared_ptr<Value> StarBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<Num> w)
	{
	  return Num::E->pow(w);
	}

	void StarBuiltin::NumMVAnonymousInnerClass::call(std::vector<double> &res, std::vector<double> &a)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = std::exp(a[i]);
	  }
	}

	std::shared_ptr<Value> StarBuiltin::call(std::shared_ptr<Value> w)
	{
	  return numM(NF, w);
	}

	std::shared_ptr<Value> StarBuiltin::callInv(std::shared_ptr<Value> w)
	{
	  return numM(LogBuiltin::NF, w);
	}

const std::shared_ptr<D_NNeN> StarBuiltin::DNF = std::make_shared<D_NNeNAnonymousInnerClass>();

	double StarBuiltin::D_NNeNAnonymousInnerClass::on(double a, double w)
	{
	  return std::pow(a, w);
	}

	void StarBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, double a, std::vector<double> &w)
	{
	  for (int i = 0; i < w.size(); i++)
	  {
		  res[i] = std::pow(a, w[i]);
	  }
	}

	void StarBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, double w)
	{
	  if (w == 2)
	  {
		  for (int i = 0; i < a.size(); i++)
		  {
			  res[i] = a[i] * a[i];
		  }
	  }
	  else
	  {
		  for (int i = 0; i < a.size(); i++)
		  {
			  res[i] = std::pow(a[i], w);
		  }
	  }
	}

	void StarBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = std::pow(a[i], w[i]);
	  }
	}

	std::shared_ptr<Value> StarBuiltin::D_NNeNAnonymousInnerClass::call(std::shared_ptr<BigValue> a, std::shared_ptr<BigValue> w)
	{
	  if (a->i->signum() == 0)
	  {
		  return BigValue::ZERO;
	  }
	  if (a->i->equals(BigInteger::ONE))
	  {
		  return BigValue::ONE;
	  }
	  if (a->i->equals(BigValue::MINUS_ONE->i))
	  {
		  return w->i->intValue() % 2 == 0? BigValue::ONE : BigValue::MINUS_ONE;
	  }
	  if (w->i->bitLength() > 30)
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"*: ⍵ too big to calculate (⍺ ≡ " + a + L"; ⍵ ≡ " + w + L")", w)); // otherwise intValue might ignore those!
	  }
	  return std::make_shared<BigValue>(a->i->pow(w->i->intValue()));
	}

	std::shared_ptr<Value> StarBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return numD(DNF, a, w);
	}

	std::shared_ptr<Value> StarBuiltin::callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return numD(LogBuiltin::DNF, a, w);
	}

	std::shared_ptr<Value> StarBuiltin::callInvA(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return numD(RootBuiltin::DNF, w, a);
	}
}
