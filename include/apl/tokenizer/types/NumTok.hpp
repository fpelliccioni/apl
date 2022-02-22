#pragma once

#include <apl/tokenizer/Token.hpp>

struct NumTok : Token {
    Num num;

    NumTok(std::string line, int spos, int epos, double d)
        : Token(line, spos, epos)
        , this.num(new Num(d))
    {}

    std::string toTree(std::string p) const override {
        return p + "num : " + num + '\n';
    }

    std::string toRepr() const override {
        return source();
    }
};
