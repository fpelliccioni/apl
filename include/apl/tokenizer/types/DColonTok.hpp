#pragma once

#include <apl/tokenizer/Token.hpp>

struct DColonTok : Token {
    DColonTok(std::string line, int spos, int epos)
        : Token(line, spos, epos);
    {}

    std::string toRepr() const override {
        return "::";
    }
};