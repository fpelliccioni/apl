#include <APL/types/functions/FunArr.h>
#include <APL/types/Arr.h>

namespace APL::types::functions
{
    // using namespace APL::types;

    FunArr::FunArr(std::vector<std::shared_ptr<APL::types::Obj>> &os) : os(os)
    {
    }

    std::string FunArr::repr()
    {
      std::shared_ptr<StringBuilder> res = std::make_shared<StringBuilder>(L"(");
      bool first = true;
      for (auto o : os)
      {
        if (first)
        {
            first = false;
        }
        else
        {
            res->append(L"⋄");
        }
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
        res->append(o->toString());
      }
      res->append(L")");
      return res->toString();
    }

    std::shared_ptr<APL::types::Value> FunArr::call(std::shared_ptr<APL::types::Value> w)
    {
      std::vector<std::shared_ptr<APL::types::Value>> vs(os.size());
      for (int i = 0; i < os.size(); i++)
      {
        vs[i] = (std::static_pointer_cast<Fun>(os[i]))->call(w);
      }
      return Arr::create(vs);
    }

    std::shared_ptr<APL::types::Value> FunArr::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      std::vector<std::shared_ptr<APL::types::Value>> vs(os.size());
      for (int i = 0; i < os.size(); i++)
      {
        vs[i] = (std::static_pointer_cast<Fun>(os[i]))->call(a, w);
      }
      return Arr::create(vs);
    }
}
