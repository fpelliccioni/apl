#include <APL/KeyBuiltin.h>
#include <APL/errors/DomainError.h>
#include <APL/types/APLMap.h>
#include <APL/types/Arr.h>
#include <APL/types/Fun.h>
#include <APL/types/Num.h>
#include <APL/errors/RankError.h>
#include <APL/Main.h>
#include <APL/errors/LengthError.h>

namespace APL::types::functions::builtins::mops
{
    // using namespace APL;
    // using namespace APL::errors;
    // using namespace APL::types;
    using HArr = APL::types::arrs::HArr;
    // using namespace APL::types::functions;

    std::string KeyBuiltin::repr()
    {
      return L"⌸";
    }

    KeyBuiltin::KeyBuiltin(std::shared_ptr<Scope> sc) : Mop(sc)
    {
    }

    std::shared_ptr<APL::types::Value> KeyBuiltin::call(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv)
    {
      std::shared_ptr<APL::types::Obj> o = callObj(f, w, derv);
      if (std::dynamic_pointer_cast<APL::types::Value>(o) != nullptr)
      {
          return std::static_pointer_cast<APL::types::Value>(o);
      }
      throw DomainError(StringHelper::wstring_to_string(L"Was expected to give array, got " + o->humanType(true), shared_from_this()));
    }

    std::shared_ptr<APL::types::Obj> KeyBuiltin::callObj(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv)
    {
      if (std::dynamic_pointer_cast<APLMap>(aa) != nullptr)
      {
        if (w->rank > 1)
        {
          std::vector<std::shared_ptr<APL::types::Value>> arr(w->ia);
          for (int i = 0; i < w->ia; i++)
          {
            arr[i] = std::static_pointer_cast<APL::types::Value>((std::static_pointer_cast<APLMap>(aa))->getRaw(w[i]));
          }
          return Arr::create(arr, w->shape);
        }
        return (std::static_pointer_cast<APLMap>(aa))->getRaw(w);
      }
      if (std::dynamic_pointer_cast<Fun>(aa) != nullptr)
      {
        int i = sc->IO;
        auto vals = std::unordered_map<std::shared_ptr<APL::types::Value>, std::vector<std::shared_ptr<APL::types::Value>>>();
        auto order = std::vector<std::shared_ptr<APL::types::Value>>();
        for (auto v : w)
        {
          if (vals.find(v) == vals.end())
          {
            auto l = std::vector<std::shared_ptr<APL::types::Value>>();
            l.push_back(Num::of(i));
            vals.emplace(v, l);
            order.push_back(v);
          }
          else
          {
            vals[v].push_back(Num::of(i));
          }
          i++;
        }
        auto *res = std::vector<std::shared_ptr<APL::types::Value>>(order.size());
        i = 0;
        for (auto c : order)
        {
          res[i++] = (std::static_pointer_cast<Fun>(aa))->call(c, Arr::create(vals[c]));
        }
        return std::make_shared<HArr>(res);
      }
      throw DomainError(StringHelper::wstring_to_string(L"⌸: ⍶ must be a function or a map, was " + aa->humanType(true), derv, aa));
    }

    std::shared_ptr<APL::types::Value> KeyBuiltin::call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv)
    {
      if (std::dynamic_pointer_cast<APLMap>(aa) != nullptr)
      {
        (std::static_pointer_cast<APLMap>(aa))[a] = w;
        return w;
      }
      if (std::dynamic_pointer_cast<Fun>(aa) != nullptr)
      {
		std::shared_ptr<Fun> aaf = std::static_pointer_cast<Fun>(aa);
		if (!Arrays::equals(a->shape, w->shape))
		{
		  if (a->rank != w->rank)
		  {
			  throw RankError(StringHelper::wstring_to_string(L"dyadic ⌸ expected ⍺ & ⍵ to have equal ranks (" + std::to_wstring(a->rank) + L" vs " + std::to_wstring(w->rank) + L")", derv, w));
		  }
		  throw LengthError(StringHelper::wstring_to_string(L"dyadic ⌸ expected ⍺ & ⍵ to have equal shapes (" + Main::formatAPL(a->shape) + L" vs " + Main::formatAPL(w->shape) + L")", derv, w));
		}
		std::unordered_map<std::shared_ptr<APL::types::Value>, std::vector<std::shared_ptr<APL::types::Value>>> vals;
		std::vector<std::shared_ptr<APL::types::Value>> order;
		for (int i = 0; i < a->ia; i++)
		{
		  std::shared_ptr<APL::types::Value> k = w[i];
		  std::shared_ptr<APL::types::Value> v = a[i];
		  std::vector<std::shared_ptr<APL::types::Value>> curr = vals[k];
		  if (curr.empty())
		  {
			std::vector<std::shared_ptr<APL::types::Value>> newArr;
			vals.emplace(k, newArr);
			curr = newArr;
			order.push_back(k);
		  }
		  curr.push_back(v);
		}
		std::vector<std::shared_ptr<APL::types::Value>> res(order.size());
		for (int i = 0; i < order.size(); i++)
		{
		  std::shared_ptr<APL::types::Value> k = order[i];
		  std::shared_ptr<APL::types::Value> vs = Arr::create(vals[k]);
		  res[i] = aaf->call(k, vs);
		}
		return Arr::create(res);
	  }
	  throw DomainError(StringHelper::wstring_to_string(L"⌸: ⍶ must be a function or a map, was " + aa->humanType(true), derv, aa));
	}
}
