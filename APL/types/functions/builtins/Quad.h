#pragma once

#include <APL/types/Settable.h>
#include <APL/Scope.h>
#include <APL/types/Callable.h>
#include <APL/types/Obj.h>
#include <APL/Type.h>
#include <string>
#include <memory>

namespace APL::types::functions::builtins
{

    // using namespace APL;
    // using namespace APL::types;

    class Quad : public Settable
    {
  private:
      const std::shared_ptr<Scope> sc;
  public:
      Quad(std::shared_ptr<Scope> sc);

      void set(std::shared_ptr<APL::types::Obj> v, std::shared_ptr<APL::types::Callable> blame) override;

      std::shared_ptr<APL::types::Obj> get() override;
      Type type() override;

      std::string toString() override;

    protected:
        std::shared_ptr<Quad> shared_from_this() {
            return std::static_pointer_cast<Quad>(Settable::shared_from_this());
        }
    };
}
