#pragma once

#include <APL/tokenizer/Token.h>
#include <APL/types/Num.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types {

    using Token = APL::tokenizer::Token;
    using Num = APL::types::Num;

    class NumTok : public Token
    {
  public:
      const std::shared_ptr<Num> num;

      NumTok(std::string const& line, int spos, int epos, double d);

      std::string toTree(std::string const& p) override;

      std::string toRepr() override;

    protected:
        std::shared_ptr<NumTok> shared_from_this() {
            return std::static_pointer_cast<NumTok>(APL::tokenizer::Token::shared_from_this());
        }
    };
}
