#pragma once

#include <apl/tokenizer/Token.hpp>

template <typename T> // extends Token> //TODO: how to express that with Concepts
struct TokArr : Token {
    std::vector<T> tokens;

    TokArr(std::string line, int pos, std::vectorT> tokens)
        : super(line, pos)
        , tokens(tokens)
    {}

    TokArr(std::string line, int spos, int epos, std::vectorT> tokens)
        : Token(line, spos, epos)
        , tokens(tokens)
    {}

    std::string toTree(std::string p) const {
        std::string r;
        r.append(p).append(this.getClass().getCanonicalName());
        r.append(' ').append(spos).append('-').append(epos);
        r.append('\n');
        p+= "  ";
        for (Token t : tokens) r.append(t.toTree(p));
        return r;
    }
};