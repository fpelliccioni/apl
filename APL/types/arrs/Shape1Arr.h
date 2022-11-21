#pragma once

#include <APL/errors/DomainError.h>
#include <APL/types/Arr.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::arrs
{

    // using namespace APL::types;

    class Shape1Arr : public Arr
    {
  private:
      static const std::vector<int> SHAPE;
      const std::shared_ptr<APL::types::Value> item;

  public:
      Shape1Arr(std::shared_ptr<APL::types::Value> item);

      std::vector<int> asIntArrClone() override;

      int asInt() override;

      std::shared_ptr<APL::types::Value> get(int i) override;

      std::string asString() override;

      std::shared_ptr<APL::types::Value> prototype() override;
      std::shared_ptr<APL::types::Value> safePrototype() override;
      std::shared_ptr<APL::types::Value> ofShape(std::vector<int> &sh) override;

      std::vector<std::shared_ptr<APL::types::Value>> valuesCopy() override;

      bool quickDoubleArr() override;

      std::vector<double> asDoubleArr() override;

    protected:
        std::shared_ptr<Shape1Arr> shared_from_this() {
            return std::static_pointer_cast<Shape1Arr>(Arr::shared_from_this());
        }
    };
}
