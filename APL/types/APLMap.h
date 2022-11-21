#pragma once

#include <APL/Main.h>
#include <APL/types/arrs/SingleItemArr.h>
#include <APL/types/Primitive.h>
#include <APL/types/Value.h>
#include <APL/types/Obj.h>
#include <APL/types/Arr.h>
#include <APL/types/Settable.h>
#include <APL/types/Callable.h>
#include <string>
#include <vector>
#include <memory>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace APL::types { class MapPointer; }

namespace APL::types
{


    class APLMap : public Primitive
    {

  public:
      virtual std::shared_ptr<MapPointer> get(std::shared_ptr<APL::types::Value> k);

      virtual std::shared_ptr<APL::types::Obj> getRaw(std::shared_ptr<APL::types::Value> k) = 0;

      virtual std::shared_ptr<APL::types::Obj> getRaw(std::string const& k);
      virtual std::shared_ptr<MapPointer> get(std::string const& k);

      virtual void set(std::shared_ptr<APL::types::Value> k, std::shared_ptr<APL::types::Obj> v) = 0;
      virtual std::shared_ptr<Arr> allValues() = 0;
      virtual std::shared_ptr<Arr> allKeys() = 0;
      virtual std::shared_ptr<Arr> kvPair() = 0;
      virtual int size() = 0;

  public:
      class MapPointer : public Settable
      {
    private:
        const std::shared_ptr<APLMap> map;
        const std::shared_ptr<APL::types::Value> k;

    public:
        MapPointer(std::shared_ptr<APLMap> map, std::shared_ptr<APL::types::Value> k);

        void set(std::shared_ptr<APL::types::Obj> v, std::shared_ptr<APL::types::Callable> blame) override;

        virtual std::string toString();

      protected:
          std::shared_ptr<MapPointer> shared_from_this()
          {
              return std::static_pointer_cast<MapPointer>(Settable::shared_from_this());
          }
      };

  public:
      std::shared_ptr<APL::types::Value> ofShape(std::vector<int> &sh) override;

    protected:
        std::shared_ptr<APLMap> shared_from_this() {
            return std::static_pointer_cast<APLMap>(Primitive::shared_from_this());
        }
    };
}
