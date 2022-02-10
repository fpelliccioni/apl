#pragma once

#include <string>
#include <string_view>

#include <apl/tokenizer/types/base.hpp>

namespace types {

struct op : base {
    std::string value;

    op(std::string_view line, int spos, int epos, std::string value)
        : base(line, spos, epos)
        , value(value)
    {}

    std::string to_repr() const {
        return value;
    }
};

} // namespace types
