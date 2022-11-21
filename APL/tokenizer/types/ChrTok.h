#pragma once

#include <APL/Main.h>
#include <APL/tokenizer/Token.h>
#include <APL/types/Value.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types {

    using Token = APL::tokenizer::Token;
    // using namespace APL::types;

    class ChrTok : public Token
    {
  public:
      const std::shared_ptr<APL::types::Value> val;
      const std::string parsed;

      ChrTok(std::string const& line, int spos, int epos, std::string const& str);

      std::string toRepr() override;

    protected:
        std::shared_ptr<ChrTok> shared_from_this() {
            return std::static_pointer_cast<ChrTok>(APL::tokenizer::Token::shared_from_this());
        }
    };
}
