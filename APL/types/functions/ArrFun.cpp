#include <APL/ArrFun.h>
#include <APL/types/functions/Dop.h>
#include <APL/types/functions/Mop.h>

namespace APL::types::functions
{
    // using namespace APL;
    using DomainError = APL::errors::DomainError;
    using BacktickTok = APL::tokenizer::types::BacktickTok;
    // using namespace APL::types;
    using SingleItemArr = APL::types::arrs::SingleItemArr;

    ArrFun::ArrFun(std::shared_ptr<Fun> f) : f(f)
    {
    }

    ArrFun::ArrFun(std::shared_ptr<BacktickTok> t, std::shared_ptr<Scope> sc) : f(Main::exec(t->value(), sc))
    {
      if (!(std::dynamic_pointer_cast<Fun>(f) != nullptr) && !(std::dynamic_pointer_cast<Mop>(f) != nullptr) && !(std::dynamic_pointer_cast<Dop>(f) != nullptr))
      {
//JAVA TO C++ CONVERTER TODO TASK: You cannot use 'shared_from_this' in a constructor:
        throw DomainError(StringHelper::wstring_to_string(L"can't arrayify " + f->humanType(true), shared_from_this()));
      }
    }

    std::shared_ptr<APL::types::Obj> ArrFun::obj()
    {
      return f;
    }

    std::shared_ptr<APL::types::Value> ArrFun::ofShape(std::vector<int> &sh)
    {
      return SingleItemArr::maybe(shared_from_this(), sh);
    }

    std::string ArrFun::toString()
    {
      if (std::dynamic_pointer_cast<Fun>(f) != nullptr)
      {
          return L"`" + (std::static_pointer_cast<Fun>(f))->repr();
      }
      if (std::dynamic_pointer_cast<Mop>(f) != nullptr)
      {
          return L"`" + (std::static_pointer_cast<Mop>(f))->repr();
      }
      if (std::dynamic_pointer_cast<Dop>(f) != nullptr)
      {
          return L"`" + (std::static_pointer_cast<Dop>(f))->repr();
      }
      throw InternalError(StringHelper::wstring_to_string(L"unexpected `" + f->humanType(false)));
    }

    int ArrFun::hashCode()
    {
      return f->hashCode();
    }

    bool ArrFun::equals(std::shared_ptr<APL::types::Obj> o)
    {
      if (!(std::dynamic_pointer_cast<ArrFun>(o) != nullptr))
      {
          return false;
      }
      std::shared_ptr<ArrFun> w = std::static_pointer_cast<ArrFun>(o);
      return w->f->equals(f);
    }
}
