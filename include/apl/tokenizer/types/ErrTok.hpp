#pragma once

#include <apl/tokenizer/Token.hpp>

struct ErrTok : Token {
    ErrTok(std::string raw, int spos, int epos)
        : Token(raw, spos, epos)
    {}

    ErrTok(std::string raw, int onepos)
        : Token(raw, onepos, onepos + 1)
    {}

    std::string toRepr() const override {
        return nullptr;
    }
};
