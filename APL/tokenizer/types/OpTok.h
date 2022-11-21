#pragma once

#include <APL/tokenizer/Token.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types {

    using Token = APL::tokenizer::Token;

    class OpTok : public Token
    {
  public:
      const std::string op;

      OpTok(std::string const& line, int spos, int epos, std::string const& op);

      std::string toRepr() override;

    protected:
        std::shared_ptr<OpTok> shared_from_this() {
            return std::static_pointer_cast<OpTok>(APL::tokenizer::Token::shared_from_this());
        }
    };
}
