//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/types/Num.h>

namespace APL::types
{
    using DomainError = APL::errors::DomainError;
    using SingleItemArr = APL::types::arrs::SingleItemArr;
    using Locale = java::util::Locale;
const std::shared_ptr<Num> Num::NEGINF = std::make_shared<Num>(-std::numeric_limits<double>::infinity());
const std::shared_ptr<Num> Num::POSINF = std::make_shared<Num>(std::numeric_limits<double>::infinity());
int Num::pp = 0;
int Num::sEr = 0;
int Num::eEr = 0;

    Num::StaticConstructor::StaticConstructor()
    {
                setPrecision(14, -10, 10);
                for (int i = 0; i < NUMS.size(); i++)
                {
    NUMS[i] = std::make_shared<Num>(i);
                }
    }

Num::StaticConstructor Num::staticConstructor;
const std::vector<wchar_t> Num::buf = std::vector<wchar_t>(400);

    std::string Num::format(double d)
    {
      double a = std::abs(d);
      if (d == 0)
      {
        if (Double::doubleToRawLongBits(d) == 0)
        {
            return L"0";
        }
        else
        {
            return L"¯0";
        }
      }

      std::string f = String::format(Locale::ENGLISH, L"%." + std::to_wstring(pp) + L"e", a);
      std::vector<wchar_t> fa(f.begin(), f.end());
      if (fa[0] > L'9')
      {
        if (fa[0] == L'N')
        {
            return L"NaN";
        }
        return d < 0? L"¯∞" : L"∞";
      }
      int exp = (fa[pp + 4] - L'0') * 10 + fa[pp + 5] - L'0'; // exponent
      /* ⎕pp←4:
         4.0000e+03
         0123456789
       ∆ 43210123456
         ¯¯¯¯
      */
      if (exp < sEr || exp > eEr)
      { // scientific notation
        int len = 0;
        if (d < 0)
        {
          buf[len++] = L'¯';
        }

        int ls = pp + 1; // last significant digit position
        while (fa[ls] == L'0')
        {
            ls--;
        }
        if (ls == 1)
        {
            ls = 0;
        }
        ls++;

        std::copy_n(fa.begin(), ls, buf.begin() + len);
        len += ls;
        buf[len++] = L'e';

        if (fa[pp + 3] == L'-')
        {
            buf[len++] = L'¯';
        }

        int es = pp + 4;
        int ee = fa.size();
        if (fa[pp + 4] == L'0')
        {
            es++;
        }
        std::copy_n(fa.begin() + es, ee - es, buf.begin() + len);
        len += ee - es;


        return std::string(buf, 0, len);
      }


      // generic standard notation
      /* ⎕pp←4:
         _31416e+00
         01234567890
       ∆ 432101234567
         ¯¯¯¯
      */
      int len = 0;
      if (d < 0)
      {
        buf[len++] = L'¯';
      }
      fa[1] = fa[0]; // put all the significant digits in order
      fa[0] = L'0'; // 0 so ls calculation doesn't have to special-case


      int ls = pp + 1; // length of significant digits
      while (fa[ls] == L'0')
      {
          ls--;
      }

      if (fa[pp + 3] == L'-')
      {
        buf[len] = L'0';
        buf[len + 1] = L'.';
        len += 2;
        for (int i = 0; i < exp - 1; i++)
        {
            buf[len + i] = L'0'; // zero padding
        }
        len += exp - 1;
        std::copy_n(fa.begin() + 1, ls, buf.begin() + len); // actual digits; ≡  for (int i = 0; i < ls; i++) buf[len+i] = fa[i+1];
        len += ls;
      }
      else
      {
        if (exp + 1 < ls)
        {
          std::copy_n(fa.begin() + 1, exp + 1, buf.begin() + len); // digits before '.'; ≡  for (int i = 0; i < exp+1; i++) buf[len+i] = fa[i+1];
          len += exp + 1;
          buf[len++] = L'.';
          std::copy_n(fa.begin() + 2 + exp, ls - exp - 1, buf.begin() + len); // ≡  for (int i = 0; i < ls-exp-1; i++) buf[len+i] = fa[i+(2+exp)];
          len += ls - exp - 1;
        }
        else
        {
          std::copy_n(fa.begin() + 1, ls, buf.begin() + len); // all given digits; ≡  for (int i = 0; i < ls; i++) buf[len+i] = fa[i+1];
          len += ls;
          for (int i = 0; i < exp - ls + 1; i++)
          {
              buf[len + i] = L'0'; // pad with zeroes
          }
          len += exp - ls + 1;
        }
      }
      // System.out.println(f+": sig="+ls+"; exp="+exp+"; len="+len);
      return std::string(buf, 0, len);
    }

    std::string Num::formatInt(int i)
    {
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
      return i < 0? L"¯" + std::to_wstring(-i) : Integer::toString(i);
    }

    void Num::setPrecision(int p)
    {
      pp = std::min(p, 20); // without min it'll actually create a ±length-p string of zeroes
    }

    void Num::setPrecision(int p, int s, int e)
    {
      pp = std::min(p, 20);
      if (s < -90 | e>90)
      {
          throw DomainError(L"⎕PP standard notation range too big");
      }
      sEr = s;
      eEr = e;
    }

const std::shared_ptr<Num> Num::MINUS_ONE = std::make_shared<Num>(L"-1");
const std::shared_ptr<Num> Num::ZERO = std::make_shared<Num>(L"0");
const std::shared_ptr<Num> Num::ONE = std::make_shared<Num>(L"1");
const std::vector<std::shared_ptr<Num>> Num::NUMS = std::vector<std::shared_ptr<Num>>(256);
const std::shared_ptr<Num> Num::E = std::make_shared<Num>(L"2.71828182845904523536028747135266249775724709369995");
const std::shared_ptr<Num> Num::PI = std::make_shared<Num>(L"3.1415926535897932384626433832795028841971693993751");

    Num::Num(std::string const& val)
    {
      if (StringHelper::startsWith(val, L"¯"))
      {
        num = -std::stod(val.substr(1));
      }
      else
      {
          num = std::stod(val);
      }
    }

    Num::Num(int n) : num(n)
    {
    }

    Num::Num(long long n) : num(n)
    {
    }

    Num::Num(double val) : num(val)
    {
    }

    std::shared_ptr<Num> Num::of(int n)
    {
      if (n >= 0 && n < 256)
      {
        return NUMS[n];
      }
      if (n == -1)
      {
          return MINUS_ONE;
      }
      return std::make_shared<Num>(n);
    }

const std::shared_ptr<Num> Num::NEG_ZERO = std::make_shared<Num>(-0.0);

    std::shared_ptr<Num> Num::of(double n)
    {
      if (n == 0)
      {
        return Double::doubleToRawLongBits(n) == 0? NUMS[0] : NEG_ZERO;
      }
      if (n > 0 && n < 256 && n % 1 == 0)
      {
        return NUMS[static_cast<int>(n)];
      }
      return std::make_shared<Num>(n);
    }

    std::shared_ptr<Num> Num::plus(std::shared_ptr<Num> w)
    {
      return std::make_shared<Num>(num + w->num);
    }

    std::shared_ptr<Num> Num::divide(std::shared_ptr<Num> w)
    {
      return std::make_shared<Num>(num / w->num);
    }

    std::shared_ptr<Num> Num::pow(std::shared_ptr<Num> w)
    {
      return std::make_shared<Num>(std::pow(num, w->num));
    }

    std::shared_ptr<Num> Num::minus(std::shared_ptr<Num> w)
    {
      return std::make_shared<Num>(num - w->num);
    }

    double Num::gcd(std::vector<double> &nums)
    {
      if (nums->length == 0)
      {
          return 0;
      }
      double res = nums[0];
      for (int i = 1; i < nums->length; i++)
      {
        double b = nums[i];
        while (b != 0)
        {
          double t = b;
          b = res % b;
          res = t;
        }
      }
      return res;
    }

    double Num::gcd2(double num0, double num1)
    {
      double res = num0;
      double b = num1;
      while (b != 0)
      {
        double t = b;
        b = res % b;
        res = t;
      }
      return res;
    }

    double Num::lcm2(double num0, double num1)
    {
      double a = num1;
      double b = num0;
      if (a == 0)
      {
          return 0;
      }
      while (b != 0)
      {
        double t = b;
        b = a % b;
        a = t;
      }
      return num0 * num1 / a;
    }

    double Num::lcm(std::vector<double> &nums)
    {
      if (nums->length == 0)
      {
          return 1;
      }
      double res = nums[0];
      for (int i = 1; i < nums->length; i++)
      {
        double n = nums[i];
        double a = n;
        if (a == 0)
        {
            return 0;
        }
        double b = res;
        while (b != 0)
        {
          double t = b;
          b = a % b;
          a = t;
        }
        res = n * res / a;
      }
      return res;
    }

    std::shared_ptr<Num> Num::conjugate()
    {
      return std::make_shared<Num>(num); // no complex numbers :p
    }

    std::shared_ptr<Num> Num::negate()
    {
      return std::make_shared<Num>(-num);
    }

    std::shared_ptr<Num> Num::abs()
    {
      if (num < 0)
      {
          return std::make_shared<Num>(-num);
      }
      else
      {
          return shared_from_this();
      }
    }

    std::shared_ptr<Num> Num::floor()
    {
      return std::make_shared<Num>(std::floor(num));
    }

    std::shared_ptr<Num> Num::root(std::shared_ptr<Num> root)
    {
      return std::make_shared<Num>(std::pow(num, 1 / root->num));
    }

    std::shared_ptr<Num> Num::log(std::shared_ptr<Num> root)
    {
      return std::make_shared<Num>(std::log(num) / std::log(root->num));
    }

    std::shared_ptr<Num> Num::binomial(std::shared_ptr<Num> w)
    {
      if (num % 1 != 0)
      {
          throw DomainError(L"binomial of non-integer ⍺", shared_from_this());
      }
      if (w->num % 1 != 0)
      {
          throw DomainError(L"binomial of non-integer ⍵", w);
      }
      if (w->num > num)
      {
          return Num::ZERO;
      }

      double res = 1;
      double a = num;
      double b = w->num;

      if (b > a - b)
      {
          b = a - b;
      }

      for (int i = 0; i < b; i++)
      {
        res = res * (a - i) / (i + 1);
      }
      return std::make_shared<Num>(res);
    }

    std::shared_ptr<Num> Num::ceil()
    {
      return std::make_shared<Num>(std::ceil(num));
    }

    int Num::compareTo(std::shared_ptr<Num> n)
    {
      return Double::compare(num, n->num);
    }

    bool Num::equals(std::shared_ptr<APL::types::Obj> n)
    {
      return std::dynamic_pointer_cast<Num>(n) != nullptr && (std::static_pointer_cast<Num>(n))->num == num;
    }

    int Num::asInt()
    { // warning: rounds
      return toInt(num);
    }

    int Num::toInt(double d)
    {
      return static_cast<int>(d); // TODO not round
    }

    double Num::asDouble()
    {
      return num;
    }

    std::vector<int> Num::asIntArrClone()
    { // TODO not round
      return std::vector<int>{static_cast<int>(num)};
    }

    std::vector<int> Num::asIntVec()
    {
      return std::vector<int>{static_cast<int>(num)};
    }

    std::string Num::toString()
    {
      return format(num);
    }

    std::string Num::oneliner(std::vector<int> &ignored)
    {
      return format(num);
    }

    std::shared_ptr<APL::types::Value> Num::ofShape(std::vector<int> &sh)
    {
      return SingleItemArr::maybe(shared_from_this(), sh);
    }

    std::shared_ptr<Num> Num::max(std::shared_ptr<Num> a, std::shared_ptr<Num> b)
    {
      return a->num > b->num? a : b;
    }

    std::shared_ptr<Num> Num::min(std::shared_ptr<Num> a, std::shared_ptr<Num> b)
    {
      return a->num < b->num? a : b;
    }

    int Num::hashCode()
    {
      if (num == 0.0)
      {
          return 0; // ¯0 == 0
      }
      return Double::hashCode(num);
    }

    std::shared_ptr<APL::types::Value> Num::safePrototype()
    {
      return ZERO;
    }

    std::vector<std::shared_ptr<APL::types::Value>> Num::valuesCopy()
    {
      return std::vector<std::shared_ptr<APL::types::Value>>{shared_from_this()};
    }

    std::vector<double> Num::asDoubleArr()
    {
      return std::vector<double>{num};
    }

    std::vector<double> Num::asDoubleArrClone()
    {
      return std::vector<double>{num};
    }

    bool Num::quickDoubleArr()
    {
      return true;
    }
}
