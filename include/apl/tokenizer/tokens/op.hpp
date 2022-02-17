#pragma once

#include <string>
#include <string_view>

#include <apl/tokenizer/tokens/base.hpp>

namespace tokens {

struct op : base {
    std::string op_;

    op(std::string_view line, int spos, int epos, std::string op)
        : base(line, spos, epos)
        , op_(op)
    {}

    std::string to_repr() const {
        return op_;
    }
};

} // namespace tokens
