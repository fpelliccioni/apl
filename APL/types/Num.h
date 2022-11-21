#pragma once

#include <APL/errors/DomainError.h>
#include <APL/types/arrs/SingleItemArr.h>
#include <APL/types/Primitive.h>
// #include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types {
class Obj;
}


namespace APL::types
{
    class Num : public Primitive
    {

  public:
      static const std::shared_ptr<Num> NEGINF;
      static const std::shared_ptr<Num> POSINF;
      static constexpr long long MAX_SAFE_INT = 9007199254740992LL;


      static int pp;
      static int sEr;
          static int eEr;
      private:
          class StaticConstructor : public std::enable_shared_from_this<StaticConstructor>
          {
          public:
              StaticConstructor();
          };

      private:
          static Num::StaticConstructor staticConstructor;

      static const std::vector<wchar_t> buf;
  public:
      static std::string format(double d);
      static std::string formatInt(int i);
      static void setPrecision(int p);
      static void setPrecision(int p, int s, int e);
      static const std::shared_ptr<Num> MINUS_ONE;
      static const std::shared_ptr<Num> ZERO;
      static const std::shared_ptr<Num> ONE;
      static const std::vector<std::shared_ptr<Num>> NUMS;


      static const std::shared_ptr<Num> E;
      static const std::shared_ptr<Num> PI;
      const double num;
      Num(std::string const& val);

      Num(int n);
      Num(long long n);
      Num(double val);

      static std::shared_ptr<Num> of(int n);

  private:
      static const std::shared_ptr<Num> NEG_ZERO;
  public:
      static std::shared_ptr<Num> of(double n);

      virtual std::shared_ptr<Num> plus(std::shared_ptr<Num> w);
      virtual std::shared_ptr<Num> divide(std::shared_ptr<Num> w);
      virtual std::shared_ptr<Num> pow(std::shared_ptr<Num> w);
      virtual std::shared_ptr<Num> minus(std::shared_ptr<Num> w);

      static double gcd(std::vector<double> &nums);
      static double gcd2(double num0, double num1);

      static double lcm2(double num0, double num1);
      static double lcm(std::vector<double> &nums);

      virtual std::shared_ptr<Num> conjugate();
      virtual std::shared_ptr<Num> negate();
      virtual std::shared_ptr<Num> abs();

      virtual std::shared_ptr<Num> floor();
      virtual std::shared_ptr<Num> root(std::shared_ptr<Num> root);
      virtual std::shared_ptr<Num> log(std::shared_ptr<Num> root);

      virtual std::shared_ptr<Num> binomial(std::shared_ptr<Num> w);


      virtual std::shared_ptr<Num> ceil();

      virtual int compareTo(std::shared_ptr<Num> n);


      bool equals(std::shared_ptr<APL::types::Obj> n) override;

      int asInt() override;
      static int toInt(double d);
      double asDouble() override;

      std::vector<int> asIntArrClone() override;
      std::vector<int> asIntVec() override;

      std::string toString() override;
      std::string oneliner(std::vector<int> &ignored) override;

      std::shared_ptr<APL::types::Value> ofShape(std::vector<int> &sh) override;

      static std::shared_ptr<Num> max(std::shared_ptr<Num> a, std::shared_ptr<Num> b);
      static std::shared_ptr<Num> min(std::shared_ptr<Num> a, std::shared_ptr<Num> b);

      virtual int hashCode();

      std::shared_ptr<APL::types::Value> safePrototype() override;

      std::vector<std::shared_ptr<APL::types::Value>> valuesCopy() override;

      std::vector<double> asDoubleArr() override;

      std::vector<double> asDoubleArrClone() override;

      bool quickDoubleArr() override;

    protected:
        std::shared_ptr<Num> shared_from_this() {
            return std::static_pointer_cast<Num>(Primitive::shared_from_this());
        }
    };
}
