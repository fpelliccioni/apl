#pragma once

#include <string>
#include <string_view>

#include <apl/tokenizer/tokens/base.hpp>

namespace tokens {

struct colon : base {
  colon(std::string_view line, int spos, int epos)
    : base(line, spos, epos)
  {}

  std::string to_repr() const {
    return ":";
  }
};


} // namespace tokens