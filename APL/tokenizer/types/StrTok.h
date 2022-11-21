#pragma once

#include <APL/Main.h>
#include <APL/tokenizer/Token.h>
#include <APL/types/arrs/ChrArr.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types {

// using Token = APL::tokenizer::Token;
// using ChrArr = APL::types::arrs::ChrArr;

class StrTok : public Token
{
public:
    const std::shared_ptr<APL::types::arrs::ChrArr> val;
    const std::string parsed;

    StrTok(std::string const& line, int spos, int epos, std::string const& str);

    std::string toRepr() override;

protected:
    std::shared_ptr<StrTok> shared_from_this()
    {
        return std::static_pointer_cast<StrTok>(APL::tokenizer::Token::shared_from_this());
    }
};

}
