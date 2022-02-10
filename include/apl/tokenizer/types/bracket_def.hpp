#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <apl/tokenizer/types/bracket.hpp>

namespace types {

bracket::bracket(std::string_view l, int spos, int epos, std::vector<line> tokens, bool hasDmd)
    : array(l, spos, tokens)
{
    is_array = tokens.size() >= 2 || hasDmd;
    end(epos);

    if (tokens.size()==0 && hasDmd) {
        //TODO:
        // throw new DomainError("[⋄] is not valid syntax", this);
        throw "[⋄] is not valid syntax";
    }
}

std::string bracket::to_repr() const {
    std::string s = "[";
    bool tail = false;
    for (auto v : tokens) {
        if (tail) s += " ⋄ ";
        s += ::to_repr(v);
        tail = true;
    }
    s += "]";
    return s;
}

} // namespace types
