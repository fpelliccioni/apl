#pragma once

#include <string>
#include <string_view>

#include <apl/tokenizer/tokens/base.hpp>

namespace tokens {

struct operator : base {
    std::string op;

    operator(std::string_view line, int spos, int epos, std::string op)
        : base(line, spos, epos)
        , op(op)
    {}

    std::string to_repr() const {
        return op;
    }
};

} // namespace tokens
