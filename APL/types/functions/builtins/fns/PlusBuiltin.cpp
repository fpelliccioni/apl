#include <APL/PlusBuiltin.h>
#include <APL/types/Num.h>
#include <APL/MinusBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	std::wstring PlusBuiltin::repr()
	{
	  return L"+";
	}

	std::shared_ptr<Value> PlusBuiltin::identity()
	{
	  return Num::ZERO;
	}

	std::shared_ptr<Value> PlusBuiltin::call(std::shared_ptr<Value> w)
	{
	  return allM([&] (std::any v)
	  {
	  if (!(std::dynamic_pointer_cast<Num>(v) != nullptr))
	  {
		  throw DomainError(L"Conjugating a non-number", this, w);
	  }
	  return (std::static_pointer_cast<Num>(v))->conjugate();
	  }, w);
	}

const std::shared_ptr<D_NNeN> PlusBuiltin::DNF = std::make_shared<D_NNeNAnonymousInnerClass>();

	double PlusBuiltin::D_NNeNAnonymousInnerClass::on(double a, double w)
	{
	  return a + w;
	}

	void PlusBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, double a, std::vector<double> &w)
	{
	  for (int i = 0; i < w.size(); i++)
	  {
		  res[i] = a + w[i];
	  }
	}

	void PlusBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, double w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = a[i] + w;
	  }
	}

	void PlusBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = a[i] + w[i];
	  }
	}

	std::shared_ptr<Value> PlusBuiltin::D_NNeNAnonymousInnerClass::call(std::shared_ptr<BigValue> a, std::shared_ptr<BigValue> w)
	{
	  return std::make_shared<BigValue>(a->i->add(w->i));
	}

	std::shared_ptr<Value> PlusBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return numD(DNF, a, w);
	}

	std::shared_ptr<Value> PlusBuiltin::callInv(std::shared_ptr<Value> w)
	{
		return call(w);
	}

	std::shared_ptr<Value> PlusBuiltin::callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return numD(MinusBuiltin::DNF, w, a);
	}

	std::shared_ptr<Value> PlusBuiltin::callInvA(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return callInvW(w, a);
	}
}
