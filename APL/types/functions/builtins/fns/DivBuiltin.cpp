#include <APL/DivBuiltin.h>
#include <APL/MulBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	std::wstring DivBuiltin::repr()
	{
	  return L"÷";
	}

const std::shared_ptr<NumMV> DivBuiltin::NF = std::make_shared<NumMVAnonymousInnerClass>();

	std::shared_ptr<Value> DivBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<Num> w)
	{
	  return Num::ONE->divide(w);
	}

	void DivBuiltin::NumMVAnonymousInnerClass::call(std::vector<double> &res, std::vector<double> &a)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = 1 / a[i];
	  }
	}

	std::shared_ptr<Value> DivBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<BigValue> w)
	{
	  throw DomainError(L"reciprocal of biginteger", w);
	}

	std::shared_ptr<Value> DivBuiltin::call(std::shared_ptr<Value> w)
	{
	  return numM(NF, w);
	}

const std::shared_ptr<D_NNeN> DivBuiltin::DNF = std::make_shared<D_NNeNAnonymousInnerClass>();

	double DivBuiltin::D_NNeNAnonymousInnerClass::on(double a, double w)
	{
	  return a / w;
	}

	void DivBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, double a, std::vector<double> &w)
	{
	  for (int i = 0; i < w.size(); i++)
	  {
		  res[i] = a / w[i];
	  }
	}

	void DivBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, double w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = a[i] / w;
	  }
	}

	void DivBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = a[i] / w[i];
	  }
	}

	std::shared_ptr<Value> DivBuiltin::D_NNeNAnonymousInnerClass::call(std::shared_ptr<BigValue> a, std::shared_ptr<BigValue> w)
	{
	  return std::make_shared<BigValue>(a->i->divide(w->i));
	}

	std::shared_ptr<Value> DivBuiltin::call(std::shared_ptr<Value> a0, std::shared_ptr<Value> w0)
	{
	  return numD(DNF, a0, w0);
	}

	std::shared_ptr<Value> DivBuiltin::callInv(std::shared_ptr<Value> w)
	{
		return call(w);
	}

	std::shared_ptr<Value> DivBuiltin::callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
		return call(a, w);
	}

	std::shared_ptr<Value> DivBuiltin::callInvA(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return numD(MulBuiltin::DNF, a, w);
	}
}
