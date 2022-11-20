#include <APL/UTackBuiltin.h>
#include <APL/types/Num.h>
#include <APL/DTackBuiltin.h>
#include <APL/errors/DomainError.h>
#include <APL/types/BigValue.h>
#include <APL/errors/NYIError.h>

namespace APL::types::functions::builtins::fns
{
	using namespace APL::errors;
	using namespace APL::types;
	using DoubleArr = APL::types::arrs::DoubleArr;
	using Builtin = APL::types::functions::Builtin;
	using BigInteger = java::math::BigInteger;

	std::wstring UTackBuiltin::repr()
	{
	  return L"⊥";
	}

	std::shared_ptr<Value> UTackBuiltin::call(std::shared_ptr<Value> w)
	{
	  return call(Num::NUMS[2], w);
	}

	std::shared_ptr<Value> UTackBuiltin::callInv(std::shared_ptr<Value> w)
	{
	  return DTackBuiltin::on(Num::NUMS[2], w, shared_from_this());
	}

	std::shared_ptr<Value> UTackBuiltin::callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return DTackBuiltin::on(a, w, shared_from_this());
	}

	std::shared_ptr<Value> UTackBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return on(a, w, shared_from_this());
	}

	std::shared_ptr<Value> UTackBuiltin::on(std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<Callable> blame)
	{
	  if (w->rank == 0)
	  {
		  throw DomainError(L"A⊥num is pointless", blame);
	  }
	  if (std::dynamic_pointer_cast<BigValue>(a) != nullptr || std::dynamic_pointer_cast<BigValue>(a->first()) != nullptr || std::dynamic_pointer_cast<BigValue>(w->first()) != nullptr)
	  {
		if (a->rank == 0)
		{
		  std::shared_ptr<BigInteger> al = BigValue::bigint(a);
		  std::shared_ptr<BigInteger> res = BigInteger::ZERO;
		  for (int i = 0; i < w->ia; i++)
		  {
			res = res->multiply(al)->add(BigValue::bigint(w[i]));
		  }
		  return std::make_shared<BigValue>(res);
		}
		else
		{
		  if (w->rank != 1)
		  {
			  throw NYIError(blame + L": 1<≢⍴⍵", blame);
		  }
		  if (a->rank != 1)
		  {
			  throw DomainError(blame + L": 1<≢⍴⍺", blame);
		  }
		  if (a->ia != w->shape[0])
		  {
			  throw DomainError(blame + L": (≢⍺) ≠ ≢⍵", blame);
		  }
		  std::shared_ptr<BigInteger> res = BigInteger::ZERO;
		  for (int i = 0; i < a->ia; i++)
		  {
			res = res->multiply(BigValue::bigint(a[i]));
			res = res->add(BigValue::bigint(w[i]));
		  }
		  return std::make_shared<BigValue>(res);
		}
	  }
	  if (std::dynamic_pointer_cast<Num>(a) != nullptr)
	  {
		double APL::types::functions::Builtin = a->asDouble();
		if (w->rank == 1)
		{
		  double res = 0;
		  for (int i = 0; i < w->ia; i++)
		  {
			res = res * APL::types::functions::Builtin + w[i].asDouble();
		  }
		  return std::make_shared<Num>(res);
		}
		else
		{
		  std::vector<double> d = w->asDoubleArr();
		  std::vector<int> sh(w->rank - 1);
		  std::copy_n(w->shape.begin() + 1, w->rank - 1, sh.begin());
		  int layers = w->shape[0];
		  std::vector<double> r(w->ia / layers);

		  std::copy_n(d.begin(), r.size(), r.begin());
		  for (int i = 1; i < layers; i++)
		  {
			for (int j = 0; j < r.size(); j++)
			{
			  r[j] = r[j] * APL::types::functions::Builtin + d[j + r.size() * i];
			}
		  }

		  return std::make_shared<DoubleArr>(r, sh);
		}
	  }
	  else
	  {
		if (a->ia != w->shape[0])
		{
			throw DomainError(blame + L": (≢⍺) ≠ ⊃⍴⍵", blame);
		}
		std::vector<double> d = w->asDoubleArr();
		std::vector<double> bases = a->asDoubleArr();
		std::vector<int> sh(w->rank - 1);
		std::copy_n(w->shape.begin() + 1, w->rank - 1, sh.begin());
		int layers = w->shape[0];
		std::vector<double> r(w->ia / layers);

		std::copy_n(d.begin(), r.size(), r.begin());
		for (int i = 1; i < layers; i++)
		{
		  double APL::types::functions::Builtin = bases[i];
		  for (int j = 0; j < r.size(); j++)
		  {
			r[j] = r[j] * APL::types::functions::Builtin + d[j + r.size() * i];
		  }
		}
		if (sh.empty())
		{
			return std::make_shared<Num>(r[0]);
		}
		return std::make_shared<DoubleArr>(r, sh);
	  }
	}
}
