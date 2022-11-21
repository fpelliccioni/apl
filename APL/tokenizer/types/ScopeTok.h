#pragma once

#include <APL/tokenizer/Token.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types {

    using Token = APL::tokenizer::Token;

    class ScopeTok : public Token
    {
  public:
      ScopeTok(std::string const& raw, int spos, int epos);

      std::string toRepr() override;

    protected:
        std::shared_ptr<ScopeTok> shared_from_this() {
            return std::static_pointer_cast<ScopeTok>(APL::tokenizer::Token::shared_from_this());
        }
    };
}
