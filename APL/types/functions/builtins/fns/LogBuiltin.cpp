#include <APL/LogBuiltin.h>
#include <APL/StarBuiltin.h>
#include <APL/RootBuiltin.h>

namespace APL::types::functions::builtins::fns
{
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;
	using Builtin = APL::types::functions::Builtin;

	std::wstring LogBuiltin::repr()
	{
	  return L"⍟";
	}

const double LogBuiltin::LN2 = std::log(2);
const std::shared_ptr<NumMV> LogBuiltin::NF = std::make_shared<NumMVAnonymousInnerClass>();

	std::shared_ptr<Value> LogBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<Num> w)
	{
	  return w->log(Num::E);
	}

	void LogBuiltin::NumMVAnonymousInnerClass::call(std::vector<double> &res, std::vector<double> &a)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = std::log(a[i]);
	  }
	}

	std::shared_ptr<Num> LogBuiltin::NumMVAnonymousInnerClass::call(std::shared_ptr<BigValue> w)
	{
	  if (w->i->signum() <= 0)
	  {
		if (w->i->signum() == -1)
		{
			throw DomainError(L"logarithm of negative number", w);
		}
		return Num::NEGINF;
	  }
	  if (w->i->bitLength() < 1023)
	  {
		  return std::make_shared<Num>(std::log(w->i->doubleValue())); // safe quick path
	  }
	  int len = w->i->bitLength();
	  int shift = len > 64? len - 64 : 0; // 64 msb should be enough to get most out of log
	  double d = w->i->shiftRight(shift).doubleValue();
	  return std::make_shared<Num>(std::log(d) + LN2 * shift);
	}

	std::shared_ptr<Value> LogBuiltin::call(std::shared_ptr<Value> w)
	{
	  return numM(NF, w);
	}

	std::shared_ptr<Value> LogBuiltin::callInv(std::shared_ptr<Value> w)
	{
	  return numM(StarBuiltin::NF, w);
	}

const std::shared_ptr<D_NNeN> LogBuiltin::DNF = std::make_shared<D_NNeNAnonymousInnerClass>();

	double LogBuiltin::D_NNeNAnonymousInnerClass::on(double a, double w)
	{
	  return std::log(w) / std::log(a);
	}

	void LogBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, double a, std::vector<double> &w)
	{
	  double la = std::log(a);
	  for (int i = 0; i < w.size(); i++)
	  {
		  res[i] = std::log(w[i]) / la;
	  }
	}

	void LogBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, double w)
	{
	  double lw = std::log(w);
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = lw / std::log(a[i]);
	  }
	}

	void LogBuiltin::D_NNeNAnonymousInnerClass::on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w)
	{
	  for (int i = 0; i < a.size(); i++)
	  {
		  res[i] = std::log(w[i]) / std::log(a[i]);
	  }
	}

	std::shared_ptr<Value> LogBuiltin::D_NNeNAnonymousInnerClass::call(double a, std::shared_ptr<BigValue> w)
	{
	  double res = (std::static_pointer_cast<Num>(NF->call(w)))->num / std::log(a);
	  if (a == 2)
	  { // quick path to make sure 2⍟ makes sense
		int expected = w->i->bitLength() - 1;
		// System.out.println(res+" > "+expected);
		if (res < expected)
		{
			return Num::of(expected);
		}
		if (res >= expected + 1)
		{ // have to get the double juuuust below expected
		  long long repr = Double::doubleToRawLongBits(expected + 1);
		  repr--; // should be safe as positive int values are always well into the proper double domain
		  return std::make_shared<Num>(Double::longBitsToDouble(repr));
		}
	  }
	  return std::make_shared<Num>(res);
	}

	std::shared_ptr<Value> LogBuiltin::call(std::shared_ptr<Value> a0, std::shared_ptr<Value> w0)
	{
	  return numD(DNF, a0, w0);
	}

	std::shared_ptr<Value> LogBuiltin::callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return numD(StarBuiltin::DNF, a, w);
	}

	std::shared_ptr<Value> LogBuiltin::callInvA(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return numD(RootBuiltin::DNF, a, w);
	}
}
