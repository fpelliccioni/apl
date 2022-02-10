#pragma once

#include <string>
#include <string_view>

#include <apl/tokenizer/types/base.hpp>

namespace types {

struct name : base {
    std::string value;

    name(std::string_view line, int spos, int epos, std::string value)
        : base(line, spos, epos)
        , value(value)
    {}

    std::string to_tree(std::string p) {
        return p + "name: " + value + "\n";
    }

    std::string to_repr() const {
        return value;
    }
};

} // namespace types