#pragma once

#include <APL/Main.h>
#include <APL/errors/DomainError.h>
#include <APL/types/Arr.h>
#include <APL/types/Value.h>
#include <APL/types/Obj.h>
#include <string>
#include <vector>
#include <cassert>
#include <memory>
#include <helpers/tangible_string_helper.h>
#include <helpers/tangible_stringbuilder.h>

namespace APL::types::arrs
{

    // using namespace APL::types;


    class HArr : public Arr
    {
  private:
      const std::vector<std::shared_ptr<APL::types::Value>> arr;
  public:
      HArr(std::vector<std::shared_ptr<APL::types::Value>> &v);
      HArr(std::vector<std::shared_ptr<APL::types::Value>> &v, std::vector<int> &sh);

    //   HArr(std::vector<std::shared_ptr<APL::types::Value>> &v);
    //   HArr(std::vector<std::shared_ptr<APL::types::Value>> &v, std::vector<int> &sh);

      std::vector<int> asIntArrClone() override;

      int asInt() override;

      std::shared_ptr<APL::types::Value> get(int i) override;

      virtual bool equals(std::shared_ptr<APL::types::Obj> o);

      std::string asString() override;

      std::shared_ptr<APL::types::Value> prototype() override;
      std::shared_ptr<APL::types::Value> safePrototype() override;
      std::vector<std::shared_ptr<APL::types::Value>> values() override;
      std::vector<std::shared_ptr<APL::types::Value>> valuesCopy() override;
      std::shared_ptr<APL::types::Value> ofShape(std::vector<int> &sh) override;


    protected:
        std::shared_ptr<HArr> shared_from_this() {
            return std::static_pointer_cast<HArr>(Arr::shared_from_this());
        }
    };
}
