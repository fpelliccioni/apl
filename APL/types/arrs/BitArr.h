#pragma once

#include <APL/Main.h>
#include <APL/errors/DomainError.h>
#include <APL/types/Arr.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <memory>
#include <helpers/tangible_string_helper.h>
#include <helpers/tangible_stringbuilder.h>

namespace APL::types::arrs
{

    // using namespace APL::types;


    class BitArr final : public Arr
    {

  public:
      const std::vector<long long> arr;
      // data[0]&1 - 1st item, (data[0]&0b10)
      // filler can be anything

      BitArr(std::vector<long long> &arr, std::vector<int> &shape);

      BitArr(std::vector<long long> &arr, std::vector<int> &shape, int ia);

      static std::shared_ptr<BitArr> of(std::shared_ptr<Arr> a);

      static std::vector<long long> convert(std::vector<double> &arr);

      static int sizeof_Keyword(std::shared_ptr<APL::types::Value> w);

      static int sizeof_Keyword(std::vector<int> &sh);
      static int sizeof_Keyword(int am);

      static std::shared_ptr<APL::types::Value> fill(std::shared_ptr<APL::types::Value> v, bool b);

      std::vector<int> asIntArrClone() override;

      std::vector<double> asDoubleArr() override;

      int asInt() override;

      std::shared_ptr<APL::types::Value> get(int i) override;

      std::string asString() override;

      std::shared_ptr<APL::types::Value> prototype() override;
      std::shared_ptr<APL::types::Value> safePrototype() override;

      std::shared_ptr<APL::types::Value> ofShape(std::vector<int> &sh) override;

      bool quickDoubleArr() override;

      int llen();

      void setEnd(bool on);

      double sum() override;

      int isum();

  public:
      class BA : public std::enable_shared_from_this<BA>
      { // bit adder
    private:
        const std::vector<long long> a; // no trailing garbage allowed!
        const std::vector<int> sh;
        int i = 0, o = 0; // index, offset
    public:
        BA(int am);
        BA(std::vector<int> &sh);
        BA(std::vector<long long> &a, int start, std::vector<int> &sh);
        virtual void add(bool b);

        virtual void add(long long l);

        virtual void add(std::shared_ptr<BitArr> a);

        virtual void add(std::shared_ptr<BitArr> g, int s, int e);

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("ConstantExpression") public void fill(int n)
        virtual void fill(int n);
        virtual void skip(int n);

        virtual std::shared_ptr<BitArr> finish();
      };

  public:
      static std::string str64(long long l);

      long long longFrom(int s);

  public:
      class BC : public std::enable_shared_from_this<BC>
      { // boolean creator
    public:
        const std::vector<long long> arr;
        const std::vector<int> sz;
        BC(std::vector<int> &sz);
        virtual std::shared_ptr<BitArr> finish();

        virtual void set(int pos);
        virtual void clear(int pos);
      };
  public:
      static std::shared_ptr<BC> create(std::vector<int> &sh);
  public:
      class BR : public std::enable_shared_from_this<BR>
      { // boolean read
      private:
          std::shared_ptr<BitArr> outerInstance;

      public:
          BR(std::shared_ptr<BitArr> outerInstance);

    private:
        int i = 0, o = 0;
    public:
        virtual bool read();

        virtual void skip(int n);
      };

  public:
      std::shared_ptr<APL::types::Value> squeeze() override;

      std::shared_ptr<BR> read();

      std::vector<std::shared_ptr<APL::types::Value>> valuesCopy() override;

    protected:
        std::shared_ptr<BitArr> shared_from_this() {
            return std::static_pointer_cast<BitArr>(Arr::shared_from_this());
        }
    };
}
