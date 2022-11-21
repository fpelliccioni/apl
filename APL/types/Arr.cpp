//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/types/Arr.h>
#include <APL/types/Char.h>
#include <APL/types/Primitive.h>
#include <APL/types/arrs/ChrArr.h>
#include <APL/types/Num.h>
#include <APL/errors/DomainError.h>
#include <APL/types/arrs/EmptyArr.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/arrs/HArr.h>
#include <APL/errors/RankError.h>
#include <APL/errors/LengthError.h>

namespace APL::types
{
    using Main = APL::Main;
    // using namespace APL::errors;
    // using namespace APL::types::arrs;

    Arr::Arr(std::vector<int> &shape) : APL::types::Value(shape)
    {
    }

    Arr::Arr(std::vector<int> &shape, int ia) : APL::types::Value(shape, ia, shape.size())
    {
    }

    Arr::Arr(std::vector<int> &shape, int ia, int rank) : APL::types::Value(shape, ia, rank)
    {
    }

    std::string Arr::string(bool quote)
    {
      if (rank == 1)
      { // strings
        std::shared_ptr<StringBuilder> all = std::make_shared<StringBuilder>();
        for (auto v : shared_from_this())
        {
          if (std::dynamic_pointer_cast<Char>(v) != nullptr)
          {
            wchar_t c = (std::static_pointer_cast<Char>(v))->chr;
            if (quote && c == L'\"')
            {
                all->append(L"\"\"");
            }
            else
            {
                all->append(c);
            }
          }
          else
          {
              return L"";
          }
        }
        if (quote)
        {
          return L"\"" + all + L"\"";
        }
        else
        {
            return all->toString();
        }
      }
      return L"";
    }

    std::string Arr::toString()
    {
      if (ia == 0)
      {
        std::string mr = std::dynamic_pointer_cast<Char>(safePrototype()) != nullptr? L"''" : L"⍬";
        if (rank == 1)
        {
            return mr;
        }
        else
        {
          std::string s = Main::formatAPL(shape);
          return s + L"⍴" + mr;
        }
      }
      std::string qs = string(Main::quotestrings || Main::noBoxing);
      if (qs != L"")
      {
          return qs;
      }
      if (Main::noBoxing)
      {
        if (rank == 0)
        {
            return L"⊂" + oneliner();
        }
        return oneliner();
      }
      else
      {
        if (rank == 0)
        {
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
            return L"⊂" + StringHelper::replace(first()->toString(), L"\n", L"\n ");
        }
        if (ia == 1)
        {
          std::shared_ptr<APL::types::Value> c = this->operator[](0);
          if (std::dynamic_pointer_cast<Primitive>(c) != nullptr || rank > 2)
          {
            if (rank == 1)
            {
                return L"⍮" + c;
            }
            std::string pre = Main::formatAPL(shape);
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
            return pre + L"⍴⊂" + StringHelper::replace(c->toString(), L"\n", L"\n" + Main::repeat(L" ", pre.length() + 2));
          }
        }
        if (rank == 1)
        { // simple vectors
          std::shared_ptr<StringBuilder> res = std::make_shared<StringBuilder>();
          auto simple = true;
          for (auto v : shared_from_this())
          {
            if (res->length() > 0)
            {
                res->append(L" ");
            }
            if (v->empty())
            {
              res->append(L"NULLPTR");
            }
            else
            {
              simple &= std::dynamic_pointer_cast<Primitive>(v) != nullptr;
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
              res->append(v->toString());
            }
          }
          if (simple)
          {
              return res->toString();
          }
        }

        if (rank == 2)
        {
          bool charmat = true;
          if (!(std::dynamic_pointer_cast<APL::types::arrs::ChrArr>(shared_from_this()) != nullptr))
          {
            for (auto v : shared_from_this())
            {
              if (!(std::dynamic_pointer_cast<Char>(v) != nullptr))
              {
                charmat = false;
                break;
              }
            }
          }

          if (charmat)
          {
            std::shared_ptr<StringBuilder> b = std::make_shared<StringBuilder>();
            int i = 0;
            for (auto v : shared_from_this())
            {
              if (i++ % shape[1] == 0 && i != 1)
              {
                  b->append(L'\n');
              }
              b->append((std::static_pointer_cast<Char>(v))->chr);
            }
            return b->toString();
          }
        }

        if (rank < 3)
        { // boxed arrays
          int w = rank == 1? shape[0] : shape[1];
          int h = rank == 1? 1 : shape[0];
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: String[][][] stringified = new String[w][h][];
          std::vector<std::vector<std::vector<std::string>>> stringified = RectangularVectors::RectangularStdWstringVector(w, h, -1);
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: int[][] itemWidths = new int[w][h];
          std::vector<std::vector<int>> itemWidths = RectangularVectors::RectangularIntVector(w, h);
          std::vector<int> widths(w);
          std::vector<int> heights(h);
          auto simple = true;
          int x = 0, y = 0;
          for (auto v : shared_from_this())
          {
            if (v->empty())
            {
                v = Main::toAPL(L"NULLPTR");
            }
            simple &= std::dynamic_pointer_cast<Primitive>(v) != nullptr;
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
            auto c = v->toString().split(L"\n");
            auto cw = 0;
            for (auto ln : c)
            {
              cw = std::max(ln->length(), cw);
            }
            itemWidths[x][y] = cw;
            widths[x] = std::max(widths[x], cw);
            heights[y] = std::max(heights[y], c->length);
            stringified[x][y] = c;
            x++;
            if (x == w)
            {
              x = 0;
              y++;
            }
          }
          int borderSize = simple? 0 : 1;
          int rw = simple? -1 : 1, rh = borderSize; // result w&h;
          for (x = 0; x < w; x++)
          {
              rw += widths[x] + 1;
          }
          for (y = 0; y < h; y++)
          {
              rh += heights[y] + borderSize;
          }
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: char[][] chars = new char[rh][rw];
          std::vector<std::vector<wchar_t>> chars = RectangularVectors::RectangularWchar_tVector(rh, rw);
          int rx = borderSize, ry; // x&y in chars
          for (x = 0; x < w; x++)
          {
            ry = borderSize;
            for (y = 0; y < h; y++)
            {
              std::vector<std::string> cobj = stringified[x][y];
              for (int cy = 0; cy < cobj.size(); cy++)
              {
                std::string s = cobj[cy];
                std::vector<wchar_t> line(s.begin(), s.end());
                int sx = std::dynamic_pointer_cast<Num>(this->operator[](y * w + x)) != nullptr? rx + widths[x] - itemWidths[x][y] : rx;
                std::copy_n(line.begin(), line.size(), chars[ry + cy].begin() + sx);
              }
              ry += heights[y] + borderSize;
            }
            rx += widths[x] + 1;
          }
          if (!simple)
          { // draw borders
            rx = 0;
            for (x = 0; x < w; x++)
            {
              ry = 0;
              for (y = 0; y < h; y++)
              {
                chars[ry][rx] = L'┼';
                for (int cx = 1; cx <= widths[x]; cx++)
                {
                    chars[ry][rx + cx] = L'─';
                }
                for (int cy = 1; cy <= heights[y]; cy++)
                {
                    chars[ry + cy][rx] = L'│';
                }
                if (x == 0)
                {
                  for (int cy = 1; cy <= heights[y]; cy++)
                  {
                      chars[ry + cy][rw - 1] = L'│';
                  }
                  chars[ry][rw - 1] = y == 0? L'┐' : L'┤';
                  chars[ry][0] = L'├';
                }
                ry += heights[y] + borderSize;
              }
              chars[0][rx] = L'┬';
              chars[rh - 1][rx] = x == 0?L'└' : L'┴';
              for (int cx = 1; cx <= widths[x]; cx++)
              {
                  chars[rh - 1][rx + cx] = L'─';
              }
              rx += widths[x] + 1;
            }
            chars[0][0] = L'┌';
            chars[rh - 1][rw - 1] = L'┘';
          }
          for (auto ca : chars)
          {
            for (int i = 0; i < ca.size(); i++)
            {
              if (ca[i] == 0)
              {
                  ca[i] = L' ';
              }
            }
          }
          std::shared_ptr<StringBuilder> res = std::make_shared<StringBuilder>();
          bool next = false;
          for (auto ln : chars)
          {
            if (next)
            {
                res->append(L'\n');
            }
            res->append(ln);
            next = true;
          }
          return res->toString();
        }
        else
        {
            return oneliner();
        }
      }
    }

    std::string Arr::oneliner(std::vector<int> &where)
    {
      auto qs = string(true);
      if (qs != L"")
      {
          return qs;
      }
      std::shared_ptr<StringBuilder> res = std::make_shared<StringBuilder>(where.empty() ? L"{" : L"[");
      if (rank == 0)
      {
        return first()->oneliner();
      }
      else if (where.size() == rank - 1)
      {
        std::vector<int> pos(rank);
        std::copy_n(where.begin(), where.size(), pos.begin());
        for (int i = 0; i < shape[where.size()]; i++)
        {
          pos[rank - 1] = i;
          if (i != 0)
          {
              res->append(L", ");
          }
          res->append(simpleAt(pos)->oneliner());
        }
      }
      else
      {
        std::vector<int> pos(where.size() + 1);
        std::copy_n(where.begin(), where.size(), pos.begin());
        for (int i = 0; i < shape[where.size()]; i++)
        {
          pos[where.size()] = i;
          if (i != 0)
          {
              res->append(L", ");
          }
          res->append(oneliner(pos));
        }
      }
      return res + (where.empty()?L"}":L"]");
    }

    std::shared_ptr<Arr> Arr::reverseOn(int dim)
    {
      if (rank == 0)
      {
        if (dim != 0)
        {
            throw DomainError(L"rotating a scalar with a non-⎕IO axis", shared_from_this());
        }
        return shared_from_this();
      }
      if (dim < 0)
      {
          dim += rank;
      }
      // 2×3×4:
      // 0 - 3×4s for 2
      // 1 - 4s for 3
      // 2 - 1s for 4
      int chunkS = 1;
      int cPSec = shape[dim]; // chunks per section
      for (int i = rank - 1; i > dim; i--)
      {
        chunkS *= shape[i];
      }
      int sec = chunkS * cPSec; // section length
      std::vector<std::shared_ptr<APL::types::Value>> res(ia);
      int c = 0;
      while (c < ia)
      {
        for (int i = 0; i < cPSec; i++)
        {
          for (int j = 0; j < chunkS; j++)
          {
            res[c + (cPSec - i - 1) * chunkS + j] = this->operator[](c + i * chunkS + j);
          }
        }
        c += sec;
      }
      return Arr::create(res, shape);
    }

    std::shared_ptr<APL::types::Value> Arr::createL(std::vector<std::shared_ptr<APL::types::Value>> &v, std::vector<int> &sh)
    { // accepts ⊂Primitive; doesn't attempt individual item squeezing; TODO check more places where this should be used
      if (sh.empty() && std::dynamic_pointer_cast<Primitive>(v[0]) != nullptr && !Main::enclosePrimitives)
      {
          return v[0];
      }
      return create(v, sh);
    }

    std::shared_ptr<Arr> Arr::create(std::vector<std::shared_ptr<APL::types::Value>> &v)
    {
      return create(v, std::vector<int>{v.size()});
    }

    std::shared_ptr<Arr> Arr::create(std::vector<std::shared_ptr<APL::types::Value>> &v, std::vector<int> &sh)
    { // note, doesn't attempt individual item squeezing
      if (v.empty())
      {
          return std::make_shared<EmptyArr>(sh, nullptr);
      }
      if (std::dynamic_pointer_cast<Num>(v[0]) != nullptr)
      {
        std::vector<double> da(v.size());
        for (int i = 0; i < v.size(); i++)
        {
          if (std::dynamic_pointer_cast<Num>(v[i]) != nullptr)
          {
              da[i] = (std::static_pointer_cast<Num>(v[i]))->num;
          }
          else
          {
            da = std::vector<double>();
            break;
          }
        }
        if (!da.empty())
        {
            return std::make_shared<DoubleArr>(da, sh);
        }
      }
      if (std::dynamic_pointer_cast<Char>(v[0]) != nullptr)
      {
        std::shared_ptr<StringBuilder> s = std::make_shared<StringBuilder>();
        for (auto aV : v)
        {
          if (std::dynamic_pointer_cast<Char>(aV) != nullptr)
          {
              s->append((std::static_pointer_cast<Char>(aV))->chr);
          }
          else
          {
            s = nullptr;
            break;
          }
        }
        if (s != nullptr)
        {
            return std::make_shared<APL::types::arrs::ChrArr>(s->toString(), sh);
        }
      }
      return std::make_shared<HArr>(v, sh);
    }

    std::shared_ptr<Arr> Arr::create(std::vector<std::shared_ptr<APL::types::Value>> &v)
    {
      return create(v, std::vector<int>{v.size()});
    }

    std::shared_ptr<Arr> Arr::create(std::vector<std::shared_ptr<APL::types::Value>> &v, std::vector<int> &sh)
    { // note, doesn't attempt individual item squeezing
      if (v.empty())
      {
          return std::make_shared<EmptyArr>(sh, nullptr);
      }
      std::shared_ptr<APL::types::Value> f = v[0];
      if (std::dynamic_pointer_cast<Num>(f) != nullptr)
      {
        std::vector<double> da(v.size());
        for (int i = 0; i < v.size(); i++)
        {
          if (std::dynamic_pointer_cast<Num>(v[i]) != nullptr)
          {
              da[i] = (std::static_pointer_cast<Num>(v[i]))->num;
          }
          else
          {
            da = std::vector<double>();
            break;
          }
        }
        if (!da.empty())
        {
            return std::make_shared<DoubleArr>(da, sh);
        }
      }
      if (std::dynamic_pointer_cast<Char>(f) != nullptr)
      {
        std::shared_ptr<StringBuilder> s = std::make_shared<StringBuilder>();
        for (auto aV : v)
        {
          if (std::dynamic_pointer_cast<Char>(aV) != nullptr)
          {
              s->append((std::static_pointer_cast<Char>(aV))->chr);
          }
          else
          {
            s = nullptr;
            break;
          }
        }
        if (s != nullptr)
        {
            return std::make_shared<APL::types::arrs::ChrArr>(s->toString(), sh);
        }
      }
      return std::make_shared<HArr>(v, sh);
    }

    bool Arr::equals(std::shared_ptr<APL::types::Obj> o)
    {
      if (!(std::dynamic_pointer_cast<Arr>(o) != nullptr))
      {
          return false;
      }
      std::shared_ptr<Arr> a = std::static_pointer_cast<Arr>(o);
      if (!Arrays::equals(shape, a->shape))
      {
          return false;
      }
      if (hash != 0 && a->hash != 0 && hash != a->hash)
      {
          return false;
      }
      std::vector<std::shared_ptr<APL::types::Value>> mvs = values();
      std::vector<std::shared_ptr<APL::types::Value>> ovs = a->values();
      for (int i = 0; i < mvs.size(); i++)
      {
        if (!mvs[i]->equals(ovs[i]))
        {
            return false;
        }
      }
      return true;
    }

    int Arr::hashCode()
    {
      if (hash == 0)
      {
        for (auto v : shared_from_this())
        {
            hash = hash * 31 + v->hashCode();
        }
        hash = shapeHash(hash);
      }
      return hash;
    }

    int Arr::shapeHash(int hash)
    {
      int h = 0;
      for (auto i : shape)
      {
        h = h * 31 + i;
      }
      int res = hash * 113 + h;
      if (res == 0)
      {
          return 100003;
      }
      return res;
    }

    int Arr::prod(std::vector<int> &ia)
    {
      int r = 1;
      for (auto i : ia)
      {
          r *= i;
      }
      return r;
    }

    void Arr::eqShapes(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
    {
      std::vector<int> as = a->shape;
      std::vector<int> ws = w->shape;
      if (as.size() != ws.size())
      {
          throw RankError(StringHelper::wstring_to_string(L"ranks don't equal (shapes: " + Main::formatAPL(as) + L" vs " + Main::formatAPL(ws) + L")", w));
      }
      for (int i = 0; i < as.size(); i++)
      {
        if (as[i] != ws[i])
        {
            throw LengthError(StringHelper::wstring_to_string(L"shapes don't match (" + Main::formatAPL(as) + L" vs " + Main::formatAPL(ws) + L")", w));
        }
      }
    }

    void Arr::eqShapes(std::vector<int> &a, std::vector<int> &w, std::shared_ptr<APL::types::Callable> blame)
    {
      if (a.size() != w.size())
      {
          throw RankError(StringHelper::wstring_to_string(L"ranks don't equal (shapes: " + Main::formatAPL(a) + L" vs " + Main::formatAPL(w) + L")", blame));
      }
      for (int i = 0; i < a.size(); i++)
      {
        if (a[i] != w[i])
        {
            throw LengthError(StringHelper::wstring_to_string(L"shapes don't match (" + Main::formatAPL(a) + L" vs " + Main::formatAPL(w) + L")", blame));
        }
      }
    }
}
