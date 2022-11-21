#include <APL/NorBuiltin.h>
#include <APL/Main.h>
#include <APL/TildeBuiltin.h>
#include <APL/types/Num.h>
#include <APL/types/arrs/DoubleArr.h>

namespace APL::types::functions::builtins::fns
{
	// using namespace APL;
	// using namespace APL::types;
	// using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;

	std::string NorBuiltin::repr()
	{
	  return L"⍱";
	}

	NorBuiltin::NorBuiltin(std::shared_ptr<Scope> sc) : APL::types::functions::Builtin(sc)
	{
	}

const std::shared_ptr<D_NNeN> NorBuiltin::DNF = std::make_shared<D_NNeNAnonymousInnerClass>();

	double NorBuiltin::D_NNeNAnonymousInnerClass::on(double a, double w)
	{
	  return Main::bool_Keyword(a) | Main::bool_Keyword(w) ? 0 : 1;
	}

	void NorBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, double a, std::vector<double> &w)
	{
	  for (int i = 0; i < w.size(); i++)
	  {
		  res[i] = Main::bool_Keyword(a) | Main::bool_Keyword(w[i]) ? 0 : 1;
	  }
	}

	void NorBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, double w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = Main::bool_Keyword(a[i]) | Main::bool_Keyword(w) ? 0 : 1;
	  }
	}

	void NorBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = Main::bool_Keyword(a[i]) | Main::bool_Keyword(w[i]) ? 0 : 1;
	  }
	}

const std::shared_ptr<D_BB> NorBuiltin::DBF = std::make_shared<D_BBAnonymousInnerClass>();

	std::shared_ptr<APL::types::Value> NorBuiltin::D_BBAnonymousInnerClass::call(bool a, std::shared_ptr<APL::types::arrs::BitArr> w)
	{
	  if (a)
	  {
		  return APL::types::arrs::BitArr::fill(w, false);
	  }
	  return TildeBuiltin::call(w);
	}

	std::shared_ptr<APL::types::Value> NorBuiltin::D_BBAnonymousInnerClass::call(std::shared_ptr<APL::types::arrs::BitArr> a, bool w)
	{
	  if (w)
	  {
		  return APL::types::arrs::BitArr::fill(a, false);
	  }
	  return TildeBuiltin::call(a);
	}

	std::shared_ptr<APL::types::Value> NorBuiltin::D_BBAnonymousInnerClass::call(std::shared_ptr<APL::types::arrs::BitArr> a, std::shared_ptr<APL::types::arrs::BitArr> w)
	{
	  std::shared_ptr<APL::types::arrs::BitArr::BC> bc = std::make_shared<APL::types::arrs::BitArr::BC>(a->shape);
	  for (int i = 0; i < a->arr.size(); i++)
	  {
		  bc->arr[i] = ~(a->arr[i] | w->arr[i]);
	  }
	  return bc->finish();
	}

	std::shared_ptr<APL::types::Value> NorBuiltin::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  return bitD(DNF, DBF, a, w);
	}

	std::shared_ptr<APL::types::Value> NorBuiltin::call(std::shared_ptr<APL::types::Value> w)
	{
	  if (std::dynamic_pointer_cast<APL::types::arrs::BitArr>(w) != nullptr)
	  {
		std::shared_ptr<APL::types::arrs::BitArr> wb = std::static_pointer_cast<APL::types::arrs::BitArr>(w);
		wb->setEnd(false);
		for (auto l : wb->arr)
		{
			if (l != 0LL)
			{
				return Num::ZERO;
			}
		}
		return Num::ONE;
	  }
	  if (std::dynamic_pointer_cast<DoubleArr>(w) != nullptr)
	  {
		std::vector<double> da = w->asDoubleArr();
		for (int i = 0; i < w->ia; i++)
		{
		  if (Main::bool_Keyword(da[i]))
		  {
			  return Num::ZERO;
		  }
		}
		return Num::ONE;
	  }
	  for (int i = 0; i < w->ia; i++)
	  {
		if (Main::bool_Keyword(w[i]))
		{
			return Num::ZERO;
		}
	  }
	  return Num::ONE;
	}
}
