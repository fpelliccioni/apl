#pragma once

// #include <format>
#include <string_view>
#include <vector>

#include <apl/tokenizer/tokens/base.hpp>

namespace tokens {

template <typename T>   //T extends Token
struct array : base {
    std::vector<T> tokens;

    array(std::string_view line, int pos, std::vector<T> tokens)
        : base(line, pos)
        , tokens(tokens)
    {}

    array(std::string_view line, int spos, int epos, std::vector<T> tokens)
        : base(line, spos, epos)
        , tokens(tokens)
    {}

    std::string to_tree_internal(std::string& p, std::string_view class_name) const;
};

} // namespace tokens
