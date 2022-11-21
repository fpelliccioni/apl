//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/types/arrs/BitArr.h>
#include <APL/types/Num.h>

namespace APL::types::arrs
{
    using Main = APL::Main;
    using DomainError = APL::errors::DomainError;
    // using namespace APL::types;
    using Arrays = java::util::Arrays;

    APL::types::arrs::BitArr::APL::types::arrs::BitArr(std::vector<long long> &arr, std::vector<int> &shape) : Arr(shape), arr(arr)
    {
      assert((Main::enclosePrimitives || shape.size() != 0, L"Internal: attempting to create a APL::types::arrs::BitArr of shape ⍬"));
      assert((sizeof_Keyword(shape) == arr.size(), std::to_wstring(arr.size()) + L" not expected for shape " + Main::formatAPL(shape)));
    }

    APL::types::arrs::BitArr::APL::types::arrs::BitArr(std::vector<long long> &arr, std::vector<int> &shape, int ia) : Arr(shape, ia), arr(arr)
    {
    }

    std::shared_ptr<APL::types::arrs::BitArr> APL::types::arrs::BitArr::of(std::shared_ptr<Arr> a)
    {
      if (std::dynamic_pointer_cast<APL::types::arrs::BitArr>(a) != nullptr)
      {
          return std::static_pointer_cast<APL::types::arrs::BitArr>(a);
      }
      if (a->quickDoubleArr())
      {
        std::vector<double> ds = a->asDoubleArr();
        std::vector<long long> arr = convert(ds);
        return std::make_shared<APL::types::arrs::BitArr>(arr, a->shape);
      }
      std::vector<long long> arr((a->ia + 63 >> 6));
      int p = 0;
      for (auto v : a)
      {
        int n = Main::bool_Keyword(v)? 1 : 0;
        arr[p >> 6] = arr[p >> 6] | n << (p & 63);
      }
      return std::make_shared<APL::types::arrs::BitArr>(arr, a->shape);
    }

    std::vector<long long> APL::types::arrs::BitArr::convert(std::vector<double> &arr)
    {
      std::vector<long long> res(arr.size() + 63 >> 6);
      for (int i = 0; i < arr.size(); i++)
      {
        double d = arr[i];
        if (d != 0 && d != 1)
        {
            throw DomainError(StringHelper::wstring_to_string(L"Converting " + std::to_wstring(d) + L" to boolean"));
        }
        res[i >> 6] = res[i >> 6] | static_cast<int>(d) << (i & 63);
      }
      return res;
    }

    int APL::types::arrs::BitArr::sizeof_Keyword(std::shared_ptr<APL::types::Value> w)
    {
      return w->ia + 63 >> 6;
    }

    int APL::types::arrs::BitArr::sizeof_Keyword(std::vector<int> &sh)
    {
      int m = 1;
      for (auto i : sh)
      {
          m *= i;
      }
      return sizeof_Keyword(m);
    }

    int APL::types::arrs::BitArr::sizeof_Keyword(int am)
    {
      return am + 63 >> 6;
    }

    std::shared_ptr<APL::types::Value> APL::types::arrs::BitArr::fill(std::shared_ptr<APL::types::Value> v, bool b)
    {
      std::vector<long long> arr(sizeof_Keyword(v));
      if (!b)
      {
          return std::make_shared<APL::types::arrs::BitArr>(arr, v->shape, v->ia);
      }
      Arrays::fill(arr, -1LL);
      return std::make_shared<APL::types::arrs::BitArr>(arr, v->shape, v->ia);
    }

    std::vector<int> APL::types::arrs::BitArr::asIntArrClone()
    {
      std::vector<int> res(ia);
      int ctr = 0;
      for (int i = 0; i < arr.size() - 1; i++)
      {
        long long cl = arr[i];
        for (int j = 0; j < 64; j++)
        {
          res[ctr++] = static_cast<int>(cl & 1);
          cl >>= 1;
        }
      }
      int over = ia & 63; // aka ia % 64
      for (int i = 0; i < over; i++)
      {
        res[ctr++] = static_cast<int>((arr[ctr / 64] >> i) & 1);
      }
      return res;
    }

    std::vector<double> APL::types::arrs::BitArr::asDoubleArr()
    {
      std::vector<double> res(ia);
      int ctr = 0;
      for (int i = 0; i < ia / 64; i++)
      {
        long long cl = arr[i];
        for (int j = 0; j < 64; j++)
        {
          res[ctr++] = cl & 1;
          cl >>= 1;
        }
      }
      int over = ia & 63; // aka ia % 64
      for (int i = 0; i < over; i++)
      {
        res[ctr++] = static_cast<int>((arr[ctr / 64] >> i) & 1);
      }
      return res;
    }

    int APL::types::arrs::BitArr::asInt()
    {
      throw DomainError(L"Using bit array as integer", shared_from_this());
    }

    std::shared_ptr<APL::types::Value> APL::types::arrs::BitArr::get(int i)
    {
      return Num::NUMS[static_cast<int>((arr[i >> 6] >> (i & 63)) & 1)]; // no branching!
    }

    std::string APL::types::arrs::BitArr::asString()
    {
      throw DomainError(L"Using bit array as string", shared_from_this());
    }

    std::shared_ptr<APL::types::Value> APL::types::arrs::BitArr::prototype()
    {
      return Num::ZERO;
    }

    std::shared_ptr<APL::types::Value> APL::types::arrs::BitArr::safePrototype()
    {
      return Num::ZERO;
    }

    std::shared_ptr<APL::types::Value> APL::types::arrs::BitArr::ofShape(std::vector<int> &sh)
    {
      if (sh.empty() && !Main::enclosePrimitives)
      {
          return this->operator[](0);
      }
      return std::make_shared<APL::types::arrs::BitArr>(arr, sh);
    }

    bool APL::types::arrs::BitArr::quickDoubleArr()
    {
      return true;
    }

    int APL::types::arrs::BitArr::llen()
    { // long length
      return arr.size();
    }

    void APL::types::arrs::BitArr::setEnd(bool on)
    {
      if ((ia & 63) != 0)
      {
        int extra = ia & 63;
        long long tail = -(1LL << extra); // bits outside of the array
        long long last = arr[arr.size() - 1]; // last item of the array
        long long at = tail & (on?~last : last); // masking tail bits of the last item
        arr[arr.size() - 1] = last ^ at;
      }
    }

    double APL::types::arrs::BitArr::sum()
    {
      return isum();
    }

    int APL::types::arrs::BitArr::isum()
    {
      int r = 0;
      setEnd(false);
      for (auto l : arr)
      {
        r += Long::bitCount(l);
      }
      return r;
    }

    APL::types::arrs::BitArr::BA::BA(int am) : a(std::vector<long long>(sizeof_Keyword(am))), sh(std::vector<int>{am})
    {
    }

    APL::types::arrs::BitArr::BA::BA(std::vector<int> &sh) : a(std::vector<long long>(sizeof_Keyword(sh))), sh(sh)
    {
    }

    APL::types::arrs::BitArr::BA::BA(std::vector<long long> &a, int start, std::vector<int> &sh) : a(a), sh(sh)
    {
      i = start >> 6;
      o = start & 63;
    }

    void APL::types::arrs::BitArr::BA::add(bool b)
    {
      a[i] |= (b? 1LL : 0LL) << o;
      o++;
      // i+= o==64? 1 : 0; // todo, idk ._.
      // o&= 63;
      if (o == 64)
      {
        o = 0;
        i++;
      }
    }

    void APL::types::arrs::BitArr::BA::add(long long l)
    { // expects a 0 or 1
      a[i] |= l << o;
      o++;
      if (o == 64)
      {
        o = 0;
        i++;
      }
    }

    void APL::types::arrs::BitArr::BA::add(std::shared_ptr<APL::types::arrs::BitArr> a)
    {
      add(a, 0, a->ia);
    }

    void APL::types::arrs::BitArr::BA::add(std::shared_ptr<APL::types::arrs::BitArr> g, int s, int e)
    {
      if (s == e)
      {
          return;
      }

      g->setEnd(false);
      if (o == 0 && (s & 63) == 0)
      {
        int si = s >> 6;
        int li = (e-1) >> 6; // incl
        std::copy_n(g->arr.begin() + si, li - si + 1, a.begin() + i);

        i += (e - s) >> 6;
        o = e & 63;
        return;
      }

      std::vector<long long> garr = g->arr;

      int startI = i;
      long long start = a[i];
      long long startMask = (1LL << o) - 1; // mask of what's already written

      int Spos = i * 64 + o; // start of where to insert
      int Epos = Spos + e - s; // end of where to insert; excl
      int Li = (Epos - 1) >> 6; // incl
      int shl = o - s;
      int pG = s >> 6;
      if (shl < 0)
      {
        shl += 64;
        pG++;
      }
      int shr = 64 - shl;
      // System.out.println(i+"…"+Li+": s="+s+" o="+o+" e="+e+" pG="+pG+" shl="+shl);

      /* some unrolling of
            for (int pT = i; pT <= Li; pT++) {
              if (pG<garr.length) a[pT]|= garr[pG]<<shl;
              if (pG-1>=0) a[pT]|= garr[pG-1]>>>shr;
              pG++;
            }
      */
      {
        int pT = i;
        if (pG < garr.size())
        {
            a[pT] |= garr[pG] << shl;
        }
        if (pG - 1 >= 0)
        {
            a[pT] |= static_cast<long long>(static_cast<unsigned long long>(garr[pG - 1]) >> shr);
        }
        pG++;
      }
      for (int pT = i + 1; pT < Li; pT++)
      {
        a[pT] |= garr[pG] << shl;
        a[pT] |= static_cast<long long>(static_cast<unsigned long long>(garr[pG - 1]) >> shr);
        pG++;
      }
      if (i + 1 <= Li)
      {
        int pT = Li;
        if (pG < garr.size())
        {
            a[pT] |= garr[pG] << shl;
        }
        a[pT] |= static_cast<long long>(static_cast<unsigned long long>(garr[pG - 1]) >> shr);
        pG++;
      }


      a[startI] &= ~startMask; // clear out garbage
      a[startI] |= start; // and fill with non-garbage
      i = Epos >> 6;
      o = Epos & 63;

      // TODO clear out end
      // for (long l : a) {
      //   String b = Long.toBinaryString(l);
      //   while (b.length()<64)b="0"+b;
      //   System.out.println(b);
      // }
    }

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("ConstantExpression") public void fill(int n)
    void APL::types::arrs::BitArr::BA::fill(int n)
    {
      int off = o + n;
      if (off < 64)
      { // start & end being in the same cell is annoying
        if (n == 0)
        {
            return;
        }
        a[i] |= ((1LL << n) - 1) << o;
        o = off;
      }
      else
      {
        a[i] |= (~0LL) << o;
        int li = i + ((off - 1) >> 6);
        for (int j = i + 1; j <= li; j++)
        {
          a[j] = ~0LL;
        }
        i += off >> 6;
        o = off & 63;

        if (o != 0)
        {
          a[i] = (1LL << o) - 1;
        }
      }
    }

    void APL::types::arrs::BitArr::BA::skip(int n)
    {
      int off = o + n;
      o = off & 63;
      i += off >> 6;
    }

    std::shared_ptr<APL::types::arrs::BitArr> APL::types::arrs::BitArr::BA::finish()
    {
      return std::make_shared<APL::types::arrs::BitArr>(a, sh);
    }

    std::string APL::types::arrs::BitArr::str64(long long l)
    {
      std::shared_ptr<StringBuilder> t = std::make_shared<StringBuilder>(Long::toBinaryString(l));
      while (t->length() < 64)
      {
          t->insert(0, L"0");
      }
      for (int i = 56; i > 0; i -= 8)
      {
          t->insert(i, L'_');
      }
      return t->toString();
    }

    long long APL::types::arrs::BitArr::longFrom(int s)
    {
      int i1 = s >> 6;
      int i2 = (s + 63) >> 6;
      int o1 = s & 63;
      // System.out.printf("%d %d %d %d\n", s, i1, i2, o1);
      if (arr.size() == i2)
      {
          return static_cast<long long>(static_cast<unsigned long long>(arr[i1]) >> o1);
      }
      return static_cast<long long>(static_cast<unsigned long long>(arr[i1]) >> o1) | arr[i2] << (64 - o1);
    }

    APL::types::arrs::BitArr::BC::BC(std::vector<int> &sz) : arr(std::vector<long long>(sizeof_Keyword(sz))), sz(sz)
    {
    }

    std::shared_ptr<APL::types::arrs::BitArr> APL::types::arrs::BitArr::BC::finish()
    {
      // assert (i<<6) + o == Arr.prod(sz); \\ idk man
      return std::make_shared<APL::types::arrs::BitArr>(arr, sz);
    }

    void APL::types::arrs::BitArr::BC::set(int pos)
    {
      arr[pos >> 6] |= 1LL << (pos & 63);
    }

    void APL::types::arrs::BitArr::BC::clear(int pos)
    {
      arr[pos >> 6] &= ~(1LL << (pos & 63));
    }

    std::shared_ptr<BC> APL::types::arrs::BitArr::create(std::vector<int> &sh)
    {
      return std::make_shared<BC>(sh);
    }

    bool APL::types::arrs::BitArr::BR::read()
    {
      bool r = (outerInstance->arr[i] & 1LL << o) != 0;
      o++;
      // i+= o==64? 1 : 0;
      // o&= 63;
      if (o == 64)
      {
        o = 0;
        i++;
      }
      return r;
    }

    void APL::types::arrs::BitArr::BR::skip(int n)
    {
      int fp = (i << 6) + o + n;
      i = fp >> 6;
      o = fp & 63;
    }

    std::shared_ptr<APL::types::Value> APL::types::arrs::BitArr::squeeze()
    {
      return shared_from_this(); // we don't need no squeezing!
    }

    std::shared_ptr<BR> APL::types::arrs::BitArr::read()
    {
      return std::make_shared<BR>(shared_from_this(), shared_from_this());
    }

    std::vector<std::shared_ptr<APL::types::Value>> APL::types::arrs::BitArr::valuesCopy()
    {
      std::vector<std::shared_ptr<APL::types::Value>> vs(ia);
      int o = 0;
      for (int i = 0; i < ia / 64; i++)
      {
        long long l = arr[i];
        for (int j = 0; j < 64; j++)
        {
          vs[o++] = Num::NUMS[static_cast<int>(l & 1)];
          l >>= 1;
        }
      }
      if (o != ia)
      {
        long long l = arr[arr.size() - 1];
        for (int i = 0; i < ia % 64; i++)
        {
          vs[o++] = Num::NUMS[static_cast<int>(l & 1)];
          l >>= 1;
        }
      }
      return vs;
    }
}
