//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/Indexer.h>
#include <APL/Main.h>
#include <APL/errors/RankError.h>
#include <APL/errors/LengthError.h>
#include <APL/errors/DomainError.h>
#include <APL/types/arrs/BitArr.h>
#include <APL/types/arrs/ChrArr.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/Primitive.h>
#include <APL/types/Arr.h>
#include <APL/types/arrs/Rank0Arr.h>
#include <APL/types/Num.h>
#include <APL/types/arrs/EmptyArr.h>

namespace APL
{
    // using namespace APL::errors;
    // using namespace APL::types;
    // using namespace APL::types::arrs;

    //NOTE(fernando)
    // using Iterator = java::util::Iterator;

    Indexer::Indexer(std::vector<int> &sh, std::vector<int> &offsets) : shape(sh), rank(sh.size()), c(std::vector<int>(sh.size())), offsets(offsets)
    {
      for (int i = 0; i < sh.size(); i++)
      {
        ia *= sh[i];
        c[i] = offsets[i];
      }
    }

    Indexer::Indexer(std::vector<int> &sh, int IO) : shape(sh), rank(sh.size()), c(std::vector<int>(sh.size())), offsets(std::vector<int>(sh.size()))
    {
      for (int i = 0; i < sh.size(); i++)
      {
        ia *= sh[i];
        offsets[i] = IO;
        c[i] = offsets[i];
      }
    }

    int Indexer::pos()
    {
      return ci - 1;
    }

    bool Indexer::hasNext()
    {
      return ci < ia;
    }

    std::vector<int> Indexer::next()
    {
      if (ci > 0)
      {
        c[rank - 1]++;
        int dim = rank - 1;
        while (c[dim] == shape[dim] + offsets[dim])
        {
          if (dim == 0)
          {
              break;
          }
          c[dim] = offsets[dim];
          c[dim - 1]++;
          dim--;
        }
      }
      ci++;
      return c;
    }

    std::vector<int> Indexer::add(std::vector<int> &a, int b)
    {
      std::vector<int> res(a.size());
      for (int i = 0; i < res.size(); i++)
      {
          res[i] = a[i] + b;
      }
      return res;
    }

    std::vector<int> Indexer::sub(std::vector<int> &a, int b)
    {
      std::vector<int> res(a.size());
      for (int i = 0; i < res.size(); i++)
      {
          res[i] = a[i] - b;
      }
      return res;
    }

    std::vector<int> Indexer::sub(std::vector<int> &a, std::vector<int> &b)
    {
      std::vector<int> res(a.size());
      for (int i = 0; i < res.size(); i++)
      {
          res[i] = a[i] - b[i];
      }
      return res;
    }

    std::vector<int> Indexer::add(std::vector<int> &a, std::vector<int> &b)
    {
      std::vector<int> res(a.size());
      for (int i = 0; i < res.size(); i++)
      {
          res[i] = a[i] + b[i];
      }
      return res;
    }

    int Indexer::fromShape(std::vector<int> &shape, std::vector<int> &pos, int IO)
    {
      int x = 0;
      for (int i = 0; i < shape.size(); i++)
      {
        x += pos[i] - IO;
        if (i != shape.size() - 1)
        {
            x *= shape[i + 1];
        }
      }
      return x;
    }

    int Indexer::fromShapeChk(std::vector<int> &sh, std::vector<int> &pos, std::shared_ptr<APL::types::Callable> blame)
    { // IO≡0
      if (sh.size() != pos.size())
      {
          throw RankError(blame + L": indexing at wrong rank (shape ≡ " + Main::formatAPL(sh) + L"; pos ≡ " + Main::formatAPL(pos) + L")", blame);
      }
      int x = 0;
      for (int i = 0; i < sh.size(); i++)
      {
        x += pos[i];
        if (pos[i] < 0 || pos[i] >= sh[i])
        {
            throw LengthError(blame + L": indexing out-of-bounds (shape ≡ " + Main::formatAPL(sh) + L"; pos ≡ " + Main::formatAPL(pos) + L"+⎕IO)", blame);
        }
        if (i != sh.size() - 1)
        {
            x *= sh[i + 1];
        }
      }
      return x;
    }

    int Indexer::fromShapeChk(std::vector<int> &sh, std::shared_ptr<APL::types::Value> pos, int IO, std::shared_ptr<APL::types::Callable> blame)
    {
      if (pos->rank > 1)
      {
          throw DomainError(blame + L": index rank should be ≤1 (shape ≡ " + Main::formatAPL(pos->shape) + L")", blame);
      }
      if (sh.size() != pos->ia)
      {
          throw RankError(blame + L": indexing at wrong rank (shape ≡ " + Main::formatAPL(sh) + L"; pos ≡ " + pos + L")", blame);
      }
      int x = 0;
      std::vector<double> ds = pos->asDoubleArr();
      for (int i = 0; i < sh.size(); i++)
      {
        int c = static_cast<int>(ds[i]);
        c -= IO;
        x += c;
        if (c < 0 || c >= sh[i])
        {
            throw LengthError(blame + L": indexing out-of-bounds (shape ≡ " + Main::formatAPL(sh) + L"; pos ≡ " + pos + L")", blame);
        }
        if (i != sh.size() - 1)
        {
            x *= sh[i + 1];
        }
      }
      return x;
    }

    Indexer::PosSh::PosSh(std::vector<int> &vals, std::vector<int> &sh) : vals(vals), sh(sh)
    {
    }

    std::shared_ptr<PosSh> Indexer::poss(std::shared_ptr<APL::types::Value> v, std::vector<int> &ish, int IO, std::shared_ptr<APL::types::Callable> blame)
    {
      // if (v instanceof Primitive) return new PosSh(new int[]{v.asInt()-IO}, Rank0Arr.SHAPE);
      if (Main::vind)
      { // ⎕VI←1
        bool deep = false;
        std::vector<int> rsh;
        if (!(std::dynamic_pointer_cast<DoubleArr>(v) != nullptr || std::dynamic_pointer_cast<APL::types::arrs::ChrArr>(v) != nullptr || std::dynamic_pointer_cast<APL::types::arrs::BitArr>(v) != nullptr))
        {
          for (auto c : v)
          {
            if (!(std::dynamic_pointer_cast<Primitive>(c) != nullptr))
            {
              if (!deep)
              {
                rsh = c->shape;
                deep = true;
              }
              else
              {
                  Arr::eqShapes(c->shape, rsh, blame);
              }
            }
          }
        }
        if (v->rank > 1)
        {
            throw RankError(blame + L": rank of indices must be 1 (shape ≡ " + Main::formatAPL(v->shape) + L")", blame);
        }
        if (!(!deep && ish.size() == 1) && ish.size() != v->ia)
        {
            throw LengthError(blame + L": amount of index parts should equal rank (" + std::to_wstring(v->ia) + L" index parts, shape ≡ " + Main::formatAPL(ish) + L")", blame);
        }
        if (!deep)
        { // either the rank==1 case or a single position
          std::vector<int> res = intsNoIO(v, IO);
          if (ish.size() == 1)
          {
              return std::make_shared<PosSh>(res, std::vector<int>{res.size()});
          }
          return std::make_shared<PosSh>(std::vector<int>{fromShapeChk(ish, res, blame)}, Rank0Arr::SHAPE);
        }

        std::vector<int> res(Arr::prod(rsh));
        for (int i = 0; i < v->ia; i++)
        {
          std::shared_ptr<APL::types::Value> c = v[i];
          if (std::dynamic_pointer_cast<Primitive>(c) != nullptr)
          {
            int n = c->asInt() - IO;
            if (n < 0 || n >= ish[i])
            {
                throw LengthError(blame + L": indexing out-of-bounds (shape ≡ " + Main::formatAPL(ish) + L"; pos[" + std::to_wstring(i + IO) + L"] ≡ " + c + L")", blame);
            }
            for (int j = 0; j < res.size(); j++)
            {
                res[j] += n;
            }
          }
          else
          {
            std::vector<double> ns = c->asDoubleArr();
            for (int j = 0; j < ns.size(); j++)
            {
              int n = Num::toInt(ns[j]);
              n -= IO;
              res[j] += n;
              if (n < 0 || n >= ish[i])
              {
                  throw LengthError(blame + L": indexing out-of-bounds (shape ≡ " + Main::formatAPL(ish) + L"; pos[" + std::to_wstring(i + IO) + L"] ≡ " + std::to_wstring(n) + L")", blame);
              }
            }
          }
          if (i != v->ia - 1)
          {
            for (int j = 0; j < res.size(); j++)
            {
                res[j] *= ish[i + 1];
            }
          }
        }
        return std::make_shared<PosSh>(res, rsh);
      }
      else
      { // ⎕VI←0
        std::vector<int> rsh = v->shape;
        if (v->quickDoubleArr())
        {
          std::vector<int> res = intsNoIO(v, IO);
          if (v->ia == 0)
          {
              return std::make_shared<PosSh>(EmptyArr::NOINTS, rsh);
          }
          if (ish.size() != 1)
          {
              throw RankError(blame + L": indexing at rank 1 (indexing by scalars in shape " + Main::formatAPL(ish) + L" array)", blame);
          }
          for (auto c : res)
          {
              if (c < 0 || c >= ish[0])
              {
                  throw LengthError(blame + L": indexing out-of bounds (shape ≡ " + std::to_wstring(rsh[0]) + L"; pos ≡ " + std::to_wstring(c + IO) + L")", blame);
              }
          }
          return std::make_shared<PosSh>(res, rsh);
        }

        std::vector<int> res(v->ia);
        for (int i = 0; i < v->ia; i++)
        {
            res[i] = fromShapeChk(ish, v[i], IO, blame);
        }
        return std::make_shared<PosSh>(res, rsh);
      }
    }

    std::vector<int> Indexer::intsNoIO(std::shared_ptr<APL::types::Value> v, int IO)
    {
      if (IO == 0)
      {
          return v->asIntArr();
      }
      std::vector<int> res = v->asIntArrClone();
      for (int i = 0; i < res.size(); i++)
      {
          res[i]--;
      }
      return res;
    }

    //NOTE(fernando)
    // std::shared_ptr<Iterator<std::vector<int>>> Indexer::iterator()
    // {
    //   return shared_from_this();
    // }
}
