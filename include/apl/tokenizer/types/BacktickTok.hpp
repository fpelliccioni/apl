#pragma once

#include <apl/tokenizer/Token.hpp>

struct BacktickTok : Token {
    BacktickTok(std::string raw, int spos, int epos, Token val)
        : Token(raw, spos, epos)
        , val(LineTok.inherit(val))
    {}

    std::string toRepr() const override {
        return "`" + val.toRepr();
    }

    LineTok value() const {
        return val;
    }
private:
    LineTok val;
};