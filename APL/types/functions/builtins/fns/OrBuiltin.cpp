#include <APL/OrBuiltin.h>
#include <APL/types/Num.h>

namespace APL::types::functions::builtins::fns {

// using namespace APL::types;
// using BitArr = APL::types::arrs::BitArr;
// using Builtin = APL::types::functions::Builtin;

std::string OrBuiltin::repr()
{
	return L"∨";
}

std::shared_ptr<APL::types::Value> OrBuiltin::identity()
{
	return Num::ZERO;
}

std::shared_ptr<APL::types::Value> OrBuiltin::call(std::shared_ptr<APL::types::Value> w)
{
	if (std::dynamic_pointer_cast<APL::types::arrs::BitArr>(w) != nullptr)
	{
	std::shared_ptr<APL::types::arrs::BitArr> wb = std::static_pointer_cast<APL::types::arrs::BitArr>(w);
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

std::shared_ptr<APL::types::Value> OrBuiltin::D_NNeNAnonymousInnerClass::call(std::shared_ptr<APL::types::BigValue> a, std::shared_ptr<APL::types::BigValue> w)
{
	return std::make_shared<APL::types::BigValue>(a->i->gcd(w->i));
}

const std::shared_ptr<D_BB> OrBuiltin::DBF = std::make_shared<D_BBAnonymousInnerClass>();

std::shared_ptr<APL::types::Value> OrBuiltin::D_BBAnonymousInnerClass::call(bool a, std::shared_ptr<APL::types::arrs::BitArr> w)
{
	if (a)
	{
		return APL::types::arrs::BitArr::fill(w, true);
	}
	return w;
}

std::shared_ptr<APL::types::Value> OrBuiltin::D_BBAnonymousInnerClass::call(std::shared_ptr<APL::types::arrs::BitArr> a, bool w)
{
	if (w)
	{
		return APL::types::arrs::BitArr::fill(a, true);
	}
	return a;
}

std::shared_ptr<APL::types::Value> OrBuiltin::D_BBAnonymousInnerClass::call(std::shared_ptr<APL::types::arrs::BitArr> a, std::shared_ptr<APL::types::arrs::BitArr> w)
{
	std::shared_ptr<APL::types::arrs::BitArr::BC> bc = std::make_shared<APL::types::arrs::BitArr::BC>(a->shape);
	for (int i = 0; i < a->arr.size(); i++)
	{
		bc->arr[i] = a->arr[i] | w->arr[i];
	}
	return bc->finish();
}

std::shared_ptr<APL::types::Value> OrBuiltin::call(std::shared_ptr<APL::types::Value> a0, std::shared_ptr<APL::types::Value> w0)
{
	return bitD(DNF, DBF, a0, w0);
}

}
