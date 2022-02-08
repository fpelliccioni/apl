// https://aplwiki.com/wiki/Category:Primitive_functions
// https://aplwiki.com/wiki/Category:Operators

// ⊃        first
// =        equal
// ∧        and
// ⊢        same
// /        reduce

#include <algorithm>
#include <array>
#include <iterator>
#include <iostream>
#include <optional>
#include <ranges>
#include <string_view>
#include <variant>
#include <vector>

#include <views.hpp>


template <size_t N>
struct string_literal {
    char value[N];

    constexpr string_literal(char const (&str)[N]) {
        std::copy_n(str, N, value);
    }

    constexpr size_t size() const {
        return N;
    }

    constexpr char const* begin() const {
        return value;
    }

    constexpr char const* end() const {
        return value + N;
    }
};

// constexpr string_literal first_str("⊃");
// constexpr string_literal equal_str("=");
// constexpr string_literal _and_str("∧");
// constexpr string_literal same_str("⊢");
// constexpr string_literal reduce_str("/");

constexpr std::string_view first_str("⊃");
constexpr std::string_view equal_str("=");
constexpr std::string_view _and_str("∧");
constexpr std::string_view same_str("⊢");
constexpr std::string_view reduce_str("/");

template <string_literal lit>
void print_lit() {
    constexpr auto size = sizeof(lit.value);
    constexpr auto contents = lit.value;
    std::cout << "Size: " << size << ", Contents: " << contents << std::endl;
}

template <string_literal lit>
void print_int() {
    for (char c : lit) {
        std::cout << (int) (unsigned char)c << '|';
    }
    std::cout << std::endl;
}

constexpr
bool is_equal(auto const& x, auto const& y) {
    return std::equal(std::begin(x), std::end(x), std::begin(y), std::end(y));
}

enum class token_t {
    integer,
    real,

    plus,
    minus,
    times,
    divide,
    negate,

    first,
    equal,
    _and,
    same,
    reduce, //TODO?

    commute,
    lparens,
    rparens,
    eof
};

constexpr
bool is_monadic_op(token_t x) {
    switch (x) {
        case token_t::commute:
            return true;
        default:
            break;
    }
    return false;
}

constexpr
bool is_function(token_t x) {
    switch (x) {
        case token_t::plus:
        case token_t::minus:
        case token_t::times:
        case token_t::divide:
            return true;
        default:
            break;
    }
    return false;
}

template <string_literal str>
struct tokenizer {
    size_t index_ = 0;

    constexpr
    std::optional<token_t> next() {
        auto view = std::string_view(str.value);
        while (index_ < str.size()) {
            char c = str.value[index_];
            // std::cout << "c: " << c << std::endl;
            // std::cout << "index_: " << index_ << std::endl;
            switch (c) {
                case ' ': case '\t': case '\n':
                    break;
                case '/':
                    ++index_;
                    return token_t::reduce;
                case '=':
                    ++index_;
                    return token_t::equal;
                case char(226): {
                    if (index_ + 1 < str.size() && str.value[index_ + 1] == char(138)) {
                        if (index_ + 2 < str.size() && str.value[index_ + 2] == char(131)) {
                            // return view.substr(index_++, 3);
                            index_ += 3;
                            return token_t::first;
                        }
                        if (index_ + 2 < str.size() && str.value[index_ + 2] == char(162)) {
                            // return view.substr(index_++, 3);
                            index_ += 3;
                            return token_t::_and;
                        }
                    } else if (index_ + 1 < str.size() && str.value[index_ + 1] == char(136)) {
                        if (index_ + 2 < str.size() && str.value[index_ + 2] == char(167)) {
                            // return view.substr(index_++, 3);
                            index_ += 3;
                            return token_t::same;
                        }
                    }
                }
                default:
                    break;
            }
            ++index_;
        }
        return {};
    }
};

std::string_view token_str(token_t token) {
    switch (token) {
        case token_t::reduce:
            return reduce_str;
        case token_t::equal:
            return equal_str;
        case token_t::first:
            return first_str;
        case token_t::_and:
            return _and_str;
        case token_t::same:
            return same_str;
        // default:
        //     break;
    }
    return {};
}

template <typename T>
struct static_vector {
    using data_t = std::array<T, 256>;
    data_t data = {};
    size_t size_ = 0;

    constexpr static_vector() = default;

    constexpr void push_back(T x) {
        data[size_] = x;
        ++size_;
    }

    constexpr size_t size() const {
        return size_;
    }

    constexpr auto begin() const {
        return data.begin();
    }
    constexpr auto end() const {
        return data.begin() + size();
    }

    constexpr T& operator[](size_t pos) {
        return data[pos];
    }
};

using token_list_t = static_vector<token_t>;

template <string_literal str>
constexpr
token_list_t tokenize() {
    tokenizer<str> tz;
    token_list_t ret{};
    while (auto token = tz.next()) {
        ret.push_back(*token);
    }
    ret.push_back(token_t::eof);
    return ret;
}


// enum class type_t {
//     symbol,
// };

// struct value {
//     type_t type;
//     std::string_view str;

//     constexpr value() = default;
//     constexpr value(type_t type, std::string_view str)
//         : type(type), str(str)
//     {}
// };

// template <typename R>
// constexpr
// std::optional<value> read_form(R reader) {
//     auto token = reader.peek();

//     if ( ! token) {
//         return {};
//     }

//     return read_atom(reader);
// }

// template <typename R>
// constexpr
// std::optional<value> read_atom(R reader) {
//     return value{type_t::symbol, *reader.next() };
//     // return value{};
// }

// template <string_literal str>
// constexpr
// std::optional<value> read_str() {
//     auto tokens = tokenize<str>();
//     reader r(tokens);
//     return read_form(r);
// }





// template <string_literal str>
// auto apl() {
//     if (is_equal(str, first)) return first_algo;
// }

struct monadic_op;
struct monadic_fun;
struct dyadic_fun;

using ast_node_t = std::variant<monadic_op, monadic_fun, dyadic_fun>;

struct monadic_op {
    constexpr monadic_op(token_t token, token_t child)
        : token_(token), child(child)
    {}

    token_t token_;
    token_t child;
};

struct monadic_fun {
    constexpr monadic_fun(token_t token, token_t child)
        : token_(token), child(child)
    {}

    token_t token_;
    token_t child;
};

struct dyadic_fun {
    constexpr dyadic_fun(token_t token, token_t left, token_t right)
        : token_(token), left(left), right(right)
    {}

    token_t token_;
    token_t left;
    token_t right;
};


template <string_literal str>
struct parser {
    constexpr parser(bool debug = false) {
        tokens = tokenize(str);
        std::reverse(std::begin(tokens), std::end(tokens));
        pos = std::size(tokens) - 1;
        token_at = tokens[pos];
        debug_on = debug;
    }

    constexpr void debug(std::string const& message) {
        if (debug_on) {
            std::cout << "PD @ " << message << '\n';
        }
    }

    // // constexpr void error(std::string const& message) {
    // constexpr void error() {
    //     // std::string error = "Parser: " + message;
    //     // throw std::exception(error);
    //     // throw error;
    //     throw "Parser error";
    // }

    constexpr bool eat(token_t token_type) {
        // """Checks if the current token matches the expected token type."""

        if (token_at != token_type) {
            return false;
            // std::string error_msg = "Expected " + token_str(token_type) " and got " + token_str(token_at) + "."
            // error(msg);
            // error(f"Expected {token_type} and got {token_at.type}.");
        }
        --pos;
        if (pos < 0) {
            token_at = std::nullopt;
        } else {
            token_at = tokens[pos];
        }
        // token_at = None if pos < 0 else tokens[pos]
        return true;
    }

    constexpr std::optional<token_t> peek() const {
        // """Returns the next token type without consuming it."""
        auto peek_at = pos - 1;
        // return None if peek_at < 0 else tokens[peek_at].type
        if (peek_at < 0) {
            return {};
        }
        return tokens[peek_at];
    }

    constexpr void parse_program() {
        // debug(f"Parsing program from {tokens}")
        node = parse_statement();
        eat(token_t::eof);
        return node;
    }

    constexpr ast_node_t parse_statement() {
        // debug(f"Parsing statement from {tokens[:pos+1]}")
        auto node = parse_array();

        while (is_function(token_at) || is_monadic_op(token_at)) {
            auto [func, base] = parse_function();

            if (std::holds_alternative<dyadic_fun>(base)) {
                base.right = node;
                base.left = parse_array();
            } else if (std::holds_alternative<monadic_fun>(base)) {
                base.child = node;
            } else {
                error();
            }
            node = func;
        }
        return node;

    constexpr def parse_array() {
        // """Parses an array composed of possibly several simple scalars."""
        // debug(f"Parsing array from {tokens[:pos+1]}")

        static_vector<ast_node_t> nodes;

        // in [Token.RPARENS, Token.INTEGER, Token.FLOAT]:
        while (token_at == token_t::rparens || token_at == token_t::integer || token_at == token_t::real) {
            if (token_at == token_t::rparens) {
                eat(token_t::rparens);
                nodes.append(parse_statement());
                eat(token_t::lparens);
            } else {
                nodes.append(parse_scalar());
            }
        }
        nodes = nodes[::-1];

        if (not nodes) {
            error("Failed to parse scalars inside an array.")
        } else if (len(nodes) == 1) {
            node = nodes[0]
        } else {
            node = Array(nodes);
        }
        return node;
    }

    // def parse_scalar() {
    //     """Parses a simple scalar."""

    //     debug(f"Parsing scalar from {tokens[:pos+1]}")
    //     if token_at.type == Token.INTEGER:
    //         node = Scalar(token_at)
    //         eat(Token.INTEGER)
    //     else:
    //         node = Scalar(token_at)
    //         eat(Token.FLOAT)
    //     return node

    constexpr std::pair<ast_node_t, ast_node_t> parse_function() {
        // """Parses a function possibly monadically operated upon."""
        // debug(f"Parsing function from {tokens[:pos+1]}")

        // if token_at.type in Token.MONADIC_OPS {
        //     node = MOp(token_at, None)
        //     eat(token_at.type)
        //     node.child, base = parse_function()
        // } else {
        //     base = node = parse_f()
        // }

        if (is_monadic_op(token_at)) {
            auto tmp = token_at;
            eat(token_at);
            auto base = parse_function();
            auto node = monadic_op(token_at, base);
            return {node, base};
        }
        auto node = parse_f();
        return {node, node};
    }

    constexpr ast_node_t parse_f() {
        // """Parses a simple one-character function.
        // We have to peek forward to decide if the function is monadic or dyadic.
        // """
        // debug(f"Parsing f from {tokens[:pos+1]}")

        if peek() in [token_t::rparens, Token.INTEGER, Token.FLOAT] {
            node = Dyad(token_at, None, None)
        } else {
            node = Monad(token_at, None)
        }
        eat(node.token)
        return node

    void parse() {
        return parse_program();
    }

    token_list_t tokens;
    int pos;
    std::optional<token_t> token_at;
    bool debug_on;
};


int main() {
    // print<"literal string">(); // Prints "Size: 15, Contents: literal string"
    // print<"∧/⊃=⊢">();
    // apl<"∧">();
    // apl<"/">();
    // apl<"⊃">();
    // apl<"=">();
    // apl<"⊢">();

    // print_int<"∧">();
    // print_int<"/">();
    // print_int<"⊃">();
    // print_int<"=">();
    // print_int<"⊢">();

    // print_int<"∧/⊃=⊢">();

    // tokenizer<"∧/⊃=⊢"> tz;
    // while (auto token = tz.next()) {
    //     std::cout << '[' << token_str(*token) << ']' << '\n';
    // }


    constexpr auto tokens = tokenize<"∧/⊃=⊢">();
    static_assert(tokens.size() == 5);
    for (auto t : tokens) {
        std::cout << token_str(t) << ',';
    }
    std::cout << std::endl;


    // auto xxx = read_str<"∧/⊃=⊢">();




    // auto f = apl<"⊃">();
    // std::vector v {1, 2, 3, 4};
    // std::cout << f(begin(v), end(v));


}


// auto print = [](auto x) { std::cout << x; };



// int main() {
//     // print<"literal string">(); // Prints "Size: 15, Contents: literal string"
//     // print<"∧/⊃=⊢">();
//     // apl<"∧">();
//     // apl<"/">();
//     // apl<"⊃">();
//     // apl<"=">();
//     // apl<"⊢">();

//     // print_int<"∧">();
//     // print_int<"/">();
//     // print_int<"⊃">();
//     // print_int<"=">();
//     // print_int<"⊢">();

//     // print_int<"∧/⊃=⊢">();

//     // tokenizer<"∧/⊃=⊢"> tz;
//     // while (auto token = tz.next()) {
//     //     std::cout << '[' << *token << ']' << '\n';
//     // }


//     // auto tokens = tokenize<"∧/⊃=⊢">();

//     // auto f = apl<"⊃">();
//     // std::vector v {1, 2, 3, 4};
//     // std::cout << f(begin(v), end(v));






//     // std::vector v {1, 2, 3, 4};
//     // for (auto x : identity_view{v}) {
//     //     std::cout << x << ", ";
//     // }
//     // std::cout << '\n';





//     // std::vector v {1, 2, 3, 4};

//     // {
//     //     auto f = first_iterator{std::cbegin(v)};
//     //     auto const l = first_iterator{std::cend(v)};
//     //     while (f != l) {
//     //         std::cout << *f << ", ";
//     //         ++f;
//     //     }
//     //     std::cout << "\n";
//     // }
//     // {
//     //     auto f = std::cbegin(v);
//     //     auto const l = std::cend(v);
//     //     while (f != l) {
//     //         std::cout << *f << ", ";
//     //         ++f;
//     //     }
//     //     std::cout << "\n";
//     // }


//     // for (auto x : identity_view{v}) {
//     //     std::cout << x << ", ";
//     // }
//     // std::cout << '\n';


//     // std::cout << "---------- first_view -----------\n";
//     // for (auto x : first_view{v}) {
//     //     std::cout << x << ", ";
//     // }
//     // std::cout << '\n';



//     // std::vector v1 {1, 2, 3, 4};
//     // // std::vector v2 {1, 2, 3, 4};
//     // // std::vector v2 {4, 3, 2, 1};
//     // // std::vector v2 {1, 2, 3};
//     // // std::vector v2 {1, 2};
//     // // std::vector v2 {1};
//     // // std::vector<int> v2;
//     // // std::vector v2 {1, 2, 3, 4, 5};
//     // // std::vector v2 {1, 2, 3, 4, 5, 6};
//     // // std::vector v2 {3, 4};
//     // std::vector v2 {3, 4, 3};
//     // auto f = equal_iterator{std::cbegin(v1), std::cend(v1), std::cbegin(v2), std::cend(v2)};
//     // f += 2;
//     // auto const l = equal_iterator{std::cend(v1), std::cend(v1), std::cend(v2), std::cend(v2)};
//     // while (f != l) {
//     //     std::cout << *f << ", ";
//     //     ++f;
//     // }






//     // std::vector v {1, 2, 3, 4};
//     // // std::vector v2 {1, 2, 3, 4};
//     // // std::vector v2 {1, 2};
//     // std::vector v2 {1, 2, 3, 4, 5, 6};
//     // for (auto x : equal_view{v, v2}) {
//     //     std::cout << x << ", ";
//     // }
//     // std::cout << '\n';






//     // std::vector v {1, 2, 3, 4};
//     std::vector v {1, 1, 1, 1};
//     auto comp = equal_view{first_view{v}, identity_view{v}};
//     // auto comp = equal_view{first_view{v}, v};
//     for (auto x : comp) {
//         std::cout << x << ", ";
//     }
//     std::cout << '\n';


//     // std::vector v {1, 2, 3, 4};

//     // // identity_view vi{v};
//     // first_view vi{v};
//     // // std::ranges::take_view vi{v, 1};

//     // // auto xxx = std::ranges::begin(vi);
//     // // auto yyy = std::ranges::end(vi);
//     // using view_t = decltype(vi);
//     // static_assert(std::ranges::view<view_t>);
//     // static_assert(std::ranges::range<view_t>);




//     // std::vector v {1, 2, 3, 4};
//     // auto it = first_iterator{std::cbegin(v)};
//     // it = first_iterator{std::cbegin(v)};
//     // // auto it = std::cbegin(v);
//     // using it_t = decltype(it);
//     // static_assert(std::input_or_output_iterator<it_t>);
//     // static_assert(std::weakly_incrementable<it_t>);
//     // static_assert(std::movable<it_t>);
//     // // static_assert(std::sentinel_for<std::iter_value_t<it_t>, it_t>);
//     // static_assert(std::sentinel_for<it_t, it_t>);



//     // std::vector v {1, 2, 3, 4};
//     // auto it = equal_iterator{std::cbegin(v), std::cend(v), std::cbegin(v), std::cend(v)};
//     // // auto it = first_iterator{std::cbegin(v)};
//     // it = equal_iterator{std::cbegin(v), std::cend(v), std::cbegin(v), std::cend(v)};
//     // // auto it = std::cbegin(v);
//     // using it_t = decltype(it);
//     // static_assert(std::input_or_output_iterator<it_t>);
//     // static_assert(std::weakly_incrementable<it_t>);
//     // static_assert(std::movable<it_t>);
//     // // static_assert(std::sentinel_for<std::iter_value_t<it_t>, it_t>);
//     // static_assert(std::sentinel_for<it_t, it_t>);


// }






// template <string_literal str>
// struct tokenizer {
//     size_t index_ = 0;

//     constexpr
//     std::optional<std::string_view> next() {
//         auto view = std::string_view(str.value);
//         while (index_ < str.size()) {
//             char c = str.value[index_];
//             switch (c) {
//                 case ' ': case '\t': case '\n':
//                     break;
//                 case '/':
//                 case '=':
//                     return view.substr(index_++, 1);
//                 case char(226): {
//                     if (index_ + 1 < str.size() && str.value[index_ + 1] == char(138)) {
//                         if (index_ + 2 < str.size() && str.value[index_ + 2] == char(131)) {
//                             return view.substr(index_++, 3);
//                         }
//                         if (index_ + 2 < str.size() && str.value[index_ + 2] == char(162)) {
//                             return view.substr(index_++, 3);
//                         }
//                     } else if (index_ + 1 < str.size() && str.value[index_ + 1] == char(136)) {
//                         if (index_ + 2 < str.size() && str.value[index_ + 2] == char(167)) {
//                             return view.substr(index_++, 3);
//                         }
//                     }
//                 }
//                 default:
//                     break;
//             }
//             ++index_;
//         }
//         return {};
//     }
// };