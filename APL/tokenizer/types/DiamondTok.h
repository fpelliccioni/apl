#pragma once

#include <APL/tokenizer/Token.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types {

    using Token = APL::tokenizer::Token;

    class DiamondTok : public Token
    {
  public:
      DiamondTok(std::string const& raw, int pos);

      std::string toRepr() override;

    protected:
        std::shared_ptr<DiamondTok> shared_from_this() {
            return std::static_pointer_cast<DiamondTok>(APL::tokenizer::Token::shared_from_this());
        }
    };
}
