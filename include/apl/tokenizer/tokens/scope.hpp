#pragma once

#include <string>
#include <string_view>

#include <apl/tokenizer/tokens/base.hpp>

namespace tokens {

struct scope : base {
    scope(std::string_view line, int spos, int epos)
        : base(line, spos, epos)
    {}

    std::string to_repr() const {
        return "#";
    }
};

} // namespace tokens
