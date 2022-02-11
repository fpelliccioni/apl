#pragma once

#include <string>
#include <string_view>

#include <apl/tokenizer/tokens/base.hpp>

namespace tokens {

struct diamond : base {
    diamond(std::string_view raw, int pos)
        : base(raw, pos, pos + 1)
    {}

    std::string to_repr() const {
        return "";
        //TODO: retornaba null
        // return null;
    }
};

} // namespace tokens

