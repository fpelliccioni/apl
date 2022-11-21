#include <APL/types/functions/builtins/SetBuiltin.h>
#include <APL/types/Settable.h>
#include <APL/types/Variable.h>

namespace APL::types::functions::builtins
{
    using SyntaxError = APL::errors::SyntaxError;
    // using namespace APL::types;
    using VarArr = APL::types::functions::VarArr;
const std::shared_ptr<APL::types::functions::builtins::SetBuiltin> SetBuiltin::inst = std::make_shared<APL::types::functions::builtins::SetBuiltin>();

    std::string SetBuiltin::toString()
    {
      return L"←";
    }

    std::shared_ptr<APL::types::Obj> SetBuiltin::callObj(std::shared_ptr<APL::types::Obj> a, std::shared_ptr<APL::types::Obj> w, bool update)
    {
      if (!(std::dynamic_pointer_cast<Settable>(a) != nullptr))
      {
          throw SyntaxError(a + L" isn't settable", a);
      }
      std::shared_ptr<Settable> as = std::static_pointer_cast<Settable>(a);
      if (update)
      {
        if (std::dynamic_pointer_cast<Variable>(a) != nullptr)
        {
            (std::static_pointer_cast<Variable>(a))->update(w);
        }
        else if (std::dynamic_pointer_cast<VarArr>(a) != nullptr)
        {
            (std::static_pointer_cast<VarArr>(a))->set(w, true);
        }
        else
        {
            as->set(w, shared_from_this()); // throw new SyntaxError("can't set", a); todo?
        }
      }
      else
      {
        as->set(w, shared_from_this());
      }
      return w;
    }

    std::shared_ptr<APL::types::Obj> SetBuiltin::callObj(std::shared_ptr<Fun> f, std::shared_ptr<APL::types::Obj> a, std::shared_ptr<APL::types::Value> w)
    {
      callObj(a, f->call(std::static_pointer_cast<APL::types::Value>((std::static_pointer_cast<Settable>(a))->get()), w), true);
      return w;
    }
}
