#pragma once

#include <apl/tokenizer/Token.hpp>

struct ScopeTok : Token {
    public ScopeTok(std::string raw, int spos, int epos)
        : Token(raw, spos, epos)
    {}

    std::string toRepr() const override {
        return "#";
    }
};
