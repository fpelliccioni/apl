//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/DTackBuiltin.h>
#include <APL/Num.h>
#include <APL/UTackBuiltin.h>
#include <APL/Primitive.h>
#include <APL/BigValue.h>
#include <APL/Arr.h>
#include <APL/errors/NYIError.h>
#include <APL/arrs/EmptyArr.h>
#include <APL/errors/DomainError.h>
#include <APL/arrs/DoubleArr.h>
#include <APL/arrs/HArr.h>
#include <APL/arrs/BitArr.h>

namespace APL::types::functions::builtins::fns
{
	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;
	using BigInteger = java::math::BigInteger;

	std::wstring DTackBuiltin::repr()
	{
	  return L"⊤";
	}

	std::shared_ptr<Value> DTackBuiltin::call(std::shared_ptr<Value> w)
	{
	  return call(Num::NUMS[2], w);
	}

	std::shared_ptr<Value> DTackBuiltin::callInv(std::shared_ptr<Value> w)
	{
	  return UTackBuiltin::on(Num::NUMS[2], w, shared_from_this());
	}

	std::shared_ptr<Value> DTackBuiltin::callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return UTackBuiltin::on(a, w, shared_from_this());
	}

	std::shared_ptr<Value> DTackBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return on(a, w, shared_from_this());
	}

	std::shared_ptr<Value> DTackBuiltin::on(std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<Callable> blame)
	{
	  if (!(std::dynamic_pointer_cast<Primitive>(a) != nullptr))
	  {
		if (std::dynamic_pointer_cast<BigValue>(w) != nullptr)
		{
		  std::vector<std::shared_ptr<Value>> res;
		  std::shared_ptr<BigInteger> c = (std::static_pointer_cast<BigValue>(w))->i;
		  for (int i = 0; i < a->ia; i++)
		  {
			std::shared_ptr<Value> v = a[a->ia - i - 1];
			std::vector<std::shared_ptr<BigInteger>> dr = c->divideAndRemainder(BigValue::bigint(v));
			res.push_back(std::dynamic_pointer_cast<Num>(v) != nullptr? std::make_shared<Num>(dr[1]) : std::make_shared<BigValue>(dr[1]));
			c = dr[0];
		  }
		  std::reverse(res.begin(), res.end());
		  return Arr::create(res);
		}
		std::vector<int> sh(w->rank + a->rank);
		if (a->rank != 1)
		{
			throw NYIError(blame + L": ⍺ with rank≥2 not yet implemented", blame);
		}

		std::copy_n(a->shape.begin(), a->rank, sh.begin()); // ≡ for (int i = 0; i < a.rank; i++) sh[i] = a.shape[i];
		std::copy_n(w->shape.begin(), w->rank, sh.begin() + a->rank); // ≡ for (int i = 0; i < w.rank; i++) sh[i+a.rank] = w.shape[i];
		if (a->ia == 0)
		{
			return std::make_shared<EmptyArr>(sh, Num::ZERO);
		}
		std::vector<double> c = w->asDoubleArrClone();
		std::vector<double> b = a->asDoubleArr();
		std::vector<double> res(w->ia * a->ia);
		for (int i = 1; i < b.size(); i++)
		{
			if (b[i] == 0)
			{
				throw DomainError(blame + L": ⍺ contained a 0 as not the 1st element", blame, a);
			}
		}
		int last = b[0] == 0? 1 : 0;
		for (int i = b.size() - 1; i >= last; i--)
		{
		  int off = w->ia * i;
		  double cb = b[i];
		  for (int j = 0; j < w->ia; j++)
		  {
			res[off + j] = c[j] % cb;
			c[j] = std::floor(c[j] / cb);
		  }
		}
		if (b[0] == 0)
		{
		  std::copy_n(c.begin(), w->ia, res.begin()); // ≡ for (int j = 0; j < w.ia; j++) res[j] = c[j];
		}
		return std::make_shared<DoubleArr>(res, sh);
	  }
	  if (!(std::dynamic_pointer_cast<Num>(w) != nullptr))
	  {
		if (std::dynamic_pointer_cast<BigValue>(w) != nullptr)
		{
		  std::shared_ptr<BigInteger> APL::types::functions::Builtin = BigValue::bigint(a);
		  bool bigBase = std::dynamic_pointer_cast<BigValue>(a) != nullptr;
		  std::shared_ptr<BigInteger> wlr = (std::static_pointer_cast<BigValue>(w))->i;
		  int sign = wlr->signum();
		  std::shared_ptr<BigInteger> wl = wlr->abs();
		  int ibase = BigValue::safeInt(APL::types::functions::Builtin);
		  if (ibase <= 1)
		  {
			if (ibase == 1 && sign != 0)
			{
				throw DomainError(blame + L": ⍺=1 and ⍵≠0 isn't possible", blame, w);
			}
			if (ibase < 0)
			{
				throw DomainError(blame + L": ⍺ < 0", blame);
			}
		  }
		  if (sign == 0)
		  {
			  return EmptyArr::SHAPE0N;
		  }
		  if (ibase == 2)
		  {
			int len = wl->bitLength();
			if (bigBase)
			{
			  std::vector<std::shared_ptr<Value>> res(len);
			  if (sign == 1)
			  {
				  for (int i = 0; i < len; i++)
				  {
					  res[len - i - 1] = wl->testBit(i)? BigValue::ONE : BigValue::ZERO;
				  }
			  }
			  else
			  {
				  for (int i = 0; i < len; i++)
				  {
					  res[len - i - 1] = wl->testBit(i)? BigValue::MINUS_ONE : BigValue::ZERO;
				  }
			  }
			  return std::make_shared<HArr>(res);
			}
			else if (sign == 1)
			{
			  std::shared_ptr<BitArr::BA> bc = std::make_shared<BitArr::BA>(len);
			  for (int i = 0; i < len; i++)
			  {
				  bc->add(wl->testBit(len - i - 1));
			  }
			  return bc->finish();
			}
			else
			{
			  std::vector<double> res(len);
			  for (int i = 0; i < len; i++)
			  {
				  res[i] = wl->testBit(len - i - 1)? -1 : 0;
			  }
			  return std::make_shared<DoubleArr>(res);
			}
		  }
		  if (ibase <= Character::MAX_RADIX)
		  { // utilize the actually optimized base conversion of BigInteger.toString
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
			std::wstring str = wl->toString(ibase);
			std::vector<std::shared_ptr<Value>> res(str.length());
			for (int i = 0; i < res.size(); i++)
			{
			  wchar_t c = str[i];
			  int n = c <= L'9'? c - L'0' : 10 + c - L'a';
			  if (sign == -1)
			  {
				  n = -n;
			  }
			  res[i] = bigBase? std::make_shared<BigValue>(static_cast<BigInteger>(n)) : Num::of(n);
			}
			return std::make_shared<HArr>(res);
		  }
		  std::vector<std::shared_ptr<Value>> ns; // if we can't, just be lazy. ¯\_(ツ)_/¯
		  while (wl->signum() != 0)
		  {
			std::vector<std::shared_ptr<BigInteger>> c = wl->divideAndRemainder(APL::types::functions::Builtin);
			wl = c[0];
			ns.push_back(bigBase? std::make_shared<BigValue>(sign == 1? c[1] : c[1]->negate()) : std::make_shared<Num>(c[1] * sign));
		  }
		  std::vector<std::shared_ptr<Value>> res(ns.size());
		  for (int i = 0; i < res.size(); i++)
		  {
			res[res.size() - i - 1] = ns[i];
		  }
		  return std::make_shared<HArr>(res);
		}
		throw NYIError(blame + L": scalar ⍺ and non-scalar ⍵ not implemented", blame);
	  }
	  double APL::types::functions::Builtin = a->asDouble();
	  double num = w->asDouble();
	  if (APL::types::functions::Builtin <= 1)
	  {
		if (APL::types::functions::Builtin == 0)
		{
			return Num::of(num);
		}
		if (APL::types::functions::Builtin < 0)
		{
			throw DomainError(blame + L": ⍺ < 0", blame, a);
		}
		throw DomainError(blame + L": ⍺ < 1", blame, a);
	  }
	  auto res = std::vector<double>();
	  if (num < 0)
	  {
		num = -num;
		while (num > 0)
		{
		  res.push_back(-num % APL::types::functions::Builtin);
		  num = std::floor(num / APL::types::functions::Builtin);
		}
	  }
	  else
	  {
		while (num > 0)
		{
		  res.push_back(num % APL::types::functions::Builtin);
		  num = std::floor(num / APL::types::functions::Builtin);
		}
	  }
	  std::vector<double> f(res.size());
	  for (int i = res.size() - 1, j = 0; i >= 0; i--, j++)
	  {
		f[j] = res[i];
	  }
	  return std::make_shared<DoubleArr>(f);
	}
}
