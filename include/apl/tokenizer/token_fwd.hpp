#pragma once

#include <string_view>
#include <variant>

#include <apl/tokenizer/tokens/tokens_fwd.hpp>

using token = std::variant<
    // tokens::array,
    // tokens::backtick,
    tokens::basic_lines,
    // tokens::big,
    tokens::bracket,
    // tokens::chr,
    tokens::colon,
    // tokens::comment,
    tokens::dcolon,
    tokens::dfn,
    tokens::diamond,
    tokens::err,
    tokens::line,
    tokens::name,
    tokens::num,
    tokens::op,
    tokens::paren,
    tokens::scope,
    tokens::semi,
    tokens::set
    // tokens::string
    >;

std::string_view raw(token x);
int spos(token x);
int epos(token x);
std::string to_tree(token x, std::string& p);
std::string to_repr(token x);
