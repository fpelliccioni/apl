#pragma once

#include <apl/tokenizer/Token.hpp>

struct DiamondTok : Token {
    public DiamondTok(std::string raw, int pos)
        : Token(raw, pos, pos+1)
    {}

    std::string toRepr() const override {
        return null;
    }
};
