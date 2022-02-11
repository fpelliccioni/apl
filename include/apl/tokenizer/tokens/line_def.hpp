#pragma once

#include <apl/tokenizer/tokens/line.hpp>

namespace tokens {

line::line(std::string_view raw, int spos, int epos, std::vector<token> tokens)
    : array(raw, spos, epos, tokens)
{}

// static
line inherit(std::vector<token> tokens) {
    auto fst = tokens.at(0);
    return line(raw(fst), spos(fst), epos(tokens.at(tokens.size()-1)), tokens);
}

// static
line inherit(token tk) {
    return line(raw(tk), spos(tk), epos(tk), std::vector<token> { tk });
}

int line::colonPos() {
    if (colonPos_) return *colonPos_;

    colonPos_ = -1;
    for (int i = 0; i < tokens.size(); ++i) {
        if (std::holds_alternative<colon>(tokens.at(i))) {
            colonPos_ = i;
            break;
        }
    }
    return *colonPos_;
}

int line::eguardPos() {
  if (eguardPos_) return *eguardPos_;

    eguardPos_ = -1;
    for (int i = 0; i < tokens.size(); ++i) {
        if (std::holds_alternative<dcolon>(tokens.at(i))) {
            eguardPos_ = i;
            break;
        }
    }
    return *eguardPos_;
}

std::string line::to_repr() const {
    std::string s;
    bool tail = false;
    for (auto v : tokens) {
        if (tail) s += " ";
        s += ::to_repr(v);
        tail = true;
    }
    return s;
}

std::string line::to_tree(std::string& p) const {
    return array::to_tree_internal(p, "line");
}

} // namespace tokens