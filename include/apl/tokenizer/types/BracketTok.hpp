#pragma once

#include <apl/tokenizer/Token.hpp>
#include <apl/tokenizer/types/LineTok.hpp
#include <apl/tokenizer/types/TokArr.hpp

struct BracketTok : TokArr<LineTok> {
    bool array;

    BracketTok(std::string line, int spos, int epos, std::vector<LineTok> tokens, bool hasDmd)
        : TokArr<LineTok>(line, spos, tokens)
        , array(tokens.size() >= 2 || hasDmd)
    {
        end(epos);
        if (tokens.size()==0 && hasDmd) {
            throw new DomainError("[⋄] is not valid syntax", this);
        }
    }

    std::string toRepr() const override {
        std::string s = "[";
        bool tail = false;
        for (auto v : tokens) {
            if (tail) s.append(" ⋄ ");
            s.append(v.toRepr());
            tail = true;
        }
        s.append("]");
        return s;
    }

    std::string toString() const {
        return "[...]";
    }
};
