#include <APL/EpsilonBuiltin.h>
#include <APL/types/Arr.h>
#include <APL/types/Primitive.h>
#include <APL/types/arrs/BitArr.h>
#include <APL/types/Num.h>
#include <APL/types/arrs/ChrArr.h>
#include <APL/types/Char.h>
#include <APL/types/Fun.h>

namespace APL::types::functions::builtins::fns
{
	using DomainError = APL::errors::DomainError;
	// using namespace APL::types;
	// using namespace APL::types::arrs;
	using Builtin = APL::types::functions::Builtin;
	// using ArrayList = java::util::ArrayList;

	std::string EpsilonBuiltin::repr()
	{
	  return L"∊";
	}

	std::shared_ptr<APL::types::Value> EpsilonBuiltin::call(std::shared_ptr<APL::types::Value> w)
	{
	  auto res = std::vector<std::shared_ptr<APL::types::Value>>();
	  rec(res, w);
	  return Arr::create(res);
	}

	void EpsilonBuiltin::rec(std::vector<std::shared_ptr<APL::types::Value>> &arr, std::shared_ptr<APL::types::Value> v)
	{
	  if (std::dynamic_pointer_cast<Primitive>(v) != nullptr)
	  {
		arr.push_back(v);
	  }
	  else
	  {
		if (std::dynamic_pointer_cast<APL::types::arrs::BitArr>(v) != nullptr)
		{
		  std::shared_ptr<APL::types::arrs::BitArr> ba = std::static_pointer_cast<APL::types::arrs::BitArr>(v);
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
		else if (std::dynamic_pointer_cast<APL::types::arrs::ChrArr>(v) != nullptr)
		{
		  std::string s = (std::static_pointer_cast<APL::types::arrs::ChrArr>(v))->s;
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

	std::shared_ptr<APL::types::Value> EpsilonBuiltin::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  if (a->scalar())
	  {
		std::shared_ptr<APL::types::Value> a1 = a->first();
		for (auto v : w)
		{
		  if (v->equals(a1))
		  {
			return Num::ONE;
		  }
		}
		return Num::ZERO;
	  }
	  std::shared_ptr<APL::types::arrs::BitArr::BA> ba = std::make_shared<APL::types::arrs::BitArr::BA>(a->shape);
	  for (int i = 0; i < a->ia; i++)
	  {
		std::shared_ptr<APL::types::Value> av = a[i];
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

	std::shared_ptr<APL::types::Value> EpsilonBuiltin::under(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w)
	{
	  std::shared_ptr<APL::types::Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(w)) : std::static_pointer_cast<APL::types::Value>(o);
	  std::vector<std::shared_ptr<APL::types::Value>> vs = v->values();
	  std::vector<std::shared_ptr<APL::types::Value>> res(w->ia);
	  int e = copyIn(res, vs, w, 0);
	  if (e != v->ia)
	  {
		  throw DomainError(L"⍢∊ expected equal amount of output & output items", shared_from_this());
	  }
	  return Arr::create(res, w->shape);
	}

	int EpsilonBuiltin::copyIn(std::vector<std::shared_ptr<APL::types::Value>> &res, std::vector<std::shared_ptr<APL::types::Value>> &vs, std::shared_ptr<APL::types::Value> orig, int s)
	{
	  for (int i = 0; i < orig->ia; i++)
	  {
		std::shared_ptr<APL::types::Value> origN = orig[i];
		if (std::dynamic_pointer_cast<Primitive>(origN) != nullptr)
		{
		  res[i] = vs[s++];
		}
		else
		{
		  std::vector<std::shared_ptr<APL::types::Value>> resN(origN->ia);
		  s = copyIn(resN, vs, origN, s);
		  res[i] = Arr::create(resN, origN->shape);
		}
	  }
	  return s;
	}
}
