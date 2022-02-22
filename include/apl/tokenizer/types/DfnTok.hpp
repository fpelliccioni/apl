#pragma once

#include <apl/tokenizer/Token.hpp>

struct DfnTok : TokArr<LineTok> {
    DfnTok(std::string line, int spos, int epos, std::vector<LineTok> tokens)
        : TokArr<LineTok>(line, spos, tokens)
    {
        end(epos);
    }

    std::string toRepr() const override {
        std::string s = "{";
        bool tail = false;
        for (auto v : tokens) {
            if (tail) s.append(" ⋄ ");
            s.append(v.toRepr());
            tail = true;
        }
        s.append("}");
        return s;
    }
};
