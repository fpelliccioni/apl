#pragma once

#include <APL/Main.h>
#include <APL/types/Value.h>
#include <APL/types/Obj.h>
#include <APL/types/Callable.h>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <helpers/tangible_rectangular_vectors.h>
#include <helpers/tangible_string_helper.h>
#include <helpers/tangible_stringbuilder.h>

namespace APL::types
{

    // using namespace APL::errors;
    // using namespace APL::types::arrs;


    class Arr : public APL::types::Value
    {
  public:
      Arr(std::vector<int> &shape);
      Arr(std::vector<int> &shape, int ia);
      Arr(std::vector<int> &shape, int ia, int rank);

      virtual std::string string(bool quote);
      std::string toString() override;
      std::string oneliner(std::vector<int> &where) override;
      virtual std::shared_ptr<Arr> reverseOn(int dim);


      static std::shared_ptr<APL::types::Value> createL(std::vector<std::shared_ptr<APL::types::Value>> &v, std::vector<int> &sh);

      static std::shared_ptr<Arr> create(std::vector<std::shared_ptr<APL::types::Value>> &v);
      static std::shared_ptr<Arr> create(std::vector<std::shared_ptr<APL::types::Value>> &v, std::vector<int> &sh);

    //   static std::shared_ptr<Arr> create(std::vector<std::shared_ptr<APL::types::Value>> &v);
    //   static std::shared_ptr<Arr> create(std::vector<std::shared_ptr<APL::types::Value>> &v, std::vector<int> &sh);

      virtual bool equals(std::shared_ptr<APL::types::Obj> o);
  protected:
      int hash = 0;
  public:
      virtual int hashCode();

  protected:
      virtual int shapeHash(int hash);

  public:
      static int prod(std::vector<int> &ia);

      static void eqShapes(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);
      static void eqShapes(std::vector<int> &a, std::vector<int> &w, std::shared_ptr<APL::types::Callable> blame);

    protected:
        std::shared_ptr<Arr> shared_from_this() {
            return std::static_pointer_cast<Arr>(APL::types::Value::shared_from_this());
        }
    };
}
