#pragma once

#include <apl/tokenizer/Token.hpp>
#include <apl/tokenizer/types/LineTok.hpp
#include <apl/tokenizer/types/TokArr.hpp

struct BasicLines : TokArr<LineTok> {
    BasicLines(std::string line, int spos, int epos, std::vector<LineTok> tokens)
        : TokArr<LineTok>(line, spos, epos, tokens);
    {}

    std::string toRepr() const override {
        std::string s;
        bool tail = false;
        for (auto v : tokens) {
            if (tail) s.append("\n");
            s.append(v.toRepr());
            tail = true;
        }
        return s;
    }
};