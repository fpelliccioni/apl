#pragma once

#include <APL/errors/DomainError.h>
#include <APL/tokenizer/types/DfnTok.h>
#include <APL/types/functions/VarArr.h>
#include <APL/types/Fun.h>
#include <APL/Scope.h>
#include <APL/types/Value.h>
#include <APL/types/Obj.h>
#include <string>
#include <vector>
#include <any>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::userDefined
{

    // using namespace APL;
    using DfnTok = APL::tokenizer::types::DfnTok;
    // using namespace APL::types;

    class Dfn : public Fun
    {
  public:
      const std::shared_ptr<DfnTok> code;
      Dfn(std::shared_ptr<DfnTok> t, std::shared_ptr<Scope> sc);
      std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) override;
      std::shared_ptr<APL::types::Obj> callObj(std::shared_ptr<APL::types::Value> w) override;
      std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;
      std::shared_ptr<APL::types::Obj> callObj(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) override;
      std::string repr() override;

      std::string name() override;

    protected:
        std::shared_ptr<Dfn> shared_from_this() {
            return std::static_pointer_cast<Dfn>(Fun::shared_from_this());
        }
    };
}
