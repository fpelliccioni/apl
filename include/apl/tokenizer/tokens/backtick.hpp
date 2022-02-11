#pragma once

#include <string>
#include <string_view>

#include <apl/tokenizer/tokens/line.hpp>
#include <apl/tokenizer/tokens/base.hpp>

namespace tokens {

struct backtick : base {
    backtick(std::string_view raw, int spos, int epos, token val);
    std::string to_repr() const;
    line value() const;
private:
    line val;
};

} // namespace tokens
