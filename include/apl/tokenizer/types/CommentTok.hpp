#pragma once

#include <apl/tokenizer/Token.hpp>

struct CommentTok : Token {
    CommentTok(std::string raw, int spos, int epos)
        : Token(raw, spos, epos)
    {}

    std::string toRepr() const override {
        return nullptr;
    }
};
