#include <APL/types/functions/Mop.h>
#include <APL/errors/IncorrectArgsError.h>
#include <APL/errors/DomainError.h>
#include <APL/errors/SyntaxError.h>

namespace APL::types::functions
{
    // using namespace APL;
    // using namespace APL::errors;
    // using namespace APL::types;

    Mop::Mop(std::shared_ptr<Scope> sc) : Callable(sc)
    {
    }

    Mop::Mop() : Callable(nullptr)
    {
    }

    APL::Type Mop::type()
    {
      return Type::mop;
    }

    std::shared_ptr<DerivedMop> Mop::derive(std::shared_ptr<APL::types::Obj> aa)
    {
      return std::make_shared<DerivedMop>(aa, shared_from_this());
    }

    std::shared_ptr<APL::types::Value> Mop::call(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv)
    {
      throw IncorrectArgsError(StringHelper::wstring_to_string(repr() + L" can't be called monadically", derv, w));
    }

    std::shared_ptr<APL::types::Value> Mop::call(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv)
    {
      throw IncorrectArgsError(StringHelper::wstring_to_string(repr() + L" can't be called dyadically", derv, a));
    }

    std::shared_ptr<APL::types::Obj> Mop::callObj(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv)
    { // if overridden, call(f, w, derv) must be overridden too!
      return call(f, w, derv);
    }

    std::shared_ptr<APL::types::Obj> Mop::callObj(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv)
    { // if overridden, call(f, a, w, derv) must be overridden too!
      return call(f, a, w, derv);
    }

    std::shared_ptr<APL::types::Value> Mop::callInv(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> w)
    {
      throw DomainError(shared_from_this() + L" doesn't support monadic inverting", shared_from_this(), w);
    }

    std::shared_ptr<APL::types::Value> Mop::callInvW(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      throw DomainError(shared_from_this() + L" doesn't support dyadic inverting of ⍵", shared_from_this(), w);
    }

    std::shared_ptr<APL::types::Value> Mop::callInvA(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      throw DomainError(shared_from_this() + L" doesn't support dyadic inverting of ⍺", shared_from_this(), w);
    }

    std::shared_ptr<APL::types::Value> Mop::under(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv)
    {
      std::shared_ptr<APL::types::Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(aa, w, derv)) : std::static_pointer_cast<APL::types::Value>(o);
      return callInv(aa, v);
    }

    std::shared_ptr<APL::types::Value> Mop::underW(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv)
    {
      std::shared_ptr<APL::types::Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(aa, a, w, derv)) : std::static_pointer_cast<APL::types::Value>(o);
      return callInvW(aa, a, v);
    }

    std::shared_ptr<APL::types::Value> Mop::underA(std::shared_ptr<APL::types::Obj> aa, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv)
    {
      std::shared_ptr<APL::types::Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(aa, a, w, derv)) : std::static_pointer_cast<APL::types::Value>(o);
      return callInvA(aa, v, w);
    }

    std::string Mop::toString()
    {
      return repr();
    }

    std::shared_ptr<Fun> Mop::isFn(std::shared_ptr<APL::types::Obj> o)
    {
      if (!(std::dynamic_pointer_cast<Fun>(o) != nullptr))
      {
          throw SyntaxError(StringHelper::wstring_to_string(repr() + L": ⍶ must be a function", shared_from_this()));
      }
      return std::static_pointer_cast<Fun>(o);
    }

    int Mop::hashCode()
    {
      return actualHashCode();
    }

    bool Mop::equals(std::shared_ptr<APL::types::Obj> o)
    {
      return shared_from_this() == o;
    }
}
