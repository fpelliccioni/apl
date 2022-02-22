#pragma once

#include <apl/tokenizer/Token.hpp>

struct ChrTok : Token {
    Value val;
    std::string parsed;

    ChrTok(std::string line, int spos, int epos, std::string str)
        : Token(line, spos, epos)
        , parsed(str)
    {
        if (str.length() == 1) val = Char::of(str.charAt(0));
        else val = Main.toAPL(str);
    }

    std::string toRepr() const override{
        return source();
    }
};
