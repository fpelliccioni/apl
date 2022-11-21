#include <APL/Pick.h>

namespace APL::types::dimensions
{
    using Scope = APL::Scope;
    // using namespace APL::types;
    using AtBuiltin = APL::types::functions::builtins::dops::AtBuiltin;
    using RShoeUBBuiltin = APL::types::functions::builtins::fns::RShoeUBBuiltin;

    Pick::Pick(std::shared_ptr<Variable> var, std::shared_ptr<Brackets> where, std::shared_ptr<Scope> sc) : Settable(nullptr), var(var), val(std::static_pointer_cast<APL::types::Value>(var->get())), idx(where->val), IO(sc->IO), obj(where)
    {
    }

    void Pick::set(std::shared_ptr<APL::types::Obj> v, std::shared_ptr<APL::types::Callable> blame)
    {
      var->update(AtBuiltin::at(v, idx, val, IO, blame));
    }

    std::shared_ptr<APL::types::Obj> Pick::get()
    {
      return RShoeUBBuiltin::on(idx, val, IO, obj);
    }

    std::shared_ptr<APL::types::Obj> Pick::getOrThis()
    {
      return get();
    }

    std::string Pick::toString()
    {
      return var->name + L"[" + val + L"]";
    }
}
