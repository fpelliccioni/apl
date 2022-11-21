#pragma once

#include <APL/tokenizer/Token.h>
#include <APL/types/BigValue.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types {

// using Token = APL::tokenizer::Token;
// using BigValue = APL::types::BigValue;

class BigTok : public Token
{
public:
    const std::shared_ptr<APL::types::BigValue> val;
    BigTok(std::string const& line, int spos, int epos, std::shared_ptr<APL::types::BigValue> val);
    std::string toRepr() override;

protected:
    std::shared_ptr<BigTok> shared_from_this()
    {
        return std::static_pointer_cast<BigTok>(APL::tokenizer::Token::shared_from_this());
    }
};

}
