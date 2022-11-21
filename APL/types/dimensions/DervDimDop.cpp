#include <APL/DervDimDop.h>
#include <APL/DimDDop.h>
#include <APL/DimMDop.h>

namespace APL::types::dimensions
{
    using Scope = APL::Scope;
    using SyntaxError = APL::errors::SyntaxError;
    // using namespace APL::types;
    // using namespace APL::types::functions;

    std::string DervDimDop::repr()
    {
      return f->repr() + L"[" + std::to_wstring(dim) + L"]";
    }

    DervDimDop::DervDimDop(std::shared_ptr<Dop> f, std::optional<int> &dim, std::shared_ptr<Scope> sc) : Dop(sc), f(f)
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

    std::shared_ptr<APL::types::Value> DervDimDop::call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv)
    {
      if (!(std::dynamic_pointer_cast<DimDDop>(f) != nullptr))
      {
          throw SyntaxError(L"Attempt to call function dyadically that doesn't support dimension specification", a);
      }
      return (std::static_pointer_cast<DimDDop>(f))->call(aa, ww, a, w, dim);
    }

    std::shared_ptr<APL::types::Value> DervDimDop::call(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedDop> derv)
    {
      if (!(std::dynamic_pointer_cast<DimMDop>(f) != nullptr))
      {
          throw SyntaxError(L"Attempt to call function monadically that doesn't support dimension specification", w);
      }
      return (std::static_pointer_cast<DimMDop>(f))->call(aa, ww, w, dim);
    }
}
