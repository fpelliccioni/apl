#include <APL/MinusBuiltin.h>
#include <APL/PlusBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	std::wstring MinusBuiltin::repr()
	{
	  return L"-";
	}

const std::shared_ptr<NumMV> MinusBuiltin::NF = std::make_shared<NumMVAnonymousInnerClass>();

	std::shared_ptr<Value> MinusBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<Num> n)
	{
	  return n->negate();
	}

	void MinusBuiltin::NumMVAnonymousInnerClass::call(std::vector<double> &res, std::vector<double> &a)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = -a[i];
	  }
	}

	std::shared_ptr<Value> MinusBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<BigValue> w)
	{
	  return std::make_shared<BigValue>(w->i->negate());
	}

	std::shared_ptr<Value> MinusBuiltin::call(std::shared_ptr<Value> w)
	{
//JAVA TO C++ CONVERTER TODO TASK: Method reference arbitrary object instance method syntax is not converted by Java to C++ Converter:
	  return numChrM(NF, Char::swap, w);
	}

const std::shared_ptr<D_NNeN> MinusBuiltin::DNF = std::make_shared<D_NNeNAnonymousInnerClass>();

	double MinusBuiltin::D_NNeNAnonymousInnerClass::on(double a, double w)
	{
	  return a - w;
	}

	void MinusBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, double a, std::vector<double> &w)
	{
	  for (int i = 0; i < w.size(); i++)
	  {
		  res[i] = a - w[i];
	  }
	}

	void MinusBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, double w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = a[i] - w;
	  }
	}

	void MinusBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = a[i] - w[i];
	  }
	}

	std::shared_ptr<Value> MinusBuiltin::D_NNeNAnonymousInnerClass::call(std::shared_ptr<BigValue> a, std::shared_ptr<BigValue> w)
	{
	  return std::make_shared<BigValue>(a->i->subtract(w->i));
	}

	std::shared_ptr<Value> MinusBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return numD(DNF, a, w);
	}

	std::shared_ptr<Value> MinusBuiltin::callInv(std::shared_ptr<Value> w)
	{
		return call(w);
	}

	std::shared_ptr<Value> MinusBuiltin::callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
		return call(a, w);
	}

	std::shared_ptr<Value> MinusBuiltin::callInvA(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return numD(PlusBuiltin::DNF, a, w);
	}
}
