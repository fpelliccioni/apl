#pragma once

#include <APL/types/functions/Builtin.h>
#include <APL/types/Value.h>
#include <APL/types/Num.h>
#include <APL/types/BigValue.h>
#include <string>
#include <vector>
#include <cmath>
#include <memory>

namespace APL::types::functions::builtins::fns
{

    // using namespace APL::types;
    using Builtin = APL::types::functions::Builtin;

    class CeilingBuiltin : public Builtin
    {
  public:
      std::string repr() override;



      std::shared_ptr<APL::types::Value> identity() override;

  private:
      static const std::shared_ptr<NumMV> NF;

  private:
      class NumMVAnonymousInnerClass : public std::enable_shared_from_this<NumMVAnonymousInnerClass>, public NumMV
      {
      public:
          std::shared_ptr<APL::types::Value> call(std::shared_ptr<Num> w) override;
          void call(std::vector<double> &res, std::vector<double> &a) override;
      };
  public:
      std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;

  private:
      static const std::shared_ptr<D_NNeN> DNF;

  private:
      class D_NNeNAnonymousInnerClass : public D_NNeN
      {
      public:
          double on(double a, double w) override;
          void on(std::vector<double> &res, double a, std::vector<double> &w) override;
          void on(std::vector<double> &res, std::vector<double> &a, double w) override;
          void on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w) override;
          std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::BigValue> a, std::shared_ptr<APL::types::BigValue> w) override;

      protected:
          std::shared_ptr<D_NNeNAnonymousInnerClass> shared_from_this()
          {
              return std::static_pointer_cast<D_NNeNAnonymousInnerClass>(D_NNeN::shared_from_this());
          }
      };
  public:
      std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a0, std::shared_ptr<APL::types::Value> w0) override;

    protected:
        std::shared_ptr<CeilingBuiltin> shared_from_this() {
            return std::static_pointer_cast<CeilingBuiltin>(APL::types::functions::Builtin::shared_from_this());
        }
    };
}
