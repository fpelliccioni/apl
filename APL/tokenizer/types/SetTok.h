#pragma once

#include <APL/tokenizer/Token.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types {

    using Token = APL::tokenizer::Token;

    class SetTok : public Token
    {
  public:
      SetTok(std::string const& line, int spos, int epos);

      std::string toRepr() override;

    protected:
        std::shared_ptr<SetTok> shared_from_this() {
            return std::static_pointer_cast<SetTok>(APL::tokenizer::Token::shared_from_this());
        }
    };
}
