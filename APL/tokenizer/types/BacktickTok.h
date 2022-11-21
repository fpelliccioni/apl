#pragma once

#include <APL/tokenizer/Token.h>
#include <APL/tokenizer/types/LineTok.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types {

    using Token = APL::tokenizer::Token;

    class BacktickTok : public Token
    {
  private:
      const std::shared_ptr<APL::tokenizer::types::LineTok> val;

  public:
      BacktickTok(std::string const& raw, int spos, int epos, std::shared_ptr<Token> val);

      std::string toRepr() override;

      virtual std::shared_ptr<APL::tokenizer::types::LineTok> value();

    protected:
        std::shared_ptr<BacktickTok> shared_from_this() {
            return std::static_pointer_cast<BacktickTok>(APL::tokenizer::Token::shared_from_this());
        }
    };
}
