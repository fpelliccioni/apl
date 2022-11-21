#include <APL/Dfn.h>
#include <APL/Main.h>
#include <APL/types/Variable.h>
#include <APL/types/Settable.h>

namespace APL::types::functions::userDefined
{
    // using namespace APL;
    using DomainError = APL::errors::DomainError;
    using DfnTok = APL::tokenizer::types::DfnTok;
    // using namespace APL::types;
    using VarArr = APL::types::functions::VarArr;

    Dfn::Dfn(std::shared_ptr<DfnTok> t, std::shared_ptr<Scope> sc) : Fun(sc), code(t)
    {
    }

    std::shared_ptr<APL::types::Value> Dfn::call(std::shared_ptr<APL::types::Value> w)
    {
      std::shared_ptr<APL::types::Obj> o = callObj(w);
      if (std::dynamic_pointer_cast<APL::types::Value>(o) != nullptr)
      {
          return std::static_pointer_cast<APL::types::Value>(o);
      }
      throw DomainError(StringHelper::wstring_to_string(L"Was expected to give array, got " + o->humanType(true), shared_from_this()));
    }

    std::shared_ptr<APL::types::Obj> Dfn::callObj(std::shared_ptr<APL::types::Value> w)
    {
      Main::printdbg(sc, std::vector<std::any> {L"dfn call", w});
      std::shared_ptr<Scope> nsc = std::make_shared<Scope>(sc);
      nsc->set(L"⍺", std::make_shared<Variable>(nsc, L"⍺"));
      nsc->set(L"⍵", w);
      nsc->set(L"∇", shared_from_this());
      auto res = Main::execLines(code, nsc);
      if (std::dynamic_pointer_cast<VarArr>(res) != nullptr)
      {
          return (std::static_pointer_cast<VarArr>(res))->get();
      }
      if (std::dynamic_pointer_cast<Settable>(res) != nullptr)
      {
          return (std::static_pointer_cast<Settable>(res))->get();
      }
      return res;
    }

    std::shared_ptr<APL::types::Value> Dfn::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      std::shared_ptr<APL::types::Obj> o = callObj(a, w);
      if (std::dynamic_pointer_cast<APL::types::Value>(o) != nullptr)
      {
          return std::static_pointer_cast<APL::types::Value>(o);
      }
      throw DomainError(StringHelper::wstring_to_string(L"Was expected to give array, got " + o->humanType(true), shared_from_this()));
    }

    std::shared_ptr<APL::types::Obj> Dfn::callObj(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      Main::printdbg(sc, std::vector<std::any> {L"dfn call", a, w});
      std::shared_ptr<Scope> nsc = std::make_shared<Scope>(sc);
      nsc->set(L"⍺", a);
      nsc->set(L"⍵", w);
      nsc->set(L"∇", shared_from_this());
      nsc->alphaDefined = true;
      auto res = Main::execLines(code, nsc);
      if (std::dynamic_pointer_cast<VarArr>(res) != nullptr)
      {
          return (std::static_pointer_cast<VarArr>(res))->get();
      }
      if (std::dynamic_pointer_cast<Settable>(res) != nullptr)
      {
          return (std::static_pointer_cast<Settable>(res))->get();
      }
      return res;
    }

    std::string Dfn::repr()
    {
      return code->toRepr();
    }

    std::string Dfn::name()
    {
        return L"dfn";
    }
}
