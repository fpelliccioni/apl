#include <APL/GTBuiltin.h>
#include <APL/Num.h>
#include <APL/Arr.h>

namespace APL::types::functions::builtins::fns
{
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;
	using BitArr = APL::types::arrs::BitArr;
	using Builtin = APL::types::functions::Builtin;
	using Arrays = java::util::Arrays;

	std::wstring GTBuiltin::repr()
	{
	  return L">";
	}

const std::shared_ptr<D_NNeB> GTBuiltin::DNF = std::make_shared<D_NNeBAnonymousInnerClass>();

	bool GTBuiltin::D_NNeBAnonymousInnerClass::on(double a, double w)
	{
	  return a > w;
	}

	void GTBuiltin::D_NNeBAnonymousInnerClass::on(std::shared_ptr<BitArr::BA> res, double a, std::vector<double> &w)
	{
	  for (auto cw : w)
	  {
		  res->add(a > cw);
	  }
	}

	void GTBuiltin::D_NNeBAnonymousInnerClass::on(std::shared_ptr<BitArr::BA> res, std::vector<double> &a, double w)
	{
	  for (auto ca : a)
	  {
		  res->add(ca > w);
	  }
	}

	void GTBuiltin::D_NNeBAnonymousInnerClass::on(std::shared_ptr<BitArr::BA> res, std::vector<double> &a, std::vector<double> &w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res->add(a[i] > w[i]);
	  }
	}

	std::shared_ptr<Value> GTBuiltin::D_NNeBAnonymousInnerClass::call(std::shared_ptr<BigValue> a, std::shared_ptr<BigValue> w)
	{
	  return a->i->compareTo(w->i) > 0? Num::ONE : Num::ZERO;
	}

	std::shared_ptr<Value> GTBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return numChrD(DNF, [&] (ca, cw)
	  {
	  return ca > cw? Num::ONE : Num::ZERO;
	  }, [&] (ca, cw)
	  {
	  throw DomainError(StringHelper::wstring_to_string(L"comparing " + ca::humanType(true) + L" and " + cw::humanType(true), this));
		}, a, w);
	}

	std::shared_ptr<Value> GTBuiltin::call(std::shared_ptr<Value> w)
	{
	  auto order = w->gradeDown();
	  std::vector<std::shared_ptr<Value>> res(order->length);
	  Arrays::setAll(res, [&] (std::any i)
	  {
	  w[order[i]];
	  });
	  return Arr::create(res);
	}
}
