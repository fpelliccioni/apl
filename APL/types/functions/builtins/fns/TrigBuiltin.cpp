#include <APL/TrigBuiltin.h>
#include <APL/errors/DomainError.h>
#include <APL/errors/NYIError.h>

namespace APL::types::functions::builtins::fns
{
	using namespace APL::errors;
	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	std::wstring TrigBuiltin::repr()
	{
	  return L"○";
	}

const std::shared_ptr<NumMV> TrigBuiltin::NF = std::make_shared<NumMVAnonymousInnerClass>();

	std::shared_ptr<Value> TrigBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<Num> w)
	{
	  return std::make_shared<Num>(w->num * M_PI);
	}

	void TrigBuiltin::NumMVAnonymousInnerClass::call(std::vector<double> &res, std::vector<double> &a)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = a[i] * M_PI;
	  }
	}

const std::shared_ptr<NumMV> TrigBuiltin::NFi = std::make_shared<NumMVAnonymousInnerClass2>();

	std::shared_ptr<Value> TrigBuiltin::NumMVAnonymousInnerClass2::call(std::shared_ptr<Num> w)
	{
	  return std::make_shared<Num>(w->num / M_PI);
	}

	void TrigBuiltin::NumMVAnonymousInnerClass2::call(std::vector<double> &res, std::vector<double> &a)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = a[i] / M_PI;
	  }
	}

	std::shared_ptr<Value> TrigBuiltin::call(std::shared_ptr<Value> w)
	{
	  return numM(NF, w);
	}

	std::shared_ptr<Value> TrigBuiltin::callInv(std::shared_ptr<Value> w)
	{
	  return numM(NFi, w);
	}

const std::shared_ptr<D_NNeN> TrigBuiltin::DNF = std::make_shared<D_NNeNAnonymousInnerClass>();

	double TrigBuiltin::D_NNeNAnonymousInnerClass::on(double a, double w)
	{
	  switch (static_cast<int>(a))
	  {
		case 1:
			return std::sin(w);
		case 2:
			return std::cos(w);
		case 3:
			return std::tan(w);
		case 4:
			return std::sqrt(w * w + 1);
		case 5:
			return std::sinh(w);
		case 6:
			return std::cosh(w);
		case 7:
			return std::tanh(w);
		case 8:
			return NAN; // pointless
		case 9:
			return w; // pointless
		case 10:
			return std::abs(w); // pointless
		case 11:
			return 0; // also pointless
		case 12:
			throw DomainError(L"what even is phase");

		case 0:
			return std::sqrt(1 - w * w); //Num.ONE.minus(n.pow(Num.TWO)).root(Num.TWO);
		case -1:
			return std::asin(w);
		case -2:
			return std::acos(w);
		case -3:
			return std::atan(w);
		case -4:
			return std::sqrt(w * w - 1);
		case -5:
			throw NYIError(L"inverse hyperbolic functions"); // return Math.asinh(w);
		case -6:
			throw NYIError(L"inverse hyperbolic functions"); // return Math.acosh(w);
		case -7:
			throw NYIError(L"inverse hyperbolic functions"); // return Math.atanh(w);
		case -8:
			return NAN; // pooointleeeessssss
		case -9:
			return w; // again, pointless pointless pointless
		case -10:
			return w;
		case -11:
			throw DomainError(L"no complex numbers :/");
		case -12:
			throw DomainError(L"no complex numbers no idea why this is even special-cased");
	  }
	  throw DomainError(L"○: ⍺ is out of bounds");
	}

	std::shared_ptr<Value> TrigBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return numD(DNF, a, w);
	}

const std::shared_ptr<D_NNeN> TrigBuiltin::DNFi = std::make_shared<D_NNeNAnonymousInnerClass2>();

	double TrigBuiltin::D_NNeNAnonymousInnerClass2::on(double a, double w)
	{
	  switch (static_cast<int>(a))
	  {
		case 1:
			return std::asin(w);
		case 2:
			return std::acos(w);
		case 3:
			return std::atan(w);

		case -1:
			return std::sin(w);
		case -2:
			return std::cos(w);
		case -3:
			return std::tan(w);
	  }
	  throw DomainError(L"○⍣¯1: ⍵ must be in (+,-)1…3");
	}

	std::shared_ptr<Value> TrigBuiltin::callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return numD(DNFi, a, w);
	}
}
