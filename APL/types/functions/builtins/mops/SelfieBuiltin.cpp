#include <APL/SelfieBuiltin.h>
#include <APL/types/Fun.h>

namespace APL::types::functions::builtins::mops
{
    using DomainError = APL::errors::DomainError;
    // using namespace APL::types;
    // using namespace APL::types::functions;

    std::string SelfieBuiltin::repr()
    {
      return L"⍨";
    }

    std::shared_ptr<APL::types::Value> SelfieBuiltin::call(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv)
    {
      if (std::dynamic_pointer_cast<Fun>(f) != nullptr)
      {
          return (std::static_pointer_cast<Fun>(f))->call(w, w);
      }
      return std::static_pointer_cast<APL::types::Value>(f);
    }

    std::shared_ptr<APL::types::Value> SelfieBuiltin::call(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv)
    {
      if (std::dynamic_pointer_cast<Fun>(f) != nullptr)
      {
          return (std::static_pointer_cast<Fun>(f))->call(w, a);
      }
      return std::static_pointer_cast<APL::types::Value>(f);
    }

    std::shared_ptr<APL::types::Value> SelfieBuiltin::callInvW(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      if (std::dynamic_pointer_cast<Fun>(f) != nullptr)
      {
          return (std::static_pointer_cast<Fun>(f))->callInvA(w, a);
      }
      throw DomainError(L"A⍨ cannot be inverted", shared_from_this());
    }

    std::shared_ptr<APL::types::Value> SelfieBuiltin::callInvA(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      if (std::dynamic_pointer_cast<Fun>(f) != nullptr)
      {
          return (std::static_pointer_cast<Fun>(f))->callInvW(w, a);
      }
      throw DomainError(L"A⍨ cannot be inverted", shared_from_this());
    }
}
