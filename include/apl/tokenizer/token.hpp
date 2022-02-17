#pragma once

#include <type_traits>
#include <variant>

#include <apl/tokenizer/token_fwd.hpp>
#include <apl/tokenizer/tokens/tokens.hpp>
#include <apl/tokenizer/tokens/tokens_def.hpp>

template<class> inline constexpr bool always_false_v = false;

std::string_view raw(token x) {
    return std::visit([](auto&& arg) {
        return arg.raw;
    }, x);
}

int spos(token x) {
    return std::visit([](auto&& arg) {
        return arg.spos;
    }, x);
}

int epos(token x) {
    return std::visit([](auto&& arg) {
        return arg.epos;
    }, x);
}

void end(token x, int i) {
    std::visit([i](auto&& arg) {
        arg.end(i);
    }, x);
}

// @Override public Token getToken() {
// return this;
// }

std::string to_repr(token x) {
    return std::visit([](auto&& arg) {
        return arg.to_repr();
    }, x);
}

auto source(token x) {
    return std::visit([](auto&& arg) {
        return arg.source();
    }, x);
}

auto class_name(token x) {
    return std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        // if constexpr (std::is_same_v<T, tokens::backtick>)
        //     return "backtick";
        if constexpr (std::is_same_v<T, tokens::basic_lines>)
            return "basic_lines";
        else if constexpr (std::is_same_v<T, tokens::bracket>)
            return "bracket";
        else if constexpr (std::is_same_v<T, tokens::colon>)
            return "colon";
        else if constexpr (std::is_same_v<T, tokens::dcolon>)
            return "dcolon";
        else if constexpr (std::is_same_v<T, tokens::diamond>)
            return "diamond";
        else if constexpr (std::is_same_v<T, tokens::dfn>)
            return "dfn";
        else if constexpr (std::is_same_v<T, tokens::err>)
            return "err";
        else if constexpr (std::is_same_v<T, tokens::line>)
            return "line";
        else if constexpr (std::is_same_v<T, tokens::name>)
            return "name";
        else if constexpr (std::is_same_v<T, tokens::num>)
            return "num";
        else if constexpr (std::is_same_v<T, tokens::paren>)
            return "paren";
        else if constexpr (std::is_same_v<T, tokens::op>)
            return "op";
        else if constexpr (std::is_same_v<T, tokens::scope>)
            return "scope";
        else if constexpr (std::is_same_v<T, tokens::semi>)
            return "semi";
        else if constexpr (std::is_same_v<T, tokens::set>)
            return "set";
        else
            static_assert(always_false_v<T>, "non-exhaustive visitor!");
    }, x);
}

// https://stackoverflow.com/questions/23999573/convert-a-number-to-a-string-literal-with-constexpr
std::string to_tree_base(token x, std::string& p) {
    // return p + this.getClass().getCanonicalName() + ' '+ spos + '-' + epos + '\n';
    p += "  ";
    std::string r = p;
    r += class_name(x);
    r += ' ';
    r += std::to_string(spos(x));
    r += '-';
    r += std::to_string(epos(x));
    r += '\n';

    return r;
}

std::string to_tree(token x, std::string& p) {
    return std::visit([&](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;

        // if constexpr (std::is_same_v<T, tokens::backtick>)
        //     return to_tree_base(x, p);
        if constexpr (std::is_same_v<T, tokens::basic_lines>)
            return arg.to_tree(p);
        else if constexpr (std::is_same_v<T, tokens::bracket>)
            return arg.to_tree(p);
        else if constexpr (std::is_same_v<T, tokens::colon>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, tokens::dcolon>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, tokens::diamond>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, tokens::dfn>)
            return arg.to_tree(p);
        else if constexpr (std::is_same_v<T, tokens::err>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, tokens::line>)
            return arg.to_tree(p);
        else if constexpr (std::is_same_v<T, tokens::name>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, tokens::num>)
            return arg.to_tree(p);
        else if constexpr (std::is_same_v<T, tokens::op>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, tokens::paren>)
            return arg.to_tree(p);
        else if constexpr (std::is_same_v<T, tokens::scope>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, tokens::semi>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, tokens::set>)
            return to_tree_base(x, p);
        else
            static_assert(always_false_v<T>, "non-exhaustive visitor!");

        // if constexpr (std::is_same_v<T, tokens::array>)
        //     return arg.to_tree(p);
        // else if constexpr (
        //         std::is_same_v<T, tokens::dcolon> ||
        //         std::is_same_v<T, tokens::diamond> ||
        //         std::is_same_v<T, tokens::err> ||
        //         std::is_same_v<T, tokens::name> ||
        //         std::is_same_v<T, tokens::op> ||
        //         std::is_same_v<T, tokens::scope> ||
        //         std::is_same_v<T, tokens::semi> ||
        //         std::is_same_v<T, tokens::set>)
        //     return to_tree_base(x, p);
        // else
        //     static_assert(always_false_v<T>, "non-exhaustive visitor!");
    }, x);
}
