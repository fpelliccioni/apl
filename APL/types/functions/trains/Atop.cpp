#include <APL/Atop.h>

namespace APL::types::functions::trains
{
    using SyntaxError = APL::errors::SyntaxError;
    // using namespace APL::types;

    Atop::Atop(std::shared_ptr<APL::types::Obj> g, std::shared_ptr<Fun> h) : g(g), h(h)
    {
    }

    std::shared_ptr<APL::types::Value> Atop::call(std::shared_ptr<APL::types::Value> w)
    {
      if (std::dynamic_pointer_cast<Fun>(g) != nullptr)
      {
          return (std::static_pointer_cast<Fun>(g))->call(h->call(w));
      }
      return h->call(std::static_pointer_cast<APL::types::Value>(g), w);
    }

    std::shared_ptr<APL::types::Value> Atop::callInv(std::shared_ptr<APL::types::Value> w)
    {
      // if (g instanceof Fun) return ((Fun) g).callInv((APL::types::Value) h.callInv(w));
      if (std::dynamic_pointer_cast<Fun>(g) != nullptr)
      {
          return h->callInv((std::static_pointer_cast<Fun>(g))->callInv(w));
      }
      return h->callInvW(std::static_pointer_cast<APL::types::Value>(g), w);
    }

    std::shared_ptr<APL::types::Value> Atop::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      if (!(std::dynamic_pointer_cast<Fun>(g) != nullptr))
      {
          throw SyntaxError(L"dyadically calling an A f train");
      }
      return (std::static_pointer_cast<Fun>(g))->call(h->call(a, w));
    }

    std::shared_ptr<APL::types::Value> Atop::callInvW(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      if (!(std::dynamic_pointer_cast<Fun>(g) != nullptr))
      {
          throw SyntaxError(L"inverting a dyadically called A f train");
      }
      return h->callInvW(a, (std::static_pointer_cast<Fun>(g))->callInv(w));
    }

    std::shared_ptr<APL::types::Value> Atop::callInvA(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      if (!(std::dynamic_pointer_cast<Fun>(g) != nullptr))
      {
          throw SyntaxError(L"inverting a dyadically called A f train");
      }
      return h->callInvA((std::static_pointer_cast<Fun>(g))->callInv(a), w);
    }

    std::shared_ptr<APL::types::Value> Atop::under(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w)
    {
      if (std::dynamic_pointer_cast<Fun>(g) != nullptr)
      {
        std::shared_ptr<Fun> gf = std::static_pointer_cast<Fun>(g);
        return h->under(std::make_shared<FunAnonymousInnerClass>(shared_from_this(), o, gf)
       , w);
      }
      else
      {
        return h->underW(o, std::static_pointer_cast<APL::types::Value>(g), w);
      }
    }

    Atop::FunAnonymousInnerClass::FunAnonymousInnerClass(std::shared_ptr<Atop> outerInstance, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Fun> gf) : outerInstance(outerInstance)
    {
        this->o = o;
        this->gf = gf;
    }

    std::string Atop::FunAnonymousInnerClass::repr()
    {
        return gf->repr();
    }

    std::shared_ptr<APL::types::Value> Atop::FunAnonymousInnerClass::call(std::shared_ptr<APL::types::Value> w)
    {
        return gf->under(o, w);
    }

    std::string Atop::repr()
    {
      return L"(" + g + L" " + h + L")";
    }
}
