#include <APL/OrBuiltin.h>
#include <APL/types/Num.h>

namespace APL::types::functions::builtins::fns
{
	using namespace APL::types;
	using BitArr = APL::types::arrs::BitArr;
	using Builtin = APL::types::functions::Builtin;

	std::wstring OrBuiltin::repr()
	{
	  return L"∨";
	}

	std::shared_ptr<Value> OrBuiltin::identity()
	{
	  return Num::ZERO;
	}

	std::shared_ptr<Value> OrBuiltin::call(std::shared_ptr<Value> w)
	{
	  if (std::dynamic_pointer_cast<BitArr>(w) != nullptr)
	  {
		std::shared_ptr<BitArr> wb = std::static_pointer_cast<BitArr>(w);
		wb->setEnd(false);
		for (auto l : wb->arr)
		{
			if (l != 0LL)
			{
				return Num::ONE;
			}
		}
		return Num::ZERO;
	  }
	  return std::make_shared<Num>(Num::gcd(w->asDoubleArr()));
	}

const std::shared_ptr<D_NNeN> OrBuiltin::DNF = std::make_shared<D_NNeNAnonymousInnerClass>();

	double OrBuiltin::D_NNeNAnonymousInnerClass::on(double a, double w)
	{
	  return Num::gcd2(a, w);
	}

	void OrBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, double a, std::vector<double> &w)
	{
	  for (int i = 0; i < w.size(); i++)
	  {
		  res[i] = Num::gcd2(a, w[i]);
	  }
	}

	void OrBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, double w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = Num::gcd2(a[i], w);
	  }
	}

	void OrBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = Num::gcd2(a[i], w[i]);
	  }
	}

	std::shared_ptr<Value> OrBuiltin::D_NNeNAnonymousInnerClass::call(std::shared_ptr<BigValue> a, std::shared_ptr<BigValue> w)
	{
	  return std::make_shared<BigValue>(a->i->gcd(w->i));
	}

const std::shared_ptr<D_BB> OrBuiltin::DBF = std::make_shared<D_BBAnonymousInnerClass>();

	std::shared_ptr<Value> OrBuiltin::D_BBAnonymousInnerClass::call(bool a, std::shared_ptr<BitArr> w)
	{
	  if (a)
	  {
		  return BitArr::fill(w, true);
	  }
	  return w;
	}

	std::shared_ptr<Value> OrBuiltin::D_BBAnonymousInnerClass::call(std::shared_ptr<BitArr> a, bool w)
	{
	  if (w)
	  {
		  return BitArr::fill(a, true);
	  }
	  return a;
	}

	std::shared_ptr<Value> OrBuiltin::D_BBAnonymousInnerClass::call(std::shared_ptr<BitArr> a, std::shared_ptr<BitArr> w)
	{
	  std::shared_ptr<BitArr::BC> bc = std::make_shared<BitArr::BC>(a->shape);
	  for (int i = 0; i < a->arr.size(); i++)
	  {
		  bc->arr[i] = a->arr[i] | w->arr[i];
	  }
	  return bc->finish();
	}

	std::shared_ptr<Value> OrBuiltin::call(std::shared_ptr<Value> a0, std::shared_ptr<Value> w0)
	{
	  return bitD(DNF, DBF, a0, w0);
	}
}
