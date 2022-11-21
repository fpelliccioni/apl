#pragma once

#include <APL/errors/SyntaxError.h>
#include <APL/types/APLMap.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/Arr.h>
#include <string>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types
{


    class SimpleMap : public APLMap
    {
  public:
      std::shared_ptr<APL::types::Obj> getRaw(std::shared_ptr<APL::types::Value> k) override;

      virtual std::shared_ptr<APL::types::Obj> getv(std::string const& s) = 0;
      virtual void setv(std::string const& s, std::shared_ptr<APL::types::Obj> v) = 0;

      void set(std::shared_ptr<APL::types::Value> k, std::shared_ptr<APL::types::Obj> v) override;

      std::shared_ptr<Arr> allValues() override;

      std::shared_ptr<Arr> allKeys() override;

      std::shared_ptr<Arr> kvPair() override;

      int size() override;

    protected:
        std::shared_ptr<SimpleMap> shared_from_this() {
            return std::static_pointer_cast<SimpleMap>(APLMap::shared_from_this());
        }
    };
}
