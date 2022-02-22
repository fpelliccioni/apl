#pragma once

#include <string>
#include <vector>

#include <apl/tokenizer/Token.hpp>
#include <apl/tokenizer/types/TokArr.hpp

struct LineTok : TokArr<Token> {
    LineTok(std::string raw, int spos, int epos, std::vector<Token> tokens)
        : TokArr<Token>(raw, spos, epos, tokens)
    {}

    static
    LineTok inherit(std::vector<Token> tokens) {
        Token fst = tokens.get(0);
        return new LineTok(fst.raw, fst.spos, tokens.get(tokens.size()-1).epos, tokens);
    }

    static
    LineTok inherit(Token tk) {
        std::vector<Token> a = new std::vector<>();
        a.add(tk);
        return new LineTok(tk.raw, tk.spos, tk.epos, a);
    }

    int colonPos() {
        if (colonPos == null) {
            colonPos = -1;
            for (int i = 0; i < tokens.size(); i++) {
                if (tokens.get(i) instanceof ColonTok) {
                    colonPos = i;
                    break;
                }
            }
        }
        return colonPos;
    }

    int eguardPos() {
        if (eguardPos == null) {
            eguardPos = -1;
            for (int i = 0; i < tokens.size(); i++) {
                if (tokens.get(i) instanceof DColonTok) {
                    eguardPos = i;
                    break;
                }
            }
        }
        return eguardPos;
    }

    std::string toRepr() const override {
        StringBuilder s = new StringBuilder();
        bool tail = false;
        for (auto v : tokens) {
            if (tail) s.append(" ");
            s.append(v.toRepr());
            tail = true;
        }
        return s.toString();
    }

private:
    Integer colonPos;
    Integer eguardPos;
};