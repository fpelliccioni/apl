#pragma once

#include <optional>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>

namespace tokens {

template <typename T>   //T extends Token
class array;

class colon;
class dcolon;
class line;

} // namespace tokens


// -----------------------------------------------------------------
using token = std::variant<
    tokens::colon,
    tokens::dcolon,
    tokens::line
    >;

// -----------------------------------------------------------------

std::string_view raw(token x);
int spos(token x);
int epos(token x);
std::string to_tree(token x, std::string& p);
std::string to_repr(token x);

// -----------------------------------------------------------------




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

namespace tokens {

struct dcolon : base {
  dcolon(std::string_view line, int spos, int epos)
    : base(line, spos, epos)
  {}

  std::string to_repr() const {
    return "::";
  }
};

} // namespace tokens

// -----------------------------------------------------------------

namespace tokens {

template <typename T>   //T extends Token
struct array : base {
    std::vector<T> tokens;

    array(std::string_view line, int pos, std::vector<T> tokens)
        : base(line, pos)
        , tokens(tokens)
    {}

    array(std::string_view line, int spos, int epos, std::vector<T> tokens)
        : base(line, spos, epos)
        , tokens(tokens)
    {}

    std::string to_tree_internal(std::string& p, std::string_view class_name) const;
};

} // namespace tokens

// -----------------------------------------------------------------

namespace tokens {

struct line : array<token> {
    line(std::string_view raw, int spos, int epos, std::vector<token> tokens);

    static
    line inherit(std::vector<token> tokens);

    static
    line inherit(token tk);

    std::string to_tree(std::string& p) const;

    int colonPos();
    int eguardPos();
    std::string to_repr() const;

private:
    std::optional<int> colonPos_;
    std::optional<int> eguardPos_;
};

} // namespace tokens



namespace tokens {

template <typename T>
std::string array<T>::to_tree_internal(std::string& p, std::string_view class_name) const {
    // class_name: this.getClass().getCanonicalName()
    // auto r = std::format("{}{} {}-{}\n", p, class_name, spos, epos);
    std::string r = p;
    r.append(class_name);
    r += " " + std::to_string(spos) + "-" + std::to_string(epos) + '\n';

    p += "  ";
    for (auto t : tokens) {
        r += to_tree(t, p);
    }
    return r;
}

} // namespace tokens




namespace tokens {

line::line(std::string_view raw, int spos, int epos, std::vector<token> tokens)
    : array(raw, spos, epos, tokens)
{}

// static
line inherit(std::vector<token> tokens) {
    auto fst = tokens.at(0);
    return line(raw(fst), spos(fst), epos(tokens.at(tokens.size()-1)), tokens);
}

// static
line inherit(token tk) {
    return line(raw(tk), spos(tk), epos(tk), std::vector<token> { tk });
}

std::string line::to_tree(std::string& p) const {
    return array::to_tree_internal(p, "line");
}

// int line::colonPos() {
//     if (colonPos_) {
//       return *colonPos_;
//     }
//     colonPos_ = -1;
//     for (int i = 0; i < tokens.size(); ++i) {
//         if (std::holds_alternative<colon>(tokens.at(i))) {
//             colonPos_ = i;
//             break;
//         }
//     }
// }

// int line::eguardPos() {
//   if (eguardPos_) {
//       return *eguardPos_;
//   }

//   eguardPos_ = -1;
//   for (int i = 0; i < tokens.size(); ++i) {
//       if (std::holds_alternative<dcolon>(tokens.at(i))) {
//           eguardPos_ = i;
//           break;
//       }
//   }
// }

std::string line::to_repr() const {
    std::string s;
    bool tail = false;
    for (auto v : tokens) {
        if (tail) s += " ";
        s += ::to_repr(v);
        tail = true;
    }
    return s;
}

} // namespace tokens

// -----------------------------------------------------------------


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
        if constexpr (std::is_same_v<T, tokens::colon>)
            return "colon";
        else if constexpr (std::is_same_v<T, tokens::dcolon>)
            return "dcolon";
        else if constexpr (std::is_same_v<T, tokens::line>)
            return "line";
        // else if constexpr (std::is_same_v<T, tokens::diamond>)
        //     return "diamond";
        // else if constexpr (std::is_same_v<T, tokens::err>)
        //     return "err";
        // else if constexpr (std::is_same_v<T, tokens::name>)
        //     return "name";
        // else if constexpr (std::is_same_v<T, tokens::op>)
        //     return "op";
        // else if constexpr (std::is_same_v<T, tokens::scope>)
        //     return "scope";
        // else if constexpr (std::is_same_v<T, tokens::semi>)
        //     return "semi";
        // else if constexpr (std::is_same_v<T, tokens::set>)
        //     return "set";
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

        if constexpr (std::is_same_v<T, tokens::colon>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, tokens::dcolon>)
            return to_tree_base(x, p);
        else if constexpr (std::is_same_v<T, tokens::line>)
            return arg.to_tree(p);
        // else if constexpr (std::is_same_v<T, tokens::diamond>)
        //     return to_tree_base(x, p);
        // else if constexpr (std::is_same_v<T, tokens::err>)
        //     return to_tree_base(x, p);
        // else if constexpr (std::is_same_v<T, tokens::name>)
        //     return to_tree_base(x, p);
        // else if constexpr (std::is_same_v<T, tokens::op>)
        //     return to_tree_base(x, p);
        // else if constexpr (std::is_same_v<T, tokens::scope>)
        //     return to_tree_base(x, p);
        // else if constexpr (std::is_same_v<T, tokens::semi>)
        //     return to_tree_base(x, p);
        // else if constexpr (std::is_same_v<T, tokens::set>)
        //     return to_tree_base(x, p);
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
