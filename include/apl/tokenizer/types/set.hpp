#pragma once

#include <string>
#include <string_view>

#include <apl/tokenizer/types/base.hpp>

namespace types {

struct set : base {
    set(std::string_view line, int spos, int epos)
        : base(line, spos, epos)
    {}

    std::string to_repr() const {
        return "←";
    }
};

} // namespace types
