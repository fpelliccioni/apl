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


// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


namespace ctll {

template <typename... Ts> struct list { };

struct _nothing { };

using empty_list = list<>;

// calculate size of list content
template <typename... Ts> constexpr auto size(list<Ts...>) noexcept { return sizeof...(Ts); }


// check if the list is empty
template <typename... Ts> constexpr bool empty(list<Ts...>) noexcept { return false; }
constexpr bool empty(empty_list) { return true; }


// concat two lists together left to right
template <typename... As, typename... Bs> constexpr auto concat(list<As...>, list<Bs...>) noexcept -> list<As..., Bs...> { return {}; }


// push something to the front of a list
template <typename T, typename... As> constexpr auto push_front(T, list<As...>) noexcept -> list<T, As...> { return {}; }


// pop element from the front of a list
template <typename T, typename... As> constexpr auto pop_front(list<T, As...>) noexcept -> list<As...> { return {}; }
constexpr auto pop_front(empty_list) -> empty_list;

// pop element from the front of a list and return new typelist too
template <typename Front, typename List> struct list_pop_pair {
	Front front{};
	List list{};
	constexpr list_pop_pair() = default;
};

template <typename Head, typename... As, typename T = _nothing> constexpr auto pop_and_get_front(list<Head, As...>, T = T()) noexcept -> list_pop_pair<Head, list<As...>> { return {}; }
template <typename T = _nothing> constexpr auto pop_and_get_front(empty_list, T = T()) noexcept -> list_pop_pair<T, empty_list> { return {}; }


// return front of the list
template <typename Head, typename... As, typename T = _nothing> constexpr auto front(list<Head, As...>, T = T()) noexcept -> Head { return {}; }
template <typename T = _nothing> constexpr auto front(empty_list, T = T()) noexcept -> T { return {}; }


// set operations
template <typename T> struct item_matcher {
	struct not_selected {
		template <typename... Ts> friend constexpr auto operator+(list<Ts...>, not_selected) -> list<Ts...>;
	};
	template <typename Y> struct wrapper {
		template <typename... Ts> friend constexpr auto operator+(list<Ts...>, wrapper<Y>) -> list<Ts...,Y>;
	};

	static constexpr auto check(T) { return std::true_type{}; }
	static constexpr auto check(...) { return std::false_type{}; }
	static constexpr auto select(T) { return not_selected{}; }
	template <typename Y> static constexpr auto select(Y) { return wrapper<Y>{}; }
};

template <typename T, typename... Ts> constexpr bool exists_in(T, list<Ts...>) noexcept {
	return (item_matcher<T>::check(Ts{}) || ... || false);
}

template <typename T, typename... Ts> constexpr auto add_item(T item, list<Ts...> l) noexcept {
	if constexpr (exists_in(item, l)) {
		return l;
	} else {
		return list<Ts..., T>{};
	}
}

template <typename T, typename... Ts> constexpr auto remove_item(T, list<Ts...>) noexcept {
	item_matcher<T> matcher;
	return decltype((list<>{} + ... + matcher.select(Ts{}))){};
}

}


// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


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

constexpr string_literal first("⊃");
constexpr string_literal equal("=");
constexpr string_literal _and("∧");
constexpr string_literal same("⊢");
constexpr string_literal reduce("/");

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

template <string_literal str>
struct tokenizer {
    size_t index_ = 0;

    constexpr
    std::optional<std::string_view> next() {
        auto view = std::string_view(str.value);
        while (index_ < str.size()) {
            char c = str.value[index_];
            switch (c) {
                case ' ': case '\t': case '\n':
                    break;
                case '/':
                case '=':
                    return view.substr(index_++, 1);
                case char(226): {
                    if (index_ + 1 < str.size() && str.value[index_ + 1] == char(138)) {
                        if (index_ + 2 < str.size() && str.value[index_ + 2] == char(131)) {
                            return view.substr(index_++, 3);
                        }
                        if (index_ + 2 < str.size() && str.value[index_ + 2] == char(162)) {
                            return view.substr(index_++, 3);
                        }
                    } else if (index_ + 1 < str.size() && str.value[index_ + 1] == char(136)) {
                        if (index_ + 2 < str.size() && str.value[index_ + 2] == char(167)) {
                            return view.substr(index_++, 3);
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


// using str_list_t = std::vector<std::string_view>;
using str_list_t = std::array<std::string_view, 256>;
// std::vector<char>

template <string_literal str>
str_list_t tokenize() {
    tokenizer<str> tz;
    str_list_t ret;
    size_t i = 0;
    while (auto token = tz.next()) {
        // std::cout << '[' << *token << ']' << '\n';
        // ret.push_back(*token);
        ret[i] = *token;
        ++i;
    }
    return ret;
}

struct reader {
    constexpr reader(str_list_t tokens)
        : tokens_(tokens)
    {}

    constexpr std::optional<std::string_view> next() {
    // constexpr std::optional<char*> next() {
        if (index_ >= tokens_.size()) return {};
        return tokens_[index_++];
        // return "";
    }

    constexpr std::optional<std::string_view> peek() {
    // constexpr std::optional<char*> peek() {
        if (index_ >= tokens_.size()) return {};
        return tokens_[index_];
        // return "";
    }

    str_list_t tokens_;
    // std::vector<char> tokens_;
    size_t index_ = 0;
};

// enum class op : size_t {};
// enum class fun : size_t {};
// using type_t = std::variant<op, fun>;

// enum class symbol_t : size_t {};
// using type_t = std::variant<symbol_t>;

enum class type_t {
    symbol,
};

struct value {
    type_t type;
    std::string_view str;

    constexpr value() = default;
    constexpr value(type_t type, std::string_view str)
        : type(type), str(str)
    {}
};

template <typename R>
constexpr
std::optional<value> read_form(R reader) {
    auto token = reader.peek();

    if ( ! token) {
        return {};
    }

    return read_atom(reader);
}

template <typename R>
constexpr
std::optional<value> read_atom(R reader) {
    return value{type_t::symbol, *reader.next() };
    // return value{};
}

template <string_literal str>
constexpr
std::optional<value> read_str() {
    auto tokens = tokenize<str>();
    reader r(tokens);
    return read_form(r);
}

// constexpr auto first_algo = [](auto f, auto l){
//     return *f;
// };





// template <string_literal str>
// auto apl() {
//     if (is_equal(str, first)) return first_algo;
// }




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
    //     std::cout << '[' << *token << ']' << '\n';
    // }


    // constexpr auto tokens = tokenize<"∧/⊃=⊢">();


    // auto tokens = tokenize<"∧/⊃=⊢">();
    // for (auto t : tokens) {
    //     std::cout << t << ',';
    // }
    // std::cout << std::endl;


    auto xxx = read_str<"∧/⊃=⊢">();




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
