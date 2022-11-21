#include <APL/types/functions/DerivedMop.h>

namespace APL::types::functions
{
    // using namespace APL::types;
    using TableBuiltin = APL::types::functions::builtins::mops::TableBuiltin;

    DerivedMop::DerivedMop(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<Mop> op) : aa(aa), op(op)
    {
      token = op->token;
    }

    std::shared_ptr<APL::types::Value> DerivedMop::call(std::shared_ptr<APL::types::Value> w)
    {
      return op->call(aa, w, shared_from_this());
    }

    std::shared_ptr<APL::types::Value> DerivedMop::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      return op->call(aa, a, w, shared_from_this());
    }

    std::shared_ptr<APL::types::Obj> DerivedMop::callObj(std::shared_ptr<APL::types::Value> w)
    {
      return op->callObj(aa, w, shared_from_this());
    }

    std::shared_ptr<APL::types::Obj> DerivedMop::callObj(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      return op->callObj(aa, a, w, shared_from_this());
    }

    std::shared_ptr<APL::types::Value> DerivedMop::callInv(std::shared_ptr<APL::types::Value> w)
    {
      return op->callInv(aa, w);
    }

    std::shared_ptr<APL::types::Value> DerivedMop::callInvW(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      return op->callInvW(aa, a, w);
    }

    std::shared_ptr<APL::types::Value> DerivedMop::callInvA(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      return op->callInvA(aa, a, w);
    }

    std::string DerivedMop::repr()
    {
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
      return std::dynamic_pointer_cast<TableBuiltin>(op) != nullptr? L"∘." + aa->toString() : aa->toString() + op->repr();
    }

    std::shared_ptr<APL::types::Value> DerivedMop::under(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w)
    {
      return op->under(aa, o, w, shared_from_this());
    }

    std::shared_ptr<APL::types::Value> DerivedMop::underW(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      return op->underW(aa, o, a, w, shared_from_this());
    }

    std::shared_ptr<APL::types::Value> DerivedMop::underA(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      return op->underA(aa, o, a, w, shared_from_this());
    }
}
