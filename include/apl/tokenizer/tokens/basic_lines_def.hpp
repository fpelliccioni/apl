#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <apl/tokenizer/tokens/basic_lines.hpp>

namespace tokens {

basic_lines::basic_lines(std::string_view l, int spos, int epos, std::vector<line> tokens)
    : array(l, spos, epos, tokens)
{}

std::string basic_lines::to_repr() const {
    std::string s;
    bool tail = false;
    for (auto v : tokens) {
        if (tail) s += '\n';
        s += ::to_repr(v);
        tail = true;
    }
    return s;
}

} // namespace tokens

