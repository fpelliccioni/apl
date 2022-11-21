#include <APL/RootBuiltin.h>
#include <APL/StarBuiltin.h>
#include <APL/LogBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	// using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	std::string RootBuiltin::repr()
	{
	  return L"√";
	}

const std::shared_ptr<NumMV> RootBuiltin::NF = std::make_shared<NumMVAnonymousInnerClass>();

	std::shared_ptr<APL::types::Value> RootBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<Num> w)
	{
	  return w->root(Num::NUMS[2]);
	}

	void RootBuiltin::NumMVAnonymousInnerClass::call(std::vector<double> &res, std::vector<double> &a)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = std::sqrt(a[i]);
	  }
	}

const std::shared_ptr<NumMV> RootBuiltin::NFi = std::make_shared<NumMVAnonymousInnerClass2>();

	std::shared_ptr<APL::types::Value> RootBuiltin::NumMVAnonymousInnerClass2::call(std::shared_ptr<Num> w)
	{
	  return Num::of(w->num * w->num);
	}

	void RootBuiltin::NumMVAnonymousInnerClass2::call(std::vector<double> &res, std::vector<double> &a)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = a[i] * a[i];
	  }
	}

	std::shared_ptr<APL::types::Value> RootBuiltin::call(std::shared_ptr<APL::types::Value> w)
	{
	  return numM(NF, w);
	}

	std::shared_ptr<APL::types::Value> RootBuiltin::callInv(std::shared_ptr<APL::types::Value> w)
	{
	  return numM(NFi, w);
	}

const std::shared_ptr<D_NNeN> RootBuiltin::DNF = std::make_shared<D_NNeNAnonymousInnerClass>();

	double RootBuiltin::D_NNeNAnonymousInnerClass::on(double a, double w)
	{
	  return std::pow(w, 1 / a);
	}

	void RootBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, double a, std::vector<double> &w)
	{
	  double pow = 1 / a;
	  for (int i = 0; i < w.size(); i++)
	  {
		  res[i] = std::pow(w[i], pow);
	  }
	}

	void RootBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, double w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = std::pow(w, 1 / a[i]);
	  }
	}

	void RootBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = std::pow(w[i], 1 / a[i]);
	  }
	}

	std::shared_ptr<APL::types::Value> RootBuiltin::call(std::shared_ptr<APL::types::Value> a0, std::shared_ptr<APL::types::Value> w0)
	{
	  return numD(DNF, a0, w0);
	}

	std::shared_ptr<APL::types::Value> RootBuiltin::callInvW(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  return numD(StarBuiltin::DNF, w, a);
	}

	std::shared_ptr<APL::types::Value> RootBuiltin::callInvA(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  return numD(LogBuiltin::DNF, a, w);
	}
}
