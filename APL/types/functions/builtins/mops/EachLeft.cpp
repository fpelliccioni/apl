#include <APL/EachLeft.h>
#include <APL/types/Fun.h>
#include <APL/types/Arr.h>
#include <APL/EachBuiltin.h>

namespace APL::types::functions::builtins::mops
{
    // using namespace APL::types;
    using Rank0Arr = APL::types::arrs::Rank0Arr;
    // using namespace APL::types::functions;

    std::string EachLeft::repr()
    {
      return L"ᐵ";
    }

    std::shared_ptr<APL::types::Value> EachLeft::call(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv)
    {
      std::shared_ptr<Fun> ff = isFn(f);
      std::vector<std::shared_ptr<APL::types::Value>> n(a->ia);
      for (int i = 0; i < n.size(); i++)
      {
          n[i] = ff->call(a[i], w);
      }
      return Arr::createL(n, a->shape);
    }

    std::shared_ptr<APL::types::Value> EachLeft::underW(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv)
    {
      return EachBuiltin::underW(isFn(aa), o, a, std::make_shared<Rank0Arr>(w), shared_from_this());
    }
}
