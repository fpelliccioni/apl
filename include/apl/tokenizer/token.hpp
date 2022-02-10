#pragma once

#include <type_traits>
#include <variant>

#include <apl/tokenizer/token_fwd.hpp>
#include <apl/tokenizer/types/types.hpp>
#include <apl/tokenizer/types/types_def.hpp>

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
        if constexpr (std::is_same_v<T, types::backtick>)
            return "backtick";
        else if constexpr (std::is_same_v<T, types::basic_lines>)
            return "basic_lines";
        else if constexpr (std::is_same_v<T, types::bracket>)
            return "bracket";
        else if constexpr (std::is_same_v<T, types::colon>)
            return "colon";
        else if constexpr (std::is_same_v<T, types::dcolon>)
            return "dcolon";
        else if constexpr (std::is_same_v<T, types::diamond>)
            return "diamond";
        else if constexpr (std::is_same_v<T, types::dfn>)
            return "dfn";
        else if constexpr (std::is_same_v<T, types::err>)
            return "err";
        else if constexpr (std::is_same_v<T, types::line>)
            return "line";
        else if constexpr (std::is_same_v<T, types::name>)
            return "name";
        else if constexpr (std::is_same_v<T, types::paren>)
            return "paren";
        else if constexpr (std::is_same_v<T, types::op>)
            return "op";
        else if constexpr (std::is_same_v<T, types::scope>)
            return "scope";
        else if constexpr (std::is_same_v<T, types::semi>)
            return "semi";
        else if constexpr (std::is_same_v<T, types::set>)
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

        if constexpr (std::is_same_v<T, types::backtick>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, types::basic_lines>)
            return arg.to_tree(p);
        else if constexpr (std::is_same_v<T, types::bracket>)
            return arg.to_tree(p);
        else if constexpr (std::is_same_v<T, types::colon>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, types::dcolon>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, types::diamond>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, types::dfn>)
            return arg.to_tree(p);
        else if constexpr (std::is_same_v<T, types::err>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, types::line>)
            return arg.to_tree(p);
        else if constexpr (std::is_same_v<T, types::name>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, types::op>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, types::paren>)
            return arg.to_tree(p);
        else if constexpr (std::is_same_v<T, types::scope>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, types::semi>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, types::set>)
            return to_tree_base(x, p);
        else
            static_assert(always_false_v<T>, "non-exhaustive visitor!");

        // if constexpr (std::is_same_v<T, types::array>)
        //     return arg.to_tree(p);
        // else if constexpr (
        //         std::is_same_v<T, types::dcolon> ||
        //         std::is_same_v<T, types::diamond> ||
        //         std::is_same_v<T, types::err> ||
        //         std::is_same_v<T, types::name> ||
        //         std::is_same_v<T, types::op> ||
        //         std::is_same_v<T, types::scope> ||
        //         std::is_same_v<T, types::semi> ||
        //         std::is_same_v<T, types::set>)
        //     return to_tree_base(x, p);
        // else
        //     static_assert(always_false_v<T>, "non-exhaustive visitor!");
    }, x);
}
