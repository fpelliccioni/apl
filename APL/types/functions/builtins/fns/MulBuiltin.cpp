//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/MulBuiltin.h>
#include <APL/DivBuiltin.h>
#include <APL/types/Fun.h>

namespace APL::types::functions::builtins::fns
{
	using Main = APL::Main;
	using DomainError = APL::errors::DomainError;
	// using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;
	// using BigInteger = java::math::BigInteger;

	std::string MulBuiltin::repr()
	{
	  return L"×";
	}

	std::shared_ptr<APL::types::Value> MulBuiltin::identity()
	{
	  return Num::ONE;
	}

const std::shared_ptr<NumMV> MulBuiltin::NF = std::make_shared<NumMVAnonymousInnerClass>();

	std::shared_ptr<APL::types::Value> MulBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<Num> w)
	{
	  double d = w->num;
	  return d > 0? Num::ONE : d < 0? Num::MINUS_ONE : Num::ZERO;
	}

	void MulBuiltin::NumMVAnonymousInnerClass::call(std::vector<double> &res, std::vector<double> &a)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = a[i] > 0? 1 : a[i] < 0? -1 : 0;
	  }
	}

	std::shared_ptr<APL::types::Value> MulBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<APL::types::BigValue> w)
	{
	  return Num::of(w->i->signum());
	}

	std::shared_ptr<APL::types::Value> MulBuiltin::call(std::shared_ptr<APL::types::Value> w)
	{
	  return numChrMapM(NF, [&] (std::any c)
	  {
	  Num::of(c::getCase());
	  }, [&] (std::any c)
	  {
	  return c->size() > 0? Num::ONE : Num::ZERO;
		}, w);
	}

const std::shared_ptr<D_NNeN> MulBuiltin::DNF = std::make_shared<D_NNeNAnonymousInnerClass>();

	double MulBuiltin::D_NNeNAnonymousInnerClass::on(double a, double w)
	{
	  return a * w;
	}

	void MulBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, double a, std::vector<double> &w)
	{
	  for (int i = 0; i < w.size(); i++)
	  {
		  res[i] = a * w[i];
	  }
	}

	void MulBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, double w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = a[i] * w;
	  }
	}

	void MulBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = a[i] * w[i];
	  }
	}

	std::shared_ptr<APL::types::Value> MulBuiltin::D_NNeNAnonymousInnerClass::call(std::shared_ptr<APL::types::BigValue> a, std::shared_ptr<APL::types::BigValue> w)
	{
	  return std::make_shared<APL::types::BigValue>(a->i->multiply(w->i));
	}

	std::shared_ptr<APL::types::Value> MulBuiltin::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  return numD(DNF, a, w);
	}

	std::shared_ptr<APL::types::Value> MulBuiltin::callInvW(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  try
	  {
		return (std::make_shared<DivBuiltin>())->call(w, a);
	  }
	  catch (const DomainError &e)
	  {
		throw DomainError(e->what(), shared_from_this(), e->cause);
	  }
	}

	std::shared_ptr<APL::types::Value> MulBuiltin::callInvA(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  return callInvW(w, a);
	}

const std::shared_ptr<D_NNeN> MulBuiltin::SET_SGN = std::make_shared<D_NNeNAnonymousInnerClass2>();

	double MulBuiltin::D_NNeNAnonymousInnerClass2::on(double o, double n)
	{
	  if (n == 0)
	  {
		  return 0;
	  }
	  if (o == 0)
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"⍢×: cannot set sign of 0 to " + Num::format(n)));
	  }
	  if (n == 1)
	  {
		  return std::abs(o);
	  }
	  if (n == -1)
	  {
		  return -std::abs(o);
	  }
	  throw DomainError(StringHelper::wstring_to_string(L"⍢×: cannot set sign to " + std::to_wstring(n)));
	}

	void MulBuiltin::D_NNeNAnonymousInnerClass2::on(std::vector<double> &res, double o, std::vector<double> &n)
	{
	  for (int i = 0; i < res.size(); i++)
	  {
		double nc = n[i];
		if (o == 0 && nc != 0)
		{
			throw DomainError(StringHelper::wstring_to_string(L"⍢×: cannot set sign of 0 to " + Num::format(nc)));
		}
		if (nc == 0 || nc == 1 || nc == -1)
		{
			res[i] = std::abs(o) * nc;
		}
		else
		{
			throw DomainError(StringHelper::wstring_to_string(L"⍢×: cannot set sign to " + std::to_wstring(nc)));
		}
	  }
	}

	void MulBuiltin::D_NNeNAnonymousInnerClass2::on(std::vector<double> &res, std::vector<double> &o, double n)
	{
	  for (int i = 0; i < res.size(); i++)
	  {
		double oc = o[i];
		if (oc == 0 && n != 0)
		{
			throw DomainError(StringHelper::wstring_to_string(L"⍢×: cannot set sign of 0 to " + Num::format(n)));
		}
		if (n == 0 || n == 1 || n == -1)
		{
			res[i] = std::abs(oc) * n;
		}
		else
		{
			throw DomainError(StringHelper::wstring_to_string(L"⍢×: cannot set sign to " + std::to_wstring(n)));
		}
	  }
	}

	void MulBuiltin::D_NNeNAnonymousInnerClass2::on(std::vector<double> &res, std::vector<double> &o, std::vector<double> &n)
	{
	  for (int i = 0; i < res.size(); i++)
	  {
		double oc = o[i];
		double nc = n[i];
		if (oc == 0 && nc != 0)
		{
			throw DomainError(StringHelper::wstring_to_string(L"⍢×: cannot set sign of 0 to " + Num::format(nc)));
		}
		if (nc == 0 || nc == 1 || nc == -1)
		{
			res[i] = std::abs(oc) * nc;
		}
		else
		{
			throw DomainError(StringHelper::wstring_to_string(L"⍢×: cannot set sign to " + std::to_wstring(nc)));
		}
	  }
	}

	std::shared_ptr<APL::types::Value> MulBuiltin::D_NNeNAnonymousInnerClass2::call(std::shared_ptr<APL::types::BigValue> o, std::shared_ptr<APL::types::BigValue> n)
	{
	  std::shared_ptr<BigInteger> oi = o->i;
	  int ni = APL::types::BigValue::safeInt(n->i);
	  if (oi->signum() == 0 && ni != 0)
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"⍢×: cannot set sign of 0 to " + std::to_wstring(ni)));
	  }
	  if (ni == 0)
	  {
		  return APL::types::BigValue::ZERO;
	  }
	  bool neg = oi->signum() == -1;
	  if (ni == 1 ^ neg)
	  {
		  return o;
	  }
	  if (ni == -1 ^ neg)
	  {
		  return std::make_shared<APL::types::BigValue>(oi->negate());
	  }
	  else
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"⍢×: cannot set sign to " + std::to_wstring(ni)));
	  }
	}

	std::shared_ptr<APL::types::Value> MulBuiltin::under(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w)
	{
	  Main::faulty = shared_from_this();
	  std::shared_ptr<APL::types::Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(w)) : std::static_pointer_cast<APL::types::Value>(o);
	  return numD(SET_SGN, w, v);
	}
}
