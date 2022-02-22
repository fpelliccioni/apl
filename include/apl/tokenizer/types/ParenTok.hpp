#pragma once

#include <apl/tokenizer/Token.hpp>

struct ParenTok : TokArr<LineTok> {
    bool hasDmd;

    ParenTok(std::string line, int spos, int epos, std::vector<LineTok> tokens, bool hasDmd)
        : TokArr<LineTok>(line, spos, tokens)
        , hasDmd(hasDmd)
    {
        end(epos);
    }

    std::string toRepr() const override {
        std::string s = "(";
        bool tail = false;
        for (auto v : tokens) {
            if (tail) s.append(" ⋄ ");
            s.append(v.toRepr());
            tail = true;
        }
        s.append(")");
        return s;
    }
};
