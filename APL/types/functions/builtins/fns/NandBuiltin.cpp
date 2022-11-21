#include <APL/NandBuiltin.h>
#include <APL/Main.h>
#include <APL/TildeBuiltin.h>
#include <APL/types/Num.h>

namespace APL::types::functions::builtins::fns {

// using namespace APL;
// using namespace APL::types;
// using BitArr = APL::types::arrs::APL::types::arrs::BitArr;
// using Builtin = APL::types::functions::Builtin;

std::string NandBuiltin::repr()
{
	return L"⍲";
}

NandBuiltin::NandBuiltin(std::shared_ptr<Scope> sc) : APL::types::functions::Builtin(sc)
{
}

const std::shared_ptr<D_NNeN> NandBuiltin::DNF = std::make_shared<D_NNeNAnonymousInnerClass>();

double NandBuiltin::D_NNeNAnonymousInnerClass::on(double a, double w)
{
	return Main::bool_Keyword(a) & Main::bool_Keyword(w) ? 0 : 1;
}

void NandBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, double a, std::vector<double> &w)
{
	for (int i = 0; i < w.size(); i++)
	{
		res[i] = Main::bool_Keyword(a) & Main::bool_Keyword(w[i]) ? 0 : 1;
	}
}

void NandBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, double w)
{
	for (int i = 0; i < a.size(); i++)
	{
		res[i] = Main::bool_Keyword(a[i]) & Main::bool_Keyword(w) ? 0 : 1;
	}
}

void NandBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w)
{
	for (int i = 0; i < a.size(); i++)
	{
		res[i] = Main::bool_Keyword(a[i]) & Main::bool_Keyword(w[i]) ? 0 : 1;
	}
}

const std::shared_ptr<D_BB> NandBuiltin::DBF = std::make_shared<D_BBAnonymousInnerClass>();

std::shared_ptr<APL::types::Value> NandBuiltin::D_BBAnonymousInnerClass::call(bool a, std::shared_ptr<APL::types::arrs::BitArr> w)
{
	if (a)
	{
		return TildeBuiltin::call(w);
	}
	return APL::types::arrs::BitArr::fill(w, true);
}

std::shared_ptr<APL::types::Value> NandBuiltin::D_BBAnonymousInnerClass::call(std::shared_ptr<APL::types::arrs::BitArr> a, bool w)
{
	if (w)
	{
		return TildeBuiltin::call(a);
	}
	return APL::types::arrs::BitArr::fill(a, true);
}

std::shared_ptr<APL::types::Value> NandBuiltin::D_BBAnonymousInnerClass::call(std::shared_ptr<APL::types::arrs::BitArr> a, std::shared_ptr<APL::types::arrs::BitArr> w)
{
	std::shared_ptr<APL::types::arrs::BitArr::BC> bc = std::make_shared<APL::types::arrs::BitArr::BC>(a->shape);
	for (int i = 0; i < a->arr.size(); i++)
	{
		bc->arr[i] = ~(a->arr[i] & w->arr[i]);
	}
	return bc->finish();
}

std::shared_ptr<APL::types::Value> NandBuiltin::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
{
	return bitD(DNF, DBF, a, w);
}

std::shared_ptr<APL::types::Value> NandBuiltin::call(std::shared_ptr<APL::types::Value> w)
{
	if (std::dynamic_pointer_cast<APL::types::arrs::BitArr>(w) != nullptr)
	{
	std::shared_ptr<APL::types::arrs::BitArr> wb = std::static_pointer_cast<APL::types::arrs::BitArr>(w);
	wb->setEnd(true);
	for (auto l : wb->arr)
	{
		if (l != ~0LL)
		{
			return Num::ONE;
		}
	}
	return Num::ZERO;
	}
	if (w->quickDoubleArr())
	{
	std::vector<double> da = w->asDoubleArr();
	for (int i = 0; i < w->ia; i++)
	{
		if (!Main::bool_Keyword(da[i]))
		{
			return Num::ONE;
		}
	}
	return Num::ZERO;
	}
	for (int i = 0; i < w->ia; i++)
	{
	if (!Main::bool_Keyword(w[i]))
	{
		return Num::ONE;
	}
	}
	return Num::ZERO;
}

}
