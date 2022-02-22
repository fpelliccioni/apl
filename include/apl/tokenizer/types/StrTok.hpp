#pragma once

#include <apl/tokenizer/Token.hpp>

struct StrTok : Token {
    ChrArr val;
    std::string parsed;

    StrTok(std::string line, int spos, int epos, std::string str)
        : Token(line, spos, epos)
        , parsed(str)
        , val(Main.toAPL(str))
    {}

    std::string toRepr() const override {
        return source();
    }
};
