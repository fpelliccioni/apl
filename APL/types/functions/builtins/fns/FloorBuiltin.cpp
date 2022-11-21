#include <APL/FloorBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	// using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	std::string FloorBuiltin::repr()
	{
	  return L"⌊";
	}

	std::shared_ptr<APL::types::Value> FloorBuiltin::identity()
	{
	  return Num::POSINF;
	}

const std::shared_ptr<NumMV> FloorBuiltin::NF = std::make_shared<NumMVAnonymousInnerClass>();

	std::shared_ptr<APL::types::Value> FloorBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<Num> w)
	{
	  return w->floor();
	}

	void FloorBuiltin::NumMVAnonymousInnerClass::call(std::vector<double> &res, std::vector<double> &a)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = std::floor(a[i]);
	  }
	}

	std::shared_ptr<APL::types::Value> FloorBuiltin::call(std::shared_ptr<APL::types::Value> w)
	{
//JAVA TO C++ CONVERTER TODO TASK: Method reference arbitrary object instance method syntax is not converted by Java to C++ Converter:
	  return numChrM(NF, Char::lower, w);
	}

const std::shared_ptr<D_NNeN> FloorBuiltin::DNF = std::make_shared<D_NNeNAnonymousInnerClass>();

	double FloorBuiltin::D_NNeNAnonymousInnerClass::on(double a, double w)
	{
	  return std::min(a, w);
	}

	void FloorBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, double a, std::vector<double> &w)
	{
	  for (int i = 0; i < w.size(); i++)
	  {
		  res[i] = std::min(a, w[i]);
	  }
	}

	void FloorBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, double w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = std::min(a[i], w);
	  }
	}

	void FloorBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = std::min(a[i], w[i]);
	  }
	}

	std::shared_ptr<APL::types::Value> FloorBuiltin::D_NNeNAnonymousInnerClass::call(std::shared_ptr<APL::types::BigValue> a, std::shared_ptr<APL::types::BigValue> w)
	{
	  return a->compareTo(w) > 0? w : a;
	}

	std::shared_ptr<APL::types::Value> FloorBuiltin::call(std::shared_ptr<APL::types::Value> a0, std::shared_ptr<APL::types::Value> w0)
	{
	  return numD(DNF, a0, w0);
	}
}
