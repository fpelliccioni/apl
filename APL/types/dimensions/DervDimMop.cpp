#include <APL/DervDimMop.h>
#include <APL/DimDMop.h>
#include <APL/types/dimensions/DimMMop.h>

namespace APL::types::dimensions
{
    using Scope = APL::Scope;
    using SyntaxError = APL::errors::SyntaxError;
    // using namespace APL::types;
    // using namespace APL::types::functions;

    DervDimMop::DervDimMop(std::shared_ptr<Mop> f, std::optional<int> &dim, std::shared_ptr<Scope> sc) : Mop(sc), f(f)
    {
      if (!dim)
      {
          this->dim = 0;
      }
      else if (dim < 0)
      {
          this->dim = dim.value();
      }
      else
      {
          this->dim = dim.value() - sc->IO;
      }
      this->token = f->token;

    }

    std::shared_ptr<APL::types::Value> DervDimMop::call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv)
    {
      if (!(std::dynamic_pointer_cast<DimDMop>(f) != nullptr))
      {
          throw SyntaxError(L"Attempt to call function dyadically that doesn't support dimension specification", a);
      }
      return (std::static_pointer_cast<DimDMop>(f))->call(aa, a, w, dim);
    }

    std::shared_ptr<APL::types::Value> DervDimMop::call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv)
    {
      if (!(std::dynamic_pointer_cast<DimMMop>(f) != nullptr))
      {
          throw SyntaxError(L"Attempt to call function monadically that doesn't support dimension specification", w);
      }
      return (std::static_pointer_cast<DimMMop>(f))->call(aa, w, dim);
    }

    std::string DervDimMop::repr()
    {
      return f->repr() + L"[" + std::to_wstring(dim) + L"]";
    }
}
