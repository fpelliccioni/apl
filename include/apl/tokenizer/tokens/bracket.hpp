#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <apl/tokenizer/tokens/line.hpp>
#include <apl/tokenizer/tokens/array.hpp>
#include <apl/tokenizer/tokens/base.hpp>

namespace tokens {

struct bracket : array<line> {
    bracket(std::string_view l, int spos, int epos, std::vector<line> tokens, bool hasDmd);

    std::string to_repr() const;

    std::string to_string() const {
        return "[...]";
    }

    std::string to_tree(std::string& p) const {
        return array::to_tree_internal(p, "bracket");
    }

    bool is_array;
};

} // namespace tokens
