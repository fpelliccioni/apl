#pragma once

#include <string_view>
#include <variant>

#include <apl/tokenizer/types/types_fwd.hpp>

using token = std::variant<
    // types::array,
    types::backtick,
    types::basic_lines,
    // types::big,
    types::bracket,
    // types::chr,
    types::colon,
    // types::comment,
    types::dcolon,
    types::dfn,
    types::diamond,
    types::err,
    types::line,
    types::name,
    // types::num,
    types::op,
    types::paren,
    types::scope,
    types::semi,
    types::set
    // types::string
    >;

std::string_view raw(token x);
int spos(token x);
int epos(token x);
std::string to_tree(token x, std::string& p);
std::string to_repr(token x);
