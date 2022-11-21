#pragma once

#include <APL/Type.h>
#include <APL/types/arrs/SingleItemArr.h>
#include <APL/types/Primitive.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <memory>

namespace APL::types
{

    using Type = APL::Type;

    class Null : public Primitive
    {
  public:
      static const std::shared_ptr<Null> NULL;
  private:
      Null();

  public:
      virtual std::string toString();

      Type type() override;

      std::shared_ptr<APL::types::Value> ofShape(std::vector<int> &sh) override;

      virtual int hashCode();

    protected:
        std::shared_ptr<Null> shared_from_this() {
            return std::static_pointer_cast<Null>(Primitive::shared_from_this());
        }
    };
}
