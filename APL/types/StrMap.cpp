#include <APL/StrMap.h>
#include <APL/Null.h>
#include <APL/Main.h>

namespace APL::types
{
    // using namespace APL;
    using HArr = APL::types::arrs::HArr;

    StrMap::StrMap(std::shared_ptr<Scope> sc) : vals(sc->vars)
    {
      // this.sc = sc;
    }

    StrMap::StrMap(std::unordered_map<std::string, std::shared_ptr<APL::types::Obj>> &vals) : vals(vals)
    {
    }

    StrMap::StrMap() : vals(std::unordered_map<std::string, Obj>())
    {
      // this.sc = null;
    }

    std::shared_ptr<APL::types::Obj> StrMap::getRaw(std::shared_ptr<APL::types::Value> k)
    {
      return getRaw(k->asString());
    }

    std::shared_ptr<APL::types::Obj> StrMap::getRaw(std::string const& k)
    {
      std::shared_ptr<APL::types::Obj> v = vals[k];
      if (v == nullptr)
      {
          return Null::NULL;
      }
      return v;
    }

    void StrMap::set(std::shared_ptr<APL::types::Value> k, std::shared_ptr<APL::types::Obj> v)
    {
      if (v == Null::NULL)
      {
          vals.erase(k->asString());
      }
      else
      {
          vals.emplace(k->asString(), v);
      }
    }

    void StrMap::setStr(std::string const& k, std::shared_ptr<APL::types::Obj> v)
    {
      if (v == Null::NULL)
      {
          vals.erase(k);
      }
      else
      {
          vals.emplace(k, v);
      }
    }

    std::shared_ptr<Arr> StrMap::allValues()
    {
      auto items = std::vector<std::shared_ptr<APL::types::Value>>();
      for (auto o : vals)
      {
        if (std::dynamic_pointer_cast<APL::types::Value>(o->second) != nullptr)
        {
            items.push_back(std::static_pointer_cast<APL::types::Value>(o->second));
        }
      }
      return Arr::create(items);
    }

    std::shared_ptr<Arr> StrMap::allKeys()
    {
      auto items = std::vector<std::shared_ptr<APL::types::Value>>();
      for (auto o : vals)
      {
        items.push_back(Main::toAPL(o.first));
      }
      return Arr::create(items);
    }

    std::shared_ptr<Arr> StrMap::kvPair()
    {
      std::vector<std::shared_ptr<APL::types::Value>> ks;
      std::vector<std::shared_ptr<APL::types::Value>> vs;
      vals.forEach([&] (k, v)
      {
      if (std::dynamic_pointer_cast<APL::types::Value>(v) != nullptr)
      {
          ks.push_back(Main::toAPL(k));
          vs.push_back(std::static_pointer_cast<APL::types::Value>(v));
      }
      });
      return std::make_shared<HArr>(std::vector<std::shared_ptr<APL::types::Value>>{std::make_shared<HArr>(ks), Arr::create(vs)});
    }

    int StrMap::size()
    {
      return vals.size();
    }

    bool StrMap::equals(std::shared_ptr<APL::types::Obj> o)
    {
      return std::dynamic_pointer_cast<StrMap>(o) != nullptr && vals.equals((std::static_pointer_cast<StrMap>(o))->vals);
    }

    std::string StrMap::toString()
    {
      std::shared_ptr<StringBuilder> res = std::make_shared<StringBuilder>(L"(");
      vals.forEach([&] (key, value)
      {
      if (res->length() != 1)
      {
          res->append(L" ⋄ ");
      }
      res->append(key)->append(L":")->append(value);
      });
      return res + L")";
    }
}
