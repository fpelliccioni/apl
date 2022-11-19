#include <APL/NEBuiltin.h>
#include <APL/Num.h>
#include <APL/TildeBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using namespace APL::types;
	using BitArr = APL::types::arrs::BitArr;
	using Builtin = APL::types::functions::Builtin;

	std::wstring NEBuiltin::repr()
	{
	  return L"≠";
	}

const std::shared_ptr<D_NNeB> NEBuiltin::DNF = std::make_shared<D_NNeBAnonymousInnerClass>();

	bool NEBuiltin::D_NNeBAnonymousInnerClass::on(double a, double w)
	{
	  return a != w;
	}

	void NEBuiltin::D_NNeBAnonymousInnerClass::on(std::shared_ptr<BitArr::BA> res, double a, std::vector<double> &w)
	{
	  for (auto cw : w)
	  {
		  res->add(a != cw);
	  }
	}

	void NEBuiltin::D_NNeBAnonymousInnerClass::on(std::shared_ptr<BitArr::BA> res, std::vector<double> &a, double w)
	{
	  for (auto ca : a)
	  {
		  res->add(ca != w);
	  }
	}

	void NEBuiltin::D_NNeBAnonymousInnerClass::on(std::shared_ptr<BitArr::BA> res, std::vector<double> &a, std::vector<double> &w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res->add(a[i] != w[i]);
	  }
	}

	std::shared_ptr<Value> NEBuiltin::D_NNeBAnonymousInnerClass::call(std::shared_ptr<BigValue> a, std::shared_ptr<BigValue> w)
	{
	  return a->equals(w)? Num::ZERO : Num::ONE;
	}

const std::shared_ptr<D_BB> NEBuiltin::DBF = std::make_shared<D_BBAnonymousInnerClass>();

	std::shared_ptr<Value> NEBuiltin::D_BBAnonymousInnerClass::call(bool a, std::shared_ptr<BitArr> w)
	{
	  if (a)
	  {
		  return TildeBuiltin::call(w);
	  }
	  return w;
	}

	std::shared_ptr<Value> NEBuiltin::D_BBAnonymousInnerClass::call(std::shared_ptr<BitArr> a, bool w)
	{
	  if (w)
	  {
		  return TildeBuiltin::call(a);
	  }
	  return a;
	}

	std::shared_ptr<Value> NEBuiltin::D_BBAnonymousInnerClass::call(std::shared_ptr<BitArr> a, std::shared_ptr<BitArr> w)
	{
	  std::shared_ptr<BitArr::BC> bc = BitArr::create(w->shape);
	  for (int i = 0; i < bc->arr.size(); i++)
	  {
		  bc->arr[i] = a->arr[i] ^ w->arr[i];
	  }
	  return bc->finish();
	}

	std::shared_ptr<Value> NEBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return ncbaD(DNF, DBF, [&] (ca, cw)
	  {
	  return ca != cw? Num::ONE : Num::ZERO;
	  }, [&] (ca, cw)
	  {
	  ca::equals(cw)? Num::ZERO : Num::ONE;
		}, a, w);
	}
}
