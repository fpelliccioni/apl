#pragma once

#include <apl/tokenizer/Token.hpp>

struct ColonTok : Token {
    ColonTok(std::string line, int spos, int epos)
        : Token(line, spos, epos);
    {}

    std::string toRepr() const override {
        return ":";
    }
};