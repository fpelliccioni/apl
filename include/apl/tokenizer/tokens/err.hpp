#pragma once

#include <string>
#include <string_view>

#include <apl/tokenizer/tokens/base.hpp>

namespace tokens {

struct err : base {
    err(std::string_view line, int spos, int epos)
        : base(line, spos, epos)
    {}

    err(std::string_view raw, int onepos)
        : base(raw, onepos, onepos + 1)
    {}

    std::string to_repr() const {
        return "";
        //TODO: retornaba null
        // return null;
    }
};

} // namespace tokens
