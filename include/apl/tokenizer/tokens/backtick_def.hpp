#pragma once

#include <apl/tokenizer/tokens/backtick.hpp>

namespace tokens {

backtick::backtick(std::string_view raw, int spos, int epos, token val)
    : base(raw, spos, epos)
    , val(line::inherit(val))
{}

std::string backtick::to_repr() const {
    return "`" + ::to_repr(val);
}

line backtick::value() const {
    return val;
}

} // namespace tokens
