#include <APL/DerivedSet.h>
#include <APL/types/Settable.h>
#include <APL/types/Value.h>

namespace APL::types::functions::builtins
{
    // using namespace APL::types;

    DerivedSet::DerivedSet(std::shared_ptr<APL::types::functions::builtins::SetBuiltin> s, std::shared_ptr<Fun> f) : s(s), f(f)
    {
    }

    std::shared_ptr<APL::types::Obj> DerivedSet::callObj(std::shared_ptr<APL::types::Obj> a, std::shared_ptr<APL::types::Obj> w, bool update)
    {
      s->callObj(a, f->call(std::static_pointer_cast<APL::types::Value>((std::static_pointer_cast<Settable>(a))->get()), std::static_pointer_cast<APL::types::Value>(w)), update);
      return w;
    }

    std::string DerivedSet::toString()
    {
      return f->repr() + L"←";
    }
}
