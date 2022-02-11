#pragma once

#include <string>
#include <string_view>

#include <apl/tokenizer/tokens/base.hpp>

namespace tokens {

struct comment : base {
    comment(std::string_view raw, int spos, int epos)
        : base(raw, spos, epos)
    {}

    std::string to_repr() const {
        return "";
        //TODO: retornaba null
        // return null;
    }
};

} // namespace tokens
