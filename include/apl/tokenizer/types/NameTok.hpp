#pragma once

#include <apl/tokenizer/Token.hpp>

struct NameTok : Token {
    std::string name;

    NameTok(std::string line, int spos, int epos, std::string name)
      : Token(line, spos, epos)
      , name(name)
    {}

    std::string toTree(std::string p) const override {
        return p+"name: " + name + "\n";
    }

    std::string toRepr() const override {
        return name;
    }
};
