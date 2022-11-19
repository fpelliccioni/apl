//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/ReplicateBuiltin.h>
#include <APL/errors/RankError.h>
#include <APL/Num.h>
#include <APL/arrs/DoubleArr.h>
#include <APL/Char.h>
#include <APL/Arr.h>
#include <APL/arrs/BitArr.h>
#include <APL/errors/LengthError.h>
#include <APL/arrs/ChrArr.h>

namespace APL::types::functions::builtins::fns
{
	using Main = APL::Main;
	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;
	using AtBuiltin = APL::types::functions::builtins::dops::AtBuiltin;
	using Arrays = java::util::Arrays;

	std::wstring ReplicateBuiltin::repr()
	{
	  return L"⌿";
	}

	std::shared_ptr<Value> ReplicateBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  return replicate(a, w, shared_from_this());
	}

	std::shared_ptr<Value> ReplicateBuiltin::replicate(std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<Callable> blame)
	{
	  if (a->rank == 0)
	  {
		if (w->rank > 1)
		{
			throw RankError(L"⌿: rank of ⍵ should be ≤1 if ⍺ is a scalar", blame);
		}
		int sz = a->asInt();
		if (sz < 0)
		{
		  int am = w->ia * -sz;
		  std::shared_ptr<Value> pr = w->prototype();
		  if (std::dynamic_pointer_cast<Num>(pr) != nullptr)
		  {
			  return std::make_shared<DoubleArr>(std::vector<double>(am));
		  }
		  std::vector<std::shared_ptr<Value>> res(am);
		  std::shared_ptr<Value> n = std::dynamic_pointer_cast<Char>(w->first()) != nullptr? Char::SPACE : Num::ZERO;
		  Arrays::fill(res, n);
		  return Arr::create(res);
		}

		int am = w->ia * sz;
		if (std::dynamic_pointer_cast<BitArr>(w) != nullptr)
		{
		  std::shared_ptr<BitArr::BA> res = std::make_shared<BitArr::BA>(am);
		  std::shared_ptr<BitArr::BR> r = (std::static_pointer_cast<BitArr>(w))->read();
		  for (int i = 0; i < w->ia; i++)
		  {
			if (r->read())
			{
				res->fill(sz);
			}
			else
			{
				res->skip(sz);
			}
		  }
		  return res->finish();
		}
		if (w->quickDoubleArr())
		{
		  std::vector<double> res(am);
		  std::vector<double> ds = w->asDoubleArr();
		  int ptr = 0;
		  for (int i = 0; i < w->ia; i++)
		  {
			double c = ds[i];
			for (int j = 0; j < sz; j++)
			{
			  res[ptr++] = c;
			}
		  }
		  return std::make_shared<DoubleArr>(res);
		}
		std::vector<std::shared_ptr<Value>> res(am);
		int ptr = 0;
		for (int i = 0; i < w->ia; i++)
		{
		  std::shared_ptr<Value> c = w[i];
		  for (int j = 0; j < sz; j++)
		  {
			res[ptr++] = c;
		  }
		}
		return Arr::create(res);
	  }

	  // ⍺.rank ≠ 0
	  if (a->rank != w->rank)
	  {
		  throw RankError(StringHelper::wstring_to_string(L"⌿: shapes of ⍺ & ⍵ must be equal (ranks " + std::to_wstring(a->rank) + L" vs " + std::to_wstring(w->rank) + L")", blame));
	  }
	  if (!Arrays::equals(a->shape, w->shape))
	  {
		  throw LengthError(StringHelper::wstring_to_string(L"⌿: shapes of ⍺ & ⍵ must be equal (" + Main::formatAPL(a->shape) + L" vs " + Main::formatAPL(w->shape) + L")", blame));
	  }

	  if (std::dynamic_pointer_cast<BitArr>(a) != nullptr)
	  {
		std::shared_ptr<BitArr> ab = std::static_pointer_cast<BitArr>(a);
		ab->setEnd(false);
		int sum = ab->isum();
		if (std::dynamic_pointer_cast<BitArr>(w) != nullptr)
		{
		  std::shared_ptr<BitArr::BA> res = std::make_shared<BitArr::BA>(sum);
		  std::vector<long long> wba = (std::static_pointer_cast<BitArr>(w))->arr;
		  (std::static_pointer_cast<BitArr>(a))->setEnd(false);
		  std::vector<long long> aba = (std::static_pointer_cast<BitArr>(a))->arr;
		  int ia = wba.size();

		  for (int i = 0; i < ia; i++)
		  {
			long long wcb = wba[i];
			long long acb = aba[i];
			for (int o = 0; o < 64; o++)
			{
			  if ((acb & 1) != 0)
			  {
				res->add(wcb & 1);
			  }
			  wcb >>= 1;
			  acb >>= 1;
			}
		  }
		  return res->finish();
		}
		if (w->quickDoubleArr())
		{
		  if (sum > w->ia * .96)
		  {
			std::vector<double> ds = w->asDoubleArr();
			std::vector<double> res(sum);

			std::vector<long long> la = ab->arr;
			int l = la.size();
			int am = 0, pos = 0;
			for (int i = 0; i < l; i++)
			{
			  long long c = la[i];
			  for (int s = 0; s < 64; s++)
			  {
				if ((c & 1) == 0)
				{
				  if (am != 0)
				  {
					  std::copy_n(ds.begin() + i * 64 + s - am, am, res.begin() + pos);
				  }
				  pos += am;
				  am = 0;
				}
				else
				{
					am++;
				}
				c >>= 1;
			  }
			}
			if (am > 0)
			{
				std::copy_n(ds.begin() + ds.size() - am, am, res.begin() + pos);
			}
			return std::make_shared<DoubleArr>(res);
		  }
		  std::vector<double> ds = w->asDoubleArr();
		  std::vector<double> res(sum);
		  std::vector<long long> la = ab->arr;
		  int l = la.size();
		  int pos = 0;
		  for (int i = 0; i < l; i++)
		  {
			long long c = la[i];
			for (int s = 0; s < 64; s++)
			{
			  if ((c & 1) != 0)
			  {
				res[pos++] = ds[i * 64 + s];
			  }
			  c >>= 1;
			}
		  }
		  return std::make_shared<DoubleArr>(res);
		  // BitArr.BR r = ab.read();
		  // int pos = 0;
		  // for (int i = 0; i < w.ia; i++) {
		  //   if (r.read()) {
		  //     res[pos++] = ds[i];
		  //   }
		  // }
		  // return new DoubleArr(res);
		}
		if (std::dynamic_pointer_cast<ChrArr>(w) != nullptr)
		{
		  std::wstring ws = (std::static_pointer_cast<ChrArr>(w))->s;
		  std::vector<wchar_t> chars(sum);
		  std::shared_ptr<BitArr::BR> r = ab->read();
		  int pos = 0;
		  for (int i = 0; i < w->ia; i++)
		  {
			if (r->read())
			{
			  chars[pos++] = ws[i];
			}
		  }
		  return std::make_shared<ChrArr>(chars);
		}
		std::vector<std::shared_ptr<Value>> res(sum);
		std::shared_ptr<BitArr::BR> r = ab->read();
		int pos = 0;
		for (int i = 0; i < w->ia; i++)
		{
		  if (r->read())
		  {
			res[pos++] = w[i];
		  }
		}
		return Arr::create(res);
	  }


	  int total = 0;
	  std::vector<int> sizes = a->asIntArr();
	  for (int i = 0; i < a->ia; i++)
	  {
		total += std::abs(sizes[i]);
	  }

	  if (std::dynamic_pointer_cast<BitArr>(w) != nullptr)
	  {
		std::shared_ptr<BitArr::BA> res = std::make_shared<BitArr::BA>(total);
		std::shared_ptr<BitArr::BR> r = (std::static_pointer_cast<BitArr>(w))->read();
		for (int i = 0; i < w->ia; i++)
		{
		  int am = sizes[i];
		  if (r->read())
		  {
			  res->fill(am);
		  }
		  else
		  {
			  res->skip(am);
		  }
		}
		return res->finish();
	  }
	  if (w->quickDoubleArr())
	  {
		int ptr = 0;
		std::vector<double> wi = w->asDoubleArr();
		std::vector<double> res(total);
		for (int i = 0; i < a->ia; i++)
		{
		  double c = wi[i];
		  int am = sizes[i];
		  if (sizes[i] < 0)
		  {
			for (int j = 0; j > am; j--)
			{
			  res[ptr++] = 0;
			}
		  }
		  else
		  {
			for (int j = 0; j < am; j++)
			{
			  res[ptr++] = c;
			}
		  }
		}
		return std::make_shared<DoubleArr>(res);

	  }
	  else
	  {
		int ptr = 0;
		std::vector<std::shared_ptr<Value>> res(total);
		for (int i = 0; i < a->ia; i++)
		{
		  std::shared_ptr<Value> c = w[i];
		  int am = sizes[i];
		  if (sizes[i] < 0)
		  {
			am = -am;
			c = c->prototype();
		  }
		  for (int j = 0; j < am; j++)
		  {
			res[ptr++] = c;
		  }
		}
		return Arr::create(res);
	  }
	}

	std::shared_ptr<Value> ReplicateBuiltin::underW(std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  std::shared_ptr<Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(a, w)) : std::static_pointer_cast<Value>(o);
	  return AtBuiltin::at(v, std::make_shared<FunAnonymousInnerClass>(shared_from_this(), a)
	 , w, -1234, shared_from_this());
	}

	ReplicateBuiltin::FunAnonymousInnerClass::FunAnonymousInnerClass(std::shared_ptr<ReplicateBuiltin> outerInstance, std::shared_ptr<APL::types::Value> a) : outerInstance(outerInstance)
	{
		this->a = a;
	}

	std::wstring ReplicateBuiltin::FunAnonymousInnerClass::repr()
	{
		return L"{⌿.⍺}";
	}

	std::shared_ptr<Value> ReplicateBuiltin::FunAnonymousInnerClass::call(std::shared_ptr<Value> w)
	{
		return a;
	}
}
