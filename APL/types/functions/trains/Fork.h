#pragma once

#include <APL/errors/DomainError.h>
#include <APL/types/Fun.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <string>
#include <memory>

namespace APL::types::functions::trains
{

    // using namespace APL::types;

    class Fork : public Fun
    {
  private:
      const std::shared_ptr<APL::types::Obj> f;
      const std::shared_ptr<Fun> g, h;
  public:
      Fork(std::shared_ptr<APL::types::Obj> f, std::shared_ptr<Fun> g, std::shared_ptr<Fun> h);

      std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;
      std::shared_ptr<APL::types::Value> callInv(std::shared_ptr<APL::types::Value> w) override;
      std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

      std::shared_ptr<APL::types::Value> callInvW(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

      std::shared_ptr<APL::types::Value> callInvA(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;

      std::string repr() override;

      std::shared_ptr<APL::types::Value> under(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w) override;

  private:
      class FunAnonymousInnerClass : public Fun
      {
      private:
          std::shared_ptr<Fork> outerInstance;

          std::shared_ptr<APL::types::Obj> o;
          std::shared_ptr<APL::types::APL::types::Value> fa;

      public:
          FunAnonymousInnerClass(std::shared_ptr<Fork> outerInstance, std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::APL::types::Value> fa);

          std::string repr() override;
          std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;

      protected:
          std::shared_ptr<FunAnonymousInnerClass> shared_from_this()
          {
              return std::static_pointer_cast<FunAnonymousInnerClass>(Fun::shared_from_this());
          }
      };

    protected:
        std::shared_ptr<Fork> shared_from_this() {
            return std::static_pointer_cast<Fork>(Fun::shared_from_this());
        }
    };
}
