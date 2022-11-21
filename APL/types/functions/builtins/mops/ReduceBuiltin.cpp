//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/ReduceBuiltin.h>
#include <APL/errors/SyntaxError.h>
#include <APL/types/functions/builtins/fns/PlusBuiltin.h>
#include <APL/types/Num.h>
#include <APL/types/functions/builtins/fns/MulBuiltin.h>
#include <APL/types/functions/builtins/fns/FloorBuiltin.h>
#include <APL/types/functions/builtins/fns/CeilingBuiltin.h>
#include <APL/types/functions/builtins/fns/CatBuiltin.h>
#include <APL/types/Char.h>
#include <APL/types/arrs/ChrArr.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/Arr.h>
#include <APL/errors/DomainError.h>
#include <APL/errors/NYIError.h>
#include <APL/types/arrs/EmptyArr.h>

namespace APL::types::functions::builtins::mops
{
    using Main = APL::Main;
    // using namespace APL::errors;
    // using namespace APL::types;
    // using namespace APL::types::arrs;
    using DimMMop = APL::types::dimensions::DimMMop;
    // using namespace APL::types::functions;
    // using namespace APL::types::functions::builtins::fns;

    std::string ReduceBuiltin::repr()
    {
      return L"/";
    }

    std::shared_ptr<APL::types::Value> ReduceBuiltin::call(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> w, int dim)
    {
      if (!(std::dynamic_pointer_cast<Fun>(f) != nullptr))
      {
          throw SyntaxError(L"/ is only reduce. To use as replicate, use ⌿", f);
      }
      return ngnReduce(w, dim, std::static_pointer_cast<Fun>(f));
    }

    std::shared_ptr<APL::types::Value> ReduceBuiltin::call(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv)
    {
      if (!(std::dynamic_pointer_cast<Fun>(f) != nullptr))
      {
          throw SyntaxError(L"/ is only reduce. To use as replicate, use ⌿", f);
      }
      std::shared_ptr<Fun> ff = std::static_pointer_cast<Fun>(f);
      if (w->rank >= 2)
      {
        return ngnReduce(w, w->rank - 1, ff);
      }
      if (w->quickDoubleArr())
      {
        if (std::dynamic_pointer_cast<PlusBuiltin>(f) != nullptr)
        {
            return std::make_shared<Num>(w->sum());
        }
        if (std::dynamic_pointer_cast<MulBuiltin>(f) != nullptr)
        {
          double p = 1;
          for (auto d : w->asDoubleArr())
          {
              p *= d;
          }
          return std::make_shared<Num>(p);
        }
        if (std::dynamic_pointer_cast<FloorBuiltin>(f) != nullptr)
        {
          double p = std::numeric_limits<double>::infinity();
          for (auto d : w->asDoubleArr())
          {
              p = std::min(p, d);
          }
          return std::make_shared<Num>(p);
        }
        if (std::dynamic_pointer_cast<CeilingBuiltin>(f) != nullptr)
        {
          double p = -std::numeric_limits<double>::infinity();
          for (auto d : w->asDoubleArr())
          {
              p = std::max(p, d);
          }
          return std::make_shared<Num>(p);
        }
      }
      if (std::dynamic_pointer_cast<CatBuiltin>(f) != nullptr)
      {
        if (w->ia > 0)
        {
          {
            std::shared_ptr<APL::types::Value> first = w->first();
            int am = 0;
            int chki = 0;
            {
              if (std::dynamic_pointer_cast<APL::types::arrs::ChrArr>(first) != nullptr || std::dynamic_pointer_cast<Char>(first) != nullptr)
              {
                for (auto v : w)
                {
                  if (v->rank > 1)
                  {
                      goto specialBreak;
                  }
                  if (!(std::dynamic_pointer_cast<APL::types::arrs::ChrArr>(v) != nullptr || std::dynamic_pointer_cast<Char>(v) != nullptr))
                  {
                      goto typedBreak;
                  }
                  am += v->ia;
                  chki++;
                }
                std::vector<wchar_t> cs(am);
                int ri = 0;
                for (int i = 0; i < w->ia; i++)
                {
                  std::shared_ptr<APL::types::Value> v = w[i];
                  if (std::dynamic_pointer_cast<Char>(v) != nullptr)
                  {
                      cs[ri++] = (std::static_pointer_cast<Char>(v))->chr;
                  }
                  else
                  {
                    std::string s = (std::static_pointer_cast<APL::types::arrs::ChrArr>(v))->s;
                    s.getChars(0, s.length(), cs, ri);
                    ri += s.length();
                  }
                }
                return Main::toAPL(std::string(cs));


              }
              else if (first->quickDoubleArr())
              {
                for (auto v : w)
                {
                  if (v->rank > 1)
                  {
                      goto specialBreak;
                  }
                  if (!v->quickDoubleArr())
                  {
                      goto typedBreak;
                  }
                  am += v->ia;
                  chki++;
                }
                std::vector<double> ds(am);

                int ri = 0;
                for (int i = 0; i < w->ia; i++)
                {
                  std::shared_ptr<APL::types::Value> v = w[i];
                  if (std::dynamic_pointer_cast<Num>(v) != nullptr)
                  {
                    ds[ri++] = (std::static_pointer_cast<Num>(v))->num;
                  }
                  else
                  {
                    std::copy_n(v->asDoubleArr().begin(), v->ia, ds.begin() + ri);
                    ri += v->ia;
                  }
                }
                return std::make_shared<DoubleArr>(ds);
              }
            }
            typedBreak:

            for (; chki < w->ia; chki++)
            {
              std::shared_ptr<APL::types::Value> v = w[chki];
              if (v->rank > 1)
              {
                  goto specialBreak;
              }
              am += v->ia;
            }

            std::vector<std::shared_ptr<APL::types::Value>> vs(am);
            int ri = 0;
            for (auto v : w)
            {
              std::copy_n(v->values().begin(), v->ia, vs.begin() + ri);
              ri += v->ia;
            }
            return Arr::create(vs);
          }
          specialBreak:;
        }
      }
      std::vector<std::shared_ptr<APL::types::Value>> a = w->values();
      if (a.empty())
      {
        std::shared_ptr<APL::types::Value> id = ff->identity();
        if (id->empty())
        {
            throw DomainError(StringHelper::wstring_to_string(L"No identity defined for " + f->name(), shared_from_this(), f));
        }
        return id;
      }
      std::shared_ptr<APL::types::Value> last = a[a.size() - 1];
      for (int i = a.size() - 2; i >= 0; i--)
      {
        last = ff->call(a[i], last);
      }
      return last;
    }

    std::shared_ptr<APL::types::Value> ReduceBuiltin::call(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DerivedMop> derv)
    {
      std::shared_ptr<Fun> ff = isFn(f);
      if (w->rank != 1)
      {
          throw APL::errors::NYIError(L"A f/ B with 2≤⍴⍴B hasn't been implemented", shared_from_this(), w);
      }
      int n = a->asInt();
      std::vector<std::shared_ptr<APL::types::Value>> ra(w->ia - std::abs(n) + 1);
      std::vector<std::shared_ptr<APL::types::Value>> wa = w->values();
      if (n > 0)
      {
        for (int i = 0; i < ra.size(); i++)
        {
          std::shared_ptr<APL::types::Value> r = wa[i + n - 1];
          for (int j = n - 2; j >= 0; j--)
          {
            r = ff->call(wa[i + j], r);
          }
          ra[i] = r;
        }
      }
      else
      {
        n = -n;
        for (int i = 0; i < ra.size(); i++)
        {
          std::shared_ptr<APL::types::Value> r = wa[i];
          for (int j = 1; j < n; j++)
          {
            r = ff->call(wa[i + j], r);
          }
          ra[i] = r;
        }
      }
      if (ra.empty())
      {
          return std::make_shared<EmptyArr>(EmptyArr::SHAPE0, w->safePrototype());
      }
      return Arr::create(ra);
    }

    std::shared_ptr<APL::types::Value> ReduceBuiltin::ngnReduce(std::shared_ptr<APL::types::Value> x, int axis, std::shared_ptr<Fun> f)
    { // https://chat.stackexchange.com/transcript/message/47158587#47158587
      if (x->rank == 0)
      {
          return x;
      }
      int n0 = 1; // product of all dimensions before "axis"
      for (int i = 0; i < axis; i++)
      {
        n0 *= x->shape[i];
      }
      int n1 = x->shape[axis]; // the dimension at "axis" - what's getting removed/reduced
      int n2 = x->ia / (n1 * n0); // product of the rest of the shape
      std::vector<int> ns = x->eraseDim(axis);

      std::vector<std::shared_ptr<APL::types::Value>> r(n0 * n2);
      for (int i = 0; i < n0; i++)
      {
        for (int k = 0; k < n2; k++)
        {
          std::shared_ptr<APL::types::Value> c = x[i * n1 * n2 + (n1 - 1) * n2 + k];
          for (int j = n1 - 2; j >= 0; j--)
          {
            c = f->call(x[i * n1 * n2 + j * n2 + k], c);
          }
          r[i * n2 + k] = c;
        }
      }
      if (r.empty())
      {
          return std::make_shared<EmptyArr>(ns, x->safePrototype());
      }
      return Arr::create(r, ns);
    }
}
