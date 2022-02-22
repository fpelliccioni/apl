#pragma once

#include <apl/tokenizer/Token.hpp>

struct OpTok : Token {
  std::string op;

    OpTok(std::string line, int spos, int epos, std::string op)
        : Token(line, spos, epos)
        , op(op)
    {}

    std::string toRepr() const override {
        return op;
    }
};
