#pragma once

#include <string>
#include <string_view>

#include <apl/tokenizer/types/line.hpp>
#include <apl/tokenizer/types/base.hpp>

namespace types {

struct backtick : base {
    backtick(std::string_view raw, int spos, int epos, token val);
    std::string to_repr() const;
    line value() const;
private:
    line val;
};

} // namespace types
