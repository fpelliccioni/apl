#include <APL/Fork.h>

namespace APL::types::functions::trains
{
    using DomainError = APL::errors::DomainError;
    // using namespace APL::types;

    Fork::Fork(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<Fun> g, std::shared_ptr<Fun> h) : f(f), g(g), h(h)
    {
    }

    std::shared_ptr<APL::types::Value> Fork::call(std::shared_ptr<APL::types::Value> w)
    {
      std::shared_ptr<APL::types::Value> right = h->call(w);
      std::shared_ptr<APL::types::Value> left = !(std::dynamic_pointer_cast<Fun>(f) != nullptr)? std::static_pointer_cast<APL::types::Value>(f) : (std::static_pointer_cast<Fun>(f))->call(w);
      return g->call(left, right);
    }

    std::shared_ptr<APL::types::Value> Fork::callInv(std::shared_ptr<APL::types::Value> w)
    {
      if (std::dynamic_pointer_cast<Fun>(f) != nullptr)
      {
          throw DomainError(L"(f g h)A cannot be inverted", shared_from_this());
      }
      std::shared_ptr<APL::types::Value> left = std::static_pointer_cast<APL::types::Value>(f);
      // System.out.println(f+";"+g+";"+h);
      return h->callInv(g->callInvW(left, w));
    }

    std::shared_ptr<APL::types::Value> Fork::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      std::shared_ptr<APL::types::Value> right = h->call(a, w);
      std::shared_ptr<APL::types::Value> left = !(std::dynamic_pointer_cast<Fun>(f) != nullptr)? std::static_pointer_cast<APL::types::Value>(f) : (std::static_pointer_cast<Fun>(f))->call(a, w);
      return g->call(left, right);
    }

    std::shared_ptr<APL::types::Value> Fork::callInvW(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      if (std::dynamic_pointer_cast<Fun>(f) != nullptr)
      {
          throw DomainError(L"A(f g h)B cannot be inverted", shared_from_this());
      }
      std::shared_ptr<APL::types::Value> left = std::static_pointer_cast<APL::types::Value>(f);
      return h->callInvW(a, g->callInvW(left, w));
    }

    std::shared_ptr<APL::types::Value> Fork::callInvA(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      if (std::dynamic_pointer_cast<Fun>(f) != nullptr)
      {
          throw DomainError(L"A(f g h)B cannot be inverted", shared_from_this());
      }
      return h->callInvA(g->callInvW(std::static_pointer_cast<APL::types::Value>(f), a), w);
    }

    std::string Fork::repr()
    {
      return L"(" + f + L" " + g + L" " + h + L")";
    }

    std::shared_ptr<APL::types::Value> Fork::under(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w)
    {
      if (!(std::dynamic_pointer_cast<APL::types::Value>(f) != nullptr))
      {
          throw DomainError(L"(f g h)A cannot be inverted", shared_from_this());
      }
      std::shared_ptr<APL::types::Value> fa = std::static_pointer_cast<APL::types::Value>(f);
      return h->under(std::make_shared<FunAnonymousInnerClass>(shared_from_this(), o, fa)
     , w);
    }

    Fork::FunAnonymousInnerClass::FunAnonymousInnerClass(std::shared_ptr<Fork> outerInstance, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::APL::types::Value> fa) : outerInstance(outerInstance)
    {
        this->o = o;
        this->fa = fa;
    }

    std::string Fork::FunAnonymousInnerClass::repr()
    {
        return outerInstance->g->repr();
    }

    std::shared_ptr<APL::types::Value> Fork::FunAnonymousInnerClass::call(std::shared_ptr<APL::types::Value> w)
    {
        return outerInstance->g->underW(o, fa, w);
    }
}
