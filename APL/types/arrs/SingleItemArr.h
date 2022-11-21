#pragma once

#include <APL/Main.h>
#include <APL/errors/DomainError.h>
#include <APL/types/Arr.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_stringbuilder.h>

namespace APL::types::arrs
{

    // using namespace APL::types;

    //NOTE(fernando)
    // using Iterator = java::util::Iterator;

    class SingleItemArr : public Arr
    {
  private:
      const std::shared_ptr<APL::types::Value> item;

  public:
      SingleItemArr(std::shared_ptr<APL::types::Value> item, std::vector<int> &shape);

      static std::shared_ptr<APL::types::Value> maybe(std::shared_ptr<APL::types::Value> item, std::vector<int> &sh);

      std::vector<int> asIntArrClone() override;

      int asInt() override;

      std::shared_ptr<APL::types::Value> get(int i) override;

      std::shared_ptr<APL::types::Value> first() override;

      std::string asString() override;

      std::shared_ptr<APL::types::Value> prototype() override;
      std::shared_ptr<APL::types::Value> safePrototype() override;
      std::shared_ptr<APL::types::Value> ofShape(std::vector<int> &sh) override;

      bool quickDoubleArr() override;
      std::vector<std::shared_ptr<APL::types::Value>> valuesCopy() override;

      double sum() override;

      std::vector<double> asDoubleArr() override;

      std::vector<double> asDoubleArrClone() override;

      std::shared_ptr<APL::types::Value> squeeze() override;

      std::string oneliner(std::vector<int> &where) override;

    //NOTE(fernando)
    //   std::shared_ptr<Iterator<std::shared_ptr<APL::types::Value>>> iterator() override;

  private:
      class IteratorAnonymousInnerClass : public std::enable_shared_from_this<IteratorAnonymousInnerClass>
                                          //NOTE(fernando)
                                          // , public Iterator<std::shared_ptr<APL::types::Value>>
      {
      private:
          std::shared_ptr<SingleItemArr> outerInstance;

      public:
          IteratorAnonymousInnerClass(std::shared_ptr<SingleItemArr> outerInstance);

          int i = 0;
          bool hasNext();

          std::shared_ptr<APL::types::Value> next();
      };

    protected:
        std::shared_ptr<SingleItemArr> shared_from_this() {
            return std::static_pointer_cast<SingleItemArr>(Arr::shared_from_this());
        }
    };
}
