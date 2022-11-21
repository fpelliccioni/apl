#pragma once

#include <APL/tokenizer/Token.h>
#include <string>
#include <memory>

namespace APL::tokenizer::types {

using Token = APL::tokenizer::Token;

class NameTok : public Token {
public:
    const std::string name;

    NameTok(std::string const& line, int spos, int epos, std::string const& name);

    std::string toTree(std::string const& p) override;

    std::string toRepr() override;

protected:
    std::shared_ptr<NameTok> shared_from_this() {
        return std::static_pointer_cast<NameTok>(APL::tokenizer::Token::shared_from_this());
    }
};

}
