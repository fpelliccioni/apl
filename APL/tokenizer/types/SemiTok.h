#pragma once

#include <APL/tokenizer/Token.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types {

    using Token = APL::tokenizer::Token;

    class SemiTok : public Token
    {
  public:
      SemiTok(std::string const& line, int spos, int epos);

      std::string toRepr() override;

    protected:
        std::shared_ptr<SemiTok> shared_from_this() {
            return std::static_pointer_cast<SemiTok>(APL::tokenizer::Token::shared_from_this());
        }
    };
}
