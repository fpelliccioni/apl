#include <APL/types/functions/DerivedDop.h>
#include <APL/types/Arr.h>

namespace APL::types::functions
{
    // using namespace APL::types;

    DerivedDop::DerivedDop(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> ww, std::shared_ptr<Dop> op) : aa(aa), ww(ww), op(op)
    {
      token = op->token;
    }

    std::shared_ptr<APL::types::Value> DerivedDop::call(std::shared_ptr<APL::types::Value> w)
    {
      return op->call(aa, ww, w, shared_from_this());
    }

    std::shared_ptr<APL::types::Value> DerivedDop::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      return op->call(aa, ww, a, w, shared_from_this());
    }

    std::shared_ptr<APL::types::Obj> DerivedDop::callObj(std::shared_ptr<APL::types::Value> w)
    {
      return op->callObj(aa, ww, w, shared_from_this());
    }

    std::shared_ptr<APL::types::Obj> DerivedDop::callObj(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      return op->callObj(aa, ww, a, w, shared_from_this());
    }

    std::shared_ptr<APL::types::Value> DerivedDop::callInv(std::shared_ptr<APL::types::Value> w)
    {
      return op->callInv(aa, ww, w);
    }

    std::shared_ptr<APL::types::Value> DerivedDop::callInvW(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      return op->callInvW(aa, ww, a, w);
    }

    std::shared_ptr<APL::types::Value> DerivedDop::callInvA(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      return op->callInvA(aa, ww, a, w);
    }

    std::string DerivedDop::repr()
    {
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
      std::string wws = ww->toString();
      if (!(std::dynamic_pointer_cast<Arr>(ww) != nullptr) && wws.length() != 1)
      {
          wws = L"(" + wws + L")";
      }
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
      return aa->toString() + op->repr() + wws;
    }

    std::shared_ptr<APL::types::Value> DerivedDop::under(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w)
    {
      return op->under(aa, ww, o, w, shared_from_this());
    }

    std::shared_ptr<APL::types::Value> DerivedDop::underW(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      return op->underW(aa, ww, o, a, w, shared_from_this());
    }

    std::shared_ptr<APL::types::Value> DerivedDop::underA(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      return op->underA(aa, ww, o, a, w, shared_from_this());
    }
}
