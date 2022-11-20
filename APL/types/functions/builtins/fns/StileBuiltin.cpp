//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/StileBuiltin.h>
#include <APL/types/Fun.h>

namespace APL::types::functions::builtins::fns
{
	using Main = APL::Main;
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;
	using BigInteger = java::math::BigInteger;

	std::wstring StileBuiltin::repr()
	{
	  return L"|";
	}

const std::shared_ptr<NumMV> StileBuiltin::NF = std::make_shared<NumMVAnonymousInnerClass>();

	std::shared_ptr<Value> StileBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<Num> w)
	{
	  return w->abs();
	}

	void StileBuiltin::NumMVAnonymousInnerClass::call(std::vector<double> &res, std::vector<double> &a)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = std::abs(a[i]);
	  }
	}

	std::shared_ptr<Value> StileBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<BigValue> w)
	{
	  return std::make_shared<BigValue>(w->i->abs());
	}

	std::shared_ptr<Value> StileBuiltin::call(std::shared_ptr<Value> w)
	{
	  return numChrMapM(NF, [&] (std::any c)
	  {
	  throw DomainError(L"|char", this, w);
	  }, [&] (std::any c)
	  {
	  return Num::of(c->size());
		}, w);
	}

const std::shared_ptr<D_NNeN> StileBuiltin::DNF = std::make_shared<D_NNeNAnonymousInnerClass>();

	double StileBuiltin::D_NNeNAnonymousInnerClass::on(double a, double w)
	{
	  double c = w % a;
	  if (c < 0)
	  {
		  return c + a;
	  }
	  return c;
	}

	void StileBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, double a, std::vector<double> &w)
	{
	  int ia = static_cast<int>(a);
	  if (a == ia)
	  {
		if (ia > 0 && (ia & ia - 1) == 0)
		{
		  // power of 2 ⍺
		  int mask = ia - 1;
		  for (int i = 0; i < w.size(); i++)
		  {
			int intv = static_cast<int>(w[i]);
			if (intv == w[i])
			{
				res[i] = (intv & mask) + w[i] - intv;
			}
			else
			{
			  double c = w[i] % ia;
			  if (c < 0)
			  {
				  res[i] = c + a;
			  }
			  else
			  {
				  res[i] = c;
			  }
			}
		  }
		}
		else
		{
		  // integer ⍺
		  for (int i = 0; i < w.size(); i++)
		  {
			double c = w[i] % ia;
			if (c < 0)
			{
				res[i] = c + a;
			}
			else
			{
				res[i] = c;
			}
		  }
		}
	  }
	  else
	  {
		// arbitrary double ⍺
		for (int i = 0; i < w.size(); i++)
		{
		  double c = w[i] % a;
		  if (c < 0)
		  {
			  res[i] = c + a;
		  }
		  else
		  {
			  res[i] = c;
		  }
		}
	  }
	}

	void StileBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, double w)
	{
	  if (w > 0)
	  {
		  for (int i = 0; i < a.size(); i++)
		  {
			  res[i] = w % a[i];
		  }
	  }
	  else
	  {
		  for (int i = 0; i < a.size(); i++)
		  {
		double c = w % a[i];
		if (c < 0)
		{
			res[i] = c + a[i];
		}
		else
		{
			res[i] = c;
		}
		  }
	  }
	}

	void StileBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		double c = w[i] % a[i];
		if (c < 0)
		{
			res[i] = c + a[i];
		}
		else
		{
			res[i] = c;
		}
	  }
	}

	std::shared_ptr<Value> StileBuiltin::D_NNeNAnonymousInnerClass::call(std::shared_ptr<BigValue> a, std::shared_ptr<BigValue> w)
	{
	  std::shared_ptr<BigInteger> r = w->i->remainder(a->i);
	  if (r->signum() < 0)
	  {
		  r = r->add(a->i);
	  }
	  return std::make_shared<BigValue>(r);
	}

	std::shared_ptr<Value> StileBuiltin::call(std::shared_ptr<Value> a0, std::shared_ptr<Value> w0)
	{
	  return numD(DNF, a0, w0);
	}

const std::shared_ptr<D_NNeN> StileBuiltin::CPY_SGN = std::make_shared<D_NNeNAnonymousInnerClass2>();

	double StileBuiltin::D_NNeNAnonymousInnerClass2::on(double o, double n)
	{
	  if (o == 0 && n != 0)
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"⍢|: cannot add sign to " + std::to_wstring(n) + L" as original was 0"));
	  }
	  return o < 0? -n : n;
	}

	void StileBuiltin::D_NNeNAnonymousInnerClass2::on(std::vector<double> &res, double o, std::vector<double> &n)
	{
	  for (int i = 0; i < res.size(); i++)
	  {
		double nc = n[i];
		if (o == 0 && nc != 0)
		{
			throw DomainError(StringHelper::wstring_to_string(L"⍢|: cannot add sign to " + std::to_wstring(nc) + L" as original was 0"));
		}
		res[i] = o < 0? -nc : nc;
	  }
	}

	void StileBuiltin::D_NNeNAnonymousInnerClass2::on(std::vector<double> &res, std::vector<double> &o, double n)
	{
	  for (int i = 0; i < res.size(); i++)
	  {
		double oc = o[i];
		if (oc == 0 && n != 0)
		{
			throw DomainError(StringHelper::wstring_to_string(L"⍢|: cannot add sign to " + std::to_wstring(n) + L" as original was 0"));
		}
		res[i] = oc < 0? -n : n;
	  }
	}

	void StileBuiltin::D_NNeNAnonymousInnerClass2::on(std::vector<double> &res, std::vector<double> &o, std::vector<double> &n)
	{
	  for (int i = 0; i < res.size(); i++)
	  {
		double oc = o[i];
		double nc = n[i];
		if (oc == 0 && nc != 0)
		{
			throw DomainError(StringHelper::wstring_to_string(L"⍢|: cannot add sign to " + std::to_wstring(nc) + L" as original was 0"));
		}
		res[i] = oc < 0? -nc : nc;
	  }
	}

	std::shared_ptr<Value> StileBuiltin::D_NNeNAnonymousInnerClass2::call(std::shared_ptr<BigValue> o, std::shared_ptr<BigValue> n)
	{
	  std::shared_ptr<BigInteger> oi = o->i;
	  std::shared_ptr<BigInteger> ni = n->i;
	  if (oi->signum() == 0 && ni->signum() != 0)
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"⍢|: cannot add sign to " + ni + L" as original was 0"));
	  }
	  return oi->signum() < 0? std::make_shared<BigValue>(ni->negate()) : n;
	}

	std::shared_ptr<Value> StileBuiltin::under(std::shared_ptr<Obj> o, std::shared_ptr<Value> w)
	{
	  Main::faulty = shared_from_this();
	  std::shared_ptr<Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(w)) : std::static_pointer_cast<Value>(o);
	  return numD(CPY_SGN, w, v);
	}
}
