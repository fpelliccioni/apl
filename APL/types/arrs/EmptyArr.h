#pragma once

#include <APL/types/Arr.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <helpers/tangible_exception_helper.h>
#include <cassert>
#include <memory>

namespace APL::types::arrs
{

    // using namespace APL::errors;
    // using namespace APL::types;

    //NOTE(fernando)
    // using Iterator = java::util::Iterator;

    class EmptyArr : public Arr
    {
  public:
      static const std::vector<int> SHAPE0;
      static const std::shared_ptr<EmptyArr> SHAPE0Q;
      static const std::shared_ptr<EmptyArr> SHAPE0N;
      static const std::vector<int> NOINTS;
  private:
      const std::shared_ptr<APL::types::Value> proto;
  public:
      EmptyArr(std::vector<int> &sh, std::shared_ptr<APL::types::Value> proto);

      std::vector<int> asIntArrClone() override;

      int asInt() override;

      bool quickDoubleArr() override;

      std::vector<double> asDoubleArr() override;

      std::shared_ptr<APL::types::Value> get(int i) override;

      std::string asString() override;

      std::shared_ptr<APL::types::Value> prototype() override;
      std::shared_ptr<APL::types::Value> safePrototype() override;

      std::shared_ptr<APL::types::Value> ofShape(std::vector<int> &sh) override;

  private:
      static const std::vector<std::shared_ptr<APL::types::Value>> NO_VALUES;
  public:
      std::vector<std::shared_ptr<APL::types::Value>> valuesCopy() override;

      std::shared_ptr<APL::types::Value> squeeze() override;



  private:
      //NOTE(fernando)
    //   static const std::shared_ptr<Iterator<std::shared_ptr<APL::types::Value>>> EIT;

  private:
      class IteratorAnonymousInnerClass : public std::enable_shared_from_this<IteratorAnonymousInnerClass>
                                          //NOTE(fernando)
                                          // , public Iterator<std::shared_ptr<APL::types::Value>>
      {
      public:
          bool hasNext();
          std::shared_ptr<APL::types::Value> next();
      };
  public:
      //NOTE(fernando)
    //   std::shared_ptr<Iterator<std::shared_ptr<APL::types::Value>>> iterator() override;

    protected:
        std::shared_ptr<EmptyArr> shared_from_this() {
            return std::static_pointer_cast<EmptyArr>(Arr::shared_from_this());
        }
    };
}
