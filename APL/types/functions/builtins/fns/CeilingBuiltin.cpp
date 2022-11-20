#include <APL/types/functions/builtins/fns/CeilingBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	std::wstring CeilingBuiltin::repr()
	{
	  return L"⌈";
	}

	std::shared_ptr<Value> CeilingBuiltin::identity()
	{
	  return Num::NEGINF;
	}

const std::shared_ptr<NumMV> CeilingBuiltin::NF = std::make_shared<NumMVAnonymousInnerClass>();

	std::shared_ptr<Value> CeilingBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<Num> w)
	{
	  return w->ceil();
	}

	void CeilingBuiltin::NumMVAnonymousInnerClass::call(std::vector<double> &res, std::vector<double> &a)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = std::ceil(a[i]);
	  }
	}

	std::shared_ptr<Value> CeilingBuiltin::call(std::shared_ptr<Value> w)
	{
//JAVA TO C++ CONVERTER TODO TASK: Method reference arbitrary object instance method syntax is not converted by Java to C++ Converter:
	  return numChrM(NF, Char::upper, w);
	}

const std::shared_ptr<D_NNeN> CeilingBuiltin::DNF = std::make_shared<D_NNeNAnonymousInnerClass>();

	double CeilingBuiltin::D_NNeNAnonymousInnerClass::on(double a, double w)
	{
	  return std::max(a, w);
	}

	void CeilingBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, double a, std::vector<double> &w)
	{
	  for (int i = 0; i < w.size(); i++)
	  {
		  res[i] = std::max(a, w[i]);
	  }
	}

	void CeilingBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, double w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = std::max(a[i], w);
	  }
	}

	void CeilingBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = std::max(a[i], w[i]);
	  }
	}

	std::shared_ptr<Value> CeilingBuiltin::D_NNeNAnonymousInnerClass::call(std::shared_ptr<BigValue> a, std::shared_ptr<BigValue> w)
	{
	  return a->compareTo(w) > 0? a : w;
	}

	std::shared_ptr<Value> CeilingBuiltin::call(std::shared_ptr<Value> a0, std::shared_ptr<Value> w0)
	{
	  return numD(DNF, a0, w0);
	}
}
