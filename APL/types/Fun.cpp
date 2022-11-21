//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/types/Fun.h>
#include <APL/errors/IncorrectArgsError.h>
#include <APL/errors/DomainError.h>
#include <APL/types/Primitive.h>
#include <APL/types/Arr.h>
#include <APL/types/arrs/HArr.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/Main.h>
#include <APL/types/arrs/ChrArr.h>
#include <APL/types/arrs/Rank0Arr.h>

namespace APL::types
{
    // using namespace APL;
    // using namespace APL::errors;
    // using namespace APL::types::arrs;
    //NOTE(fernando)
    // using Iterator = java::util::Iterator;

    std::shared_ptr<APL::types::Value> Fun::identity()
    {
      return nullptr;
    }

    Fun::Fun(std::shared_ptr<Scope> sc) : Callable(sc)
    {
    }

    Fun::Fun() : Callable(nullptr)
    {
    }

    std::shared_ptr<APL::types::Value> Fun::call(std::shared_ptr<APL::types::Value> w)
    {
      throw IncorrectArgsError(StringHelper::wstring_to_string(L"function " + toString() + L" called monadically", shared_from_this(), w));
    }

    std::shared_ptr<APL::types::Value> Fun::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      throw IncorrectArgsError(StringHelper::wstring_to_string(L"function " + toString() + L" called dyadically", shared_from_this(), a));
    }

    std::shared_ptr<APL::types::Obj> Fun::callObj(std::shared_ptr<APL::types::Value> w)
    { // if overridden, call(w) must be overridden too!
      return call(w);
    }

    std::shared_ptr<APL::types::Obj> Fun::callObj(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    { // if overridden, call(a, w) must be overridden too!
      return call(a, w);
    }

    std::shared_ptr<APL::types::Value> Fun::callInv(std::shared_ptr<APL::types::Value> w)
    {
      throw DomainError(shared_from_this() + L" doesn't support monadic inverting", shared_from_this(), w);
    }

    std::shared_ptr<APL::types::Value> Fun::callInvW(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      throw DomainError(shared_from_this() + L" doesn't support dyadic inverting of ⍵", shared_from_this(), w);
    }

    std::shared_ptr<APL::types::Value> Fun::callInvA(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      throw DomainError(shared_from_this() + L" doesn't support dyadic inverting of ⍺", shared_from_this(), w);
    }

    std::shared_ptr<APL::types::Value> Fun::under(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w)
    {
      std::shared_ptr<APL::types::Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(w)) : std::static_pointer_cast<APL::types::Value>(o);
      return callInv(v);
    }

    std::shared_ptr<APL::types::Value> Fun::underW(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      std::shared_ptr<APL::types::Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(a, w)) : std::static_pointer_cast<APL::types::Value>(o);
      return callInvW(a, v);
    }

    std::shared_ptr<APL::types::Value> Fun::underA(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      std::shared_ptr<APL::types::Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(a, w)) : std::static_pointer_cast<APL::types::Value>(o);
      return callInvA(v, w);
    }

    bool Fun::NumMV::retNum()
    {
      return true;
    }

    double Fun::NumMV::call(double w)
    {
      return call(std::make_shared<Num>(w)).asDouble();
    }

    void Fun::NumMV::call(std::vector<double> &res, std::vector<double> &a)
    {
      for (int i = 0; i < res.length; i++)
          res[i] = call(a[i]);
    }

    std::shared_ptr<APL::types::Value> Fun::NumMV::call(std::shared_ptr<APL::types::BigValue> w)
    {
      throw DomainError(L"bigintegers not allowed here", w);
    }

    std::shared_ptr<Arr> Fun::ChrMV::call(std::shared_ptr<APL::types::arrs::ChrArr> a)
    {
      APL::types::Value[] res = std::vector<std::shared_ptr<APL::types::Value>>(a.ia);
      for (int i = 0; i < a.ia; i++)
          res[i] = call(Char.of(a.s.charAt(i)));
      return std::make_shared<HArr>(res, a.shape);
    }

    std::shared_ptr<APL::types::Value> Fun::allM(std::shared_ptr<AllMV> f, std::shared_ptr<APL::types::Value> w)
    {
      if (std::dynamic_pointer_cast<Primitive>(w) != nullptr)
      {
        return f->call(w);
      }
      else
      {
        std::shared_ptr<Arr> o = std::static_pointer_cast<Arr>(w);
        std::vector<std::shared_ptr<APL::types::Value>> arr(o->ia);
        for (int i = 0; i < o->ia; i++)
        {
          arr[i] = allM(f, o[i]);
        }
        return std::make_shared<HArr>(arr, o->shape);
      }
    }

    std::shared_ptr<APL::types::Value> Fun::numM(std::shared_ptr<NumMV> nf, std::shared_ptr<APL::types::Value> w)
    {
      if (std::dynamic_pointer_cast<Arr>(w) != nullptr)
      {
        if (w->quickDoubleArr())
        {
          std::vector<double> res(w->ia);
          nf->call(res, w->asDoubleArr());
          return std::make_shared<DoubleArr>(res, w->shape);
        }
        std::shared_ptr<Arr> o = std::static_pointer_cast<Arr>(w);
        std::vector<std::shared_ptr<APL::types::Value>> arr(o->ia);
        for (int i = 0; i < o->ia; i++)
        {
          arr[i] = numM(nf, o[i]);
        }
        return std::make_shared<HArr>(arr, o->shape);
      }
      if (std::dynamic_pointer_cast<Num>(w) != nullptr)
      {
          return nf->call(std::static_pointer_cast<Num>(w));
      }
      if (std::dynamic_pointer_cast<APL::types::BigValue>(w) != nullptr)
      {
          return nf->call(std::static_pointer_cast<APL::types::BigValue>(w));
      }
      throw DomainError(StringHelper::wstring_to_string(L"Expected number, got " + w->humanType(false), shared_from_this(), w));
    }

    std::shared_ptr<APL::types::Value> Fun::numChrM(std::shared_ptr<NumMV> nf, std::shared_ptr<ChrMV> cf, std::shared_ptr<APL::types::Value> w)
    {
      if (std::dynamic_pointer_cast<Arr>(w) != nullptr)
      {
        if (std::dynamic_pointer_cast<DoubleArr>(w) != nullptr && nf->retNum())
        {
          std::vector<double> res(w->ia);
          nf->call(res, w->asDoubleArr());
          return std::make_shared<DoubleArr>(res, w->shape);
        }
        if (std::dynamic_pointer_cast<APL::types::arrs::ChrArr>(w) != nullptr)
        {
            return cf->call(std::static_pointer_cast<APL::types::arrs::ChrArr>(w));
        }
        std::shared_ptr<Arr> o = std::static_pointer_cast<Arr>(w);
        std::vector<std::shared_ptr<APL::types::Value>> arr(o->ia);
        for (int i = 0; i < o->ia; i++)
        {
          arr[i] = numChrM(nf, cf, o[i]);
        }
        return std::make_shared<HArr>(arr, o->shape);
      }
      if (std::dynamic_pointer_cast<Char>(w) != nullptr)
      {
          return cf->call(std::static_pointer_cast<Char>(w));
      }
      if (std::dynamic_pointer_cast<Num>(w) != nullptr)
      {
          return nf->call(std::static_pointer_cast<Num>(w));
      }
      if (std::dynamic_pointer_cast<APL::types::BigValue>(w) != nullptr)
      {
          return nf->call(std::static_pointer_cast<APL::types::BigValue>(w));
      }
      throw DomainError(StringHelper::wstring_to_string(L"Expected either number or character argument, got " + w->humanType(false), shared_from_this(), w));
    }

    std::shared_ptr<APL::types::Value> Fun::numChrMapM(std::shared_ptr<NumMV> nf, std::shared_ptr<ChrMV> cf, std::shared_ptr<MapMV> mf, std::shared_ptr<APL::types::Value> w)
    {
      if (std::dynamic_pointer_cast<Arr>(w) != nullptr)
      {
        if (w->quickDoubleArr())
        {
          std::vector<double> res(w->ia);
          nf->call(res, w->asDoubleArr());
          return std::make_shared<DoubleArr>(res, w->shape);
        }
        std::shared_ptr<Arr> o = std::static_pointer_cast<Arr>(w);
        std::vector<std::shared_ptr<APL::types::Value>> arr(o->ia);
        for (int i = 0; i < o->ia; i++)
        {
          arr[i] = numChrMapM(nf, cf, mf, o[i]);
        }
        return std::make_shared<HArr>(arr, o->shape);
      }
      if (std::dynamic_pointer_cast<Char>(w) != nullptr)
      {
          return cf->call(std::static_pointer_cast<Char>(w));
      }
      if (std::dynamic_pointer_cast<Num>(w) != nullptr)
      {
          return nf->call(std::static_pointer_cast<Num>(w));
      }
      if (std::dynamic_pointer_cast<APLMap>(w) != nullptr)
      {
          return mf->call(std::static_pointer_cast<APLMap>(w));
      }
      if (std::dynamic_pointer_cast<APL::types::BigValue>(w) != nullptr)
      {
          return nf->call(std::static_pointer_cast<APL::types::BigValue>(w));
      }
      throw DomainError(StringHelper::wstring_to_string(L"Expected either number/char/map, got " + w->humanType(false), shared_from_this(), w));
    }

    std::shared_ptr<APL::types::Value> Fun::allD(std::shared_ptr<D_AA> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      if (std::dynamic_pointer_cast<Primitive>(a) != nullptr && std::dynamic_pointer_cast<Primitive>(w) != nullptr)
      {
          return f->call(a, w);
      }

      if (a->scalar())
      {
        std::shared_ptr<APL::types::Value> af = a->first();

        if (w->scalar())
        {
          return std::make_shared<Rank0Arr>(allD(f, af, w->first()));
        }
        else
        { // ⍺ ⍵¨
          std::vector<std::shared_ptr<APL::types::Value>> arr(w->ia);
          APL::types::APL::types::Value::const_iterator wi = w->begin();
          for (int i = 0; i < w->ia; i++)
          {
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
            arr[i] = allD(f, af, wi->next());
          }
          return std::make_shared<HArr>(arr, w->shape);

        }
      }
      else
      {
        if (w->scalar())
        { // ⍺¨ ⍵
          std::shared_ptr<APL::types::Value> wf = w->first();

          std::vector<std::shared_ptr<APL::types::Value>> arr(a->ia);
          APL::types::APL::types::Value::const_iterator ai = a->begin();
          for (int i = 0; i < a->ia; i++)
          {
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
            arr[i] = allD(f, ai->next(), wf);
          }
          return std::make_shared<HArr>(arr, a->shape);

        }
        else
        { // ⍺ ¨ ⍵
          Arr::eqShapes(a, w);
          assert(a->ia == w->ia);
          std::vector<std::shared_ptr<APL::types::Value>> arr(a->ia);
          APL::types::APL::types::Value::const_iterator ai = a->begin();
          APL::types::APL::types::Value::const_iterator wi = w->begin();
          for (int i = 0; i < a->ia; i++)
          {
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
            arr[i] = allD(f, ai->next(), wi->next());
          }
          return std::make_shared<HArr>(arr, a->shape);

        }
      }
    }

    void Fun::D_NNeN::on(std::vector<double> &res, double a, std::vector<double> &w)
    {
      for (int i = 0; i < w.size(); i++)
      {
        res[i] = on(a, w[i]);
      }
    }

    void Fun::D_NNeN::on(std::vector<double> &res, std::vector<double> &a, double w)
    {
      for (int i = 0; i < a.size(); i++)
      {
        res[i] = on(a[i], w);
      }
    }

    void Fun::D_NNeN::on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w)
    {
      for (int i = 0; i < a.size(); i++)
      {
        res[i] = on(a[i], w[i]);
      }
    }

    std::shared_ptr<APL::types::Value> Fun::D_NNeN::call(double a, double w)
    {
      return std::make_shared<Num>(on(a, w));
    }

    std::shared_ptr<APL::types::Value> Fun::D_NNeN::call(std::vector<double> &a, std::vector<double> &w, std::vector<int> &sh)
    {
      std::vector<double> res(w.size());
      on(res, a, w);
      return std::make_shared<DoubleArr>(res, sh);
    }

    std::shared_ptr<APL::types::Value> Fun::D_NNeN::call(double a, std::vector<double> &w, std::vector<int> &sh)
    {
      std::vector<double> res(w.size());
      on(res, a, w);
      return std::make_shared<DoubleArr>(res, sh);
    }

    std::shared_ptr<APL::types::Value> Fun::D_NNeN::call(std::vector<double> &a, double w, std::vector<int> &sh)
    {
      std::vector<double> res(a.size());
      on(res, a, w);
      return std::make_shared<DoubleArr>(res, sh);
    }

    std::shared_ptr<APL::types::Value> Fun::D_NNeN::call(std::shared_ptr<APL::types::BigValue> a, std::shared_ptr<APL::types::BigValue> w)
    {
      throw DomainError(L"bigintegers not allowed here", w);
    }

    std::shared_ptr<APL::types::Value> Fun::D_NNeB::call(double a, double w)
    {
      return on(a, w)? Num::ONE : Num::ZERO;
    }

    std::shared_ptr<APL::types::Value> Fun::D_NNeB::call(std::vector<double> &a, std::vector<double> &w, std::vector<int> &sh)
    {
      std::shared_ptr<APL::types::arrs::BitArr::BA> res = std::make_shared<APL::types::arrs::BitArr::BA>(sh);
      on(res, a, w);
      return res->finish();
    }

    std::shared_ptr<APL::types::Value> Fun::D_NNeB::call(double a, std::vector<double> &w, std::vector<int> &sh)
    {
      std::shared_ptr<APL::types::arrs::BitArr::BA> res = std::make_shared<APL::types::arrs::BitArr::BA>(sh);
      on(res, a, w);
      return res->finish();
    }

    std::shared_ptr<APL::types::Value> Fun::D_NNeB::call(std::vector<double> &a, double w, std::vector<int> &sh)
    {
      std::shared_ptr<APL::types::arrs::BitArr::BA> res = std::make_shared<APL::types::arrs::BitArr::BA>(sh);
      on(res, a, w);
      return res->finish();
    }

    std::shared_ptr<APL::types::Value> Fun::D_NNeB::call(std::shared_ptr<APL::types::BigValue> a, std::shared_ptr<APL::types::BigValue> w)
    {
      throw DomainError(L"bigintegers not allowed here", w);
    }

    std::shared_ptr<APL::types::Value> Fun::D_NN::call(double a, std::shared_ptr<APL::types::BigValue> w)
    { // special requirement for log; only needs to be handled in numD
      return call(std::make_shared<APL::types::BigValue>(a), w);
    }

    std::shared_ptr<APL::types::Value> Fun::numD(std::shared_ptr<D_NN> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      if (a->scalar())
      {
        if (w->scalar())
        { // ⊃⍺ ⊃⍵
          if (std::dynamic_pointer_cast<Primitive>(a) != nullptr & std::dynamic_pointer_cast<Primitive>(w) != nullptr)
          {
            bool an = std::dynamic_pointer_cast<Num>(a) != nullptr;
            bool wn = std::dynamic_pointer_cast<Num>(w) != nullptr;
            if (an & wn)
            {
                return f->call((std::static_pointer_cast<Num>(a))->num, (std::static_pointer_cast<Num>(w))->num);
            }
            if ((std::dynamic_pointer_cast<APL::types::BigValue>(a) != nullptr | an) & (std::dynamic_pointer_cast<APL::types::BigValue>(w) != nullptr | wn))
            {
              if (an)
              {
                  return f->call((std::static_pointer_cast<Num>(a))->num, std::static_pointer_cast<APL::types::BigValue>(w));
              }
              else
              {
                  return f->call(std::static_pointer_cast<APL::types::BigValue>(a), wn? std::make_shared<APL::types::BigValue>((std::static_pointer_cast<Num>(w))->num) : std::static_pointer_cast<APL::types::BigValue>(w));
              }
            }
            throw DomainError(StringHelper::wstring_to_string(L"calling a number-only function with " + w->humanType(true), shared_from_this()));
          }
          else
          {
              return std::make_shared<Rank0Arr>(numD(f, a->first(), w->first()));
          }

        }
        else
        { // ⍺¨ ⍵
          if (w->quickDoubleArr() && std::dynamic_pointer_cast<Num>(a) != nullptr)
          {
            return f->call(a->asDouble(), w->asDoubleArr(), w->shape);
          }
          std::shared_ptr<APL::types::Value> af = a->first();
          APL::types::APL::types::Value::const_iterator wi = w->begin();
          std::vector<std::shared_ptr<APL::types::Value>> vs(w->ia);
          for (int i = 0; i < w->ia; i++)
          {
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
            vs[i] = numD(f, af, wi->next());
          }
          return std::make_shared<HArr>(vs, w->shape);

        }
      }
      else
      {
        if (w->scalar())
        { // ⍺ ⍵¨
          if (a->quickDoubleArr() && std::dynamic_pointer_cast<Num>(w) != nullptr)
          {
            return f->call(a->asDoubleArr(), w->asDouble(), a->shape);
          }
          std::shared_ptr<APL::types::Value> wf = w->first();
          APL::types::APL::types::Value::const_iterator ai = a->begin();
          std::vector<std::shared_ptr<APL::types::Value>> vs(a->ia);
          for (int i = 0; i < a->ia; i++)
          {
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
            vs[i] = numD(f, ai->next(), wf);
          }

          return std::make_shared<HArr>(vs, a->shape);

        }
        else
        { // ⍺ ¨ ⍵
          Arr::eqShapes(a, w);

          if (a->quickDoubleArr() && w->quickDoubleArr())
          {
            return f->call(a->asDoubleArr(), w->asDoubleArr(), a->shape);
          }

          std::vector<std::shared_ptr<APL::types::Value>> arr(a->ia);
          APL::types::APL::types::Value::const_iterator ai = a->begin();
          APL::types::APL::types::Value::const_iterator wi = w->begin();
          for (int i = 0; i < a->ia; i++)
          {
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
            arr[i] = numD(f, ai->next(), wi->next());
          }
          return std::make_shared<HArr>(arr, a->shape);

        }
      }
    }

    std::shared_ptr<APL::types::Value> Fun::bitD(std::shared_ptr<D_NN> n, std::shared_ptr<D_BB> b, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      if (a->scalar())
      {
        if (w->scalar())
        { // ⊃⍺ ⊃⍵
          if (std::dynamic_pointer_cast<Primitive>(a) != nullptr & std::dynamic_pointer_cast<Primitive>(w) != nullptr)
          {
            bool an = std::dynamic_pointer_cast<Num>(a) != nullptr;
            bool wn = std::dynamic_pointer_cast<Num>(w) != nullptr;
            if (an & wn)
            {
                return n->call((std::static_pointer_cast<Num>(a))->num, (std::static_pointer_cast<Num>(w))->num);
            }
            if ((std::dynamic_pointer_cast<APL::types::BigValue>(a) != nullptr | an) & (std::dynamic_pointer_cast<APL::types::BigValue>(w) != nullptr | wn))
            {
              return n->call(an? std::make_shared<APL::types::BigValue>((std::static_pointer_cast<Num>(a))->num) : std::static_pointer_cast<APL::types::BigValue>(a), wn? std::make_shared<APL::types::BigValue>((std::static_pointer_cast<Num>(w))->num) : std::static_pointer_cast<APL::types::BigValue>(w));
            }
            throw DomainError(StringHelper::wstring_to_string(L"calling a number-only function with " + w->humanType(true), shared_from_this()));
          }
          else
          {
              return std::make_shared<Rank0Arr>(bitD(n, b, a->first(), w->first()));
          }

        }
        else
        { // ⍺¨ ⍵
          if (std::dynamic_pointer_cast<Primitive>(a) != nullptr)
          {
            if (std::dynamic_pointer_cast<APL::types::arrs::BitArr>(w) != nullptr && Main::isBool(a))
            {
              return b->call(Main::bool_Keyword(a), std::static_pointer_cast<APL::types::arrs::BitArr>(w));
            }
            if (std::dynamic_pointer_cast<Num>(a) != nullptr && w->quickDoubleArr())
            {
              return n->call(a->asDouble(), w->asDoubleArr(), w->shape);
            }
          }
          std::shared_ptr<APL::types::Value> af = a->first();
          APL::types::APL::types::Value::const_iterator wi = w->begin();
          std::vector<std::shared_ptr<APL::types::Value>> vs(w->ia);
          for (int i = 0; i < w->ia; i++)
          {
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
            vs[i] = bitD(n, b, af, wi->next());
          }
          return std::make_shared<HArr>(vs, w->shape);

        }
      }
      else
      {
        if (w->scalar())
        { // ⍺ ⍵¨
          if (std::dynamic_pointer_cast<Primitive>(w) != nullptr)
          {
            if (std::dynamic_pointer_cast<APL::types::arrs::BitArr>(a) != nullptr && Main::isBool(w))
            {
              return b->call(std::static_pointer_cast<APL::types::arrs::BitArr>(a), Main::bool_Keyword(w));
            }
            if (std::dynamic_pointer_cast<Num>(a) != nullptr && a->quickDoubleArr())
            {
              return n->call(a->asDoubleArr(), w->asDouble(), a->shape);
            }
          }
          std::shared_ptr<APL::types::Value> wf = w->first();
          APL::types::APL::types::Value::const_iterator ai = a->begin();
          std::vector<std::shared_ptr<APL::types::Value>> vs(a->ia);
          for (int i = 0; i < a->ia; i++)
          {
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
            vs[i] = bitD(n, b, ai->next(), wf);
          }

          return std::make_shared<HArr>(vs, a->shape);

        }
        else
        { // ⍺ ¨ ⍵
          Arr::eqShapes(a, w);

          if (std::dynamic_pointer_cast<APL::types::arrs::BitArr>(a) != nullptr && std::dynamic_pointer_cast<APL::types::arrs::BitArr>(w) != nullptr)
          {
            return b->call(std::static_pointer_cast<APL::types::arrs::BitArr>(a), std::static_pointer_cast<APL::types::arrs::BitArr>(w));
          }

          if (a->quickDoubleArr() && w->quickDoubleArr())
          {
            return n->call(a->asDoubleArr(), w->asDoubleArr(), a->shape);
          }

          std::vector<std::shared_ptr<APL::types::Value>> arr(a->ia);
          APL::types::APL::types::Value::const_iterator ai = a->begin();
          APL::types::APL::types::Value::const_iterator wi = w->begin();
          for (int i = 0; i < a->ia; i++)
          {
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
            arr[i] = bitD(n, b, ai->next(), wi->next());
          }
          return std::make_shared<HArr>(arr, a->shape);

        }
      }
    }

    std::shared_ptr<APL::types::Value> Fun::numChrD(std::shared_ptr<D_NN> n, std::shared_ptr<D_CC> c, std::shared_ptr<D_AA> def, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      if (a->scalar())
      {
        if (w->scalar())
        { // ⊃⍺ ⊃⍵
          if (std::dynamic_pointer_cast<Primitive>(a) != nullptr & std::dynamic_pointer_cast<Primitive>(w) != nullptr)
          {
            bool an = std::dynamic_pointer_cast<Num>(a) != nullptr;
            bool wn = std::dynamic_pointer_cast<Num>(w) != nullptr;
            if (an & wn)
            {
                return n->call((std::static_pointer_cast<Num>(a))->num, (std::static_pointer_cast<Num>(w))->num);
            }
            if ((std::dynamic_pointer_cast<APL::types::BigValue>(a) != nullptr | an) & (std::dynamic_pointer_cast<APL::types::BigValue>(w) != nullptr | wn))
            {
              return n->call(an? std::make_shared<APL::types::BigValue>((std::static_pointer_cast<Num>(a))->num) : std::static_pointer_cast<APL::types::BigValue>(a), wn? std::make_shared<APL::types::BigValue>((std::static_pointer_cast<Num>(w))->num) : std::static_pointer_cast<APL::types::BigValue>(w));
            }
            if (std::dynamic_pointer_cast<Char>(a) != nullptr & std::dynamic_pointer_cast<Char>(w) != nullptr)
            {
                return c->call((std::static_pointer_cast<Char>(a))->chr, (std::static_pointer_cast<Char>(w))->chr);
            }
            return def->call(a, w);
          }
          else
          {
              return std::make_shared<Rank0Arr>(numChrD(n, c, def, a->first(), w->first()));
          }

        }
        else
        { // ⍺¨ ⍵
          if (std::dynamic_pointer_cast<Num>(a) != nullptr && w->quickDoubleArr())
          {
            return n->call(a->asDouble(), w->asDoubleArr(), w->shape);
          }

          std::shared_ptr<APL::types::Value> af = a->first();
          APL::types::APL::types::Value::const_iterator wi = w->begin();
          std::vector<std::shared_ptr<APL::types::Value>> vs(w->ia);
          for (int i = 0; i < w->ia; i++)
          {
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
            vs[i] = numChrD(n, c, def, af, wi->next());
          }
          return std::make_shared<HArr>(vs, w->shape);

        }
      }
      else
      {
        if (w->scalar())
        { // ⍺ ⍵¨
          if (std::dynamic_pointer_cast<Num>(w) != nullptr && a->quickDoubleArr())
          {
            return n->call(a->asDoubleArr(), w->asDouble(), a->shape);
          }
          std::shared_ptr<APL::types::Value> wf = w->first();
          APL::types::APL::types::Value::const_iterator ai = a->begin();
          std::vector<std::shared_ptr<APL::types::Value>> vs(a->ia);
          for (int i = 0; i < a->ia; i++)
          {
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
            vs[i] = numChrD(n, c, def, ai->next(), wf);
          }

          return std::make_shared<HArr>(vs, a->shape);
        }
        else
        { // ⍺ ¨ ⍵
          Arr::eqShapes(a, w);

          if (a->quickDoubleArr() && w->quickDoubleArr())
          {
            return n->call(a->asDoubleArr(), w->asDoubleArr(), a->shape);
          }

          std::vector<std::shared_ptr<APL::types::Value>> arr(a->ia);
          APL::types::APL::types::Value::const_iterator ai = a->begin();
          APL::types::APL::types::Value::const_iterator wi = w->begin();
          for (int i = 0; i < a->ia; i++)
          {
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
            arr[i] = numChrD(n, c, def, ai->next(), wi->next());
          }
          return std::make_shared<HArr>(arr, a->shape);

        }
      }
    }

    std::shared_ptr<APL::types::Value> Fun::ncbaD(std::shared_ptr<D_NN> n, std::shared_ptr<D_BB> b, std::shared_ptr<D_CC> c, std::shared_ptr<D_AA> def, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      if (a->scalar())
      {
        if (w->scalar())
        { // ⊃⍺ ⊃⍵
          if (std::dynamic_pointer_cast<Primitive>(a) != nullptr & std::dynamic_pointer_cast<Primitive>(w) != nullptr)
          {
            bool an = std::dynamic_pointer_cast<Num>(a) != nullptr;
            bool wn = std::dynamic_pointer_cast<Num>(w) != nullptr;
            if (an & wn)
            {
                return n->call((std::static_pointer_cast<Num>(a))->num, (std::static_pointer_cast<Num>(w))->num);
            }
            else if (std::dynamic_pointer_cast<Char>(a) != nullptr & std::dynamic_pointer_cast<Char>(w) != nullptr)
            {
                return c->call((std::static_pointer_cast<Char>(a))->chr, (std::static_pointer_cast<Char>(w))->chr);
            }
            else if ((std::dynamic_pointer_cast<APL::types::BigValue>(a) != nullptr | an) & (std::dynamic_pointer_cast<APL::types::BigValue>(w) != nullptr | wn))
            {
              return n->call(an? std::make_shared<APL::types::BigValue>((std::static_pointer_cast<Num>(a))->num) : std::static_pointer_cast<APL::types::BigValue>(a), wn? std::make_shared<APL::types::BigValue>((std::static_pointer_cast<Num>(w))->num) : std::static_pointer_cast<APL::types::BigValue>(w));
            }
            else
            {
                return def->call(a, w);
            }
          }
          else
          {
              return std::make_shared<Rank0Arr>(ncbaD(n, b, c, def, a->first(), w->first()));
          }

        }
        else
        { // ⍺¨ ⍵
          if (std::dynamic_pointer_cast<Primitive>(a) != nullptr)
          {
            if (std::dynamic_pointer_cast<APL::types::arrs::BitArr>(w) != nullptr && Main::isBool(a))
            {
              return b->call(Main::bool_Keyword(a), std::static_pointer_cast<APL::types::arrs::BitArr>(w));
            }
            if (std::dynamic_pointer_cast<Num>(a) != nullptr && w->quickDoubleArr())
            {
              return n->call(a->asDouble(), w->asDoubleArr(), w->shape);
            }
          }

          std::shared_ptr<APL::types::Value> af = a->first();
          APL::types::APL::types::Value::const_iterator wi = w->begin();
          std::vector<std::shared_ptr<APL::types::Value>> vs(w->ia);
          for (int i = 0; i < w->ia; i++)
          {
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
            vs[i] = ncbaD(n, b, c, def, af, wi->next());
          }
          return std::make_shared<HArr>(vs, w->shape);
        }
      }
      else
      {
        if (w->scalar())
        { // ⍺ ⍵¨
          if (std::dynamic_pointer_cast<Primitive>(w) != nullptr)
          {
            if (std::dynamic_pointer_cast<APL::types::arrs::BitArr>(a) != nullptr && Main::isBool(w))
            {
              return b->call(std::static_pointer_cast<APL::types::arrs::BitArr>(a), Main::bool_Keyword(w));
            }
            if (std::dynamic_pointer_cast<Num>(a) != nullptr && a->quickDoubleArr())
            {
              return n->call(a->asDoubleArr(), w->asDouble(), a->shape);
            }
          }
          std::shared_ptr<APL::types::Value> wf = w->first();
          APL::types::APL::types::Value::const_iterator ai = a->begin();
          std::vector<std::shared_ptr<APL::types::Value>> vs(a->ia);
          for (int i = 0; i < a->ia; i++)
          {
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
            vs[i] = ncbaD(n, b, c, def, ai->next(), wf);
          }

          return std::make_shared<HArr>(vs, a->shape);

        }
        else
        { // ⍺ ¨ ⍵
          Arr::eqShapes(a, w);

          if (std::dynamic_pointer_cast<APL::types::arrs::BitArr>(a) != nullptr && std::dynamic_pointer_cast<APL::types::arrs::BitArr>(w) != nullptr)
          {
            return b->call(std::static_pointer_cast<APL::types::arrs::BitArr>(a), std::static_pointer_cast<APL::types::arrs::BitArr>(w));
          }
          if (a->quickDoubleArr() && w->quickDoubleArr())
          {
            return n->call(a->asDoubleArr(), w->asDoubleArr(), a->shape);
          }

          std::vector<std::shared_ptr<APL::types::Value>> arr(a->ia);
          APL::types::APL::types::Value::const_iterator ai = a->begin();
          APL::types::APL::types::Value::const_iterator wi = w->begin();
          for (int i = 0; i < a->ia; i++)
          {
//JAVA TO C++ CONVERTER TODO TASK: Java iterators are only converted within the context of 'while' and 'for' loops:
            arr[i] = ncbaD(n, b, c, def, ai->next(), wi->next());
          }
          return std::make_shared<HArr>(arr, a->shape);

        }
      }
    }

    APL::Type Fun::type()
    {
      return Type::fn;
    }

    std::string Fun::toString()
    {
      return repr();
    }

    int Fun::hashCode()
    {
      return actualHashCode();
    }

    bool Fun::equals(std::shared_ptr<APL::types::Obj> o)
    {
      return shared_from_this() == o;
    }
}
