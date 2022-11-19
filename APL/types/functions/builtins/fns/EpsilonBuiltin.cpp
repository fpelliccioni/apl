#include <APL/EpsilonBuiltin.h>
#include <APL/Arr.h>
#include <APL/Primitive.h>
#include <APL/arrs/BitArr.h>
#include <APL/Num.h>
#include <APL/arrs/ChrArr.h>
#include <APL/Char.h>
#include <APL/Fun.h>

namespace APL::types::functions::builtins::fns
{
	using DomainError = APL::errors::DomainError;
	using namespace APL::types;
	using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;
	using ArrayList = java::util::ArrayList;

	std::wstring EpsilonBuiltin::repr()
	{
	  return L"∊";
	}

	std::shared_ptr<Value> EpsilonBuiltin::call(std::shared_ptr<Value> w)
	{
	  auto res = std::vector<std::shared_ptr<Value>>();
	  rec(res, w);
	  return Arr::create(res);
	}

	void EpsilonBuiltin::rec(std::vector<std::shared_ptr<Value>> &arr, std::shared_ptr<Value> v)
	{
	  if (std::dynamic_pointer_cast<Primitive>(v) != nullptr)
	  {
		arr.push_back(v);
	  }
	  else
	  {
		if (std::dynamic_pointer_cast<BitArr>(v) != nullptr)
		{
		  std::shared_ptr<BitArr> ba = std::static_pointer_cast<BitArr>(v);
		  for (int i = 0; i < ba->ia; i++)
		  {
			  arr.push_back(ba[i]);
		  }
		}
		else if (v->quickDoubleArr())
		{
		  for (auto d : v->asDoubleArr())
		  {
			  arr.push_back(Num::of(d));
		  }
		}
		else if (std::dynamic_pointer_cast<ChrArr>(v) != nullptr)
		{
		  std::wstring s = (std::static_pointer_cast<ChrArr>(v))->s;
		  for (int i = 0; i < s.length(); i++)
		  {
			arr.push_back(Char::of(s[i]));
		  }
		}
		else
		{
			for (auto c : v)
			{
				rec(arr, c);
			}
		}
	  }
	}

	std::shared_ptr<Value> EpsilonBuiltin::call(std::shared_ptr<Value> a, std::shared_ptr<Value> w)
	{
	  if (a->scalar())
	  {
		std::shared_ptr<Value> a1 = a->first();
		for (auto v : w)
		{
		  if (v->equals(a1))
		  {
			return Num::ONE;
		  }
		}
		return Num::ZERO;
	  }
	  std::shared_ptr<BitArr::BA> ba = std::make_shared<BitArr::BA>(a->shape);
	  for (int i = 0; i < a->ia; i++)
	  {
		std::shared_ptr<Value> av = a[i];
		bool b = false;
		for (auto v : w)
		{
		  if (v->equals(av))
		  {
			b = true;
			break;
		  }
		}
		ba->add(b);
	  }
	  return ba->finish();
	}

	std::shared_ptr<Value> EpsilonBuiltin::under(std::shared_ptr<Obj> o, std::shared_ptr<Value> w)
	{
	  std::shared_ptr<Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(w)) : std::static_pointer_cast<Value>(o);
	  std::vector<std::shared_ptr<Value>> vs = v->values();
	  std::vector<std::shared_ptr<Value>> res(w->ia);
	  int e = copyIn(res, vs, w, 0);
	  if (e != v->ia)
	  {
		  throw DomainError(L"⍢∊ expected equal amount of output & output items", shared_from_this());
	  }
	  return Arr::create(res, w->shape);
	}

	int EpsilonBuiltin::copyIn(std::vector<std::shared_ptr<Value>> &res, std::vector<std::shared_ptr<Value>> &vs, std::shared_ptr<Value> orig, int s)
	{
	  for (int i = 0; i < orig->ia; i++)
	  {
		std::shared_ptr<Value> origN = orig[i];
		if (std::dynamic_pointer_cast<Primitive>(origN) != nullptr)
		{
		  res[i] = vs[s++];
		}
		else
		{
		  std::vector<std::shared_ptr<Value>> resN(origN->ia);
		  s = copyIn(resN, vs, origN, s);
		  res[i] = Arr::create(resN, origN->shape);
		}
	  }
	  return s;
	}
}
