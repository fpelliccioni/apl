#pragma once

#include <APL/errors/DomainError.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types
{


    class Primitive : public APL::types::Value
    {
  private:
      static const std::vector<int> SHAPE;

  public:
      Primitive();

      std::shared_ptr<APL::types::Value> get(int i) final override;

      std::shared_ptr<APL::types::Value> first() final override;

      std::vector<int> asIntArrClone() override;
      std::vector<int> asIntVec() override;

      int asInt() override;

      std::string asString() override;

      std::shared_ptr<APL::types::Value> prototype() final override;
      std::shared_ptr<APL::types::Value> safePrototype() override;

      std::shared_ptr<APL::types::Value> squeeze() override;

    protected:
        std::shared_ptr<Primitive> shared_from_this() {
            return std::static_pointer_cast<Primitive>(APL::types::Value::shared_from_this());
        }
    };
}
