#include <algorithm>
#include <array>
#include <iterator>
#include <numeric>
#include <iostream>
#include <limits>
#include <tuple>
#include <utility>
#include <vector>

#include <apl/helpers/apl_functions.hpp>
#include <apl/helpers/ct_error.hpp>
#include <apl/helpers/string_literal.hpp>
#include <apl/helpers/unicode.hpp>

#define CONSTANT(...) \
  union { static constexpr auto value() { return __VA_ARGS__; } }

#define CONSTANT_VALUE(...) \
  [] { using R = CONSTANT(__VA_ARGS__); return R{}; }()

struct zero {
    template <typename T>
    constexpr auto operator()(T) const {
        return T(0);
    }
};

struct one {
    template <typename T>
    constexpr auto operator()(T) const {
        return T(1);
    }
};

struct min {
    template <typename T>
    constexpr auto operator()(T) const {
        return std::numeric_limits<T>::min();
    }
};

struct max {
    template <typename T>
    constexpr auto operator()(T) const {
        return std::numeric_limits<T>::max();
    }
};

template <string_literal lit>
constexpr auto return_fn() {
    constexpr std::string_view c(lit.value);
    if constexpr (c == "+") {
        return plus_sign;
    } else if constexpr (c == "-") {
        return minus_sign;
    } else if constexpr (c == "×") {
        return times_sign;
    } else if constexpr (c == "÷") {
        return divide_sign;
    } else {
        ct_error("operator not supported")();
    }
}

template <string_literal lit, size_t from = 0, size_t to = lit.size()>
constexpr auto identity() {
    constexpr std::string_view sv(lit.value);
    constexpr std::string_view op_str = sv.substr(from, to);

    if constexpr (op_str == "+") {
        return 0;
    } else if constexpr (op_str == "-") {
        return 0;
    } else if constexpr (op_str == "×") {
        return 1;
    } else if constexpr (op_str == "÷") {
        return 1;
    } else {
        ct_error("operator not supported")();
    }

        // Function	 	    Identity
        // Add	                +	0
        // Subtract    	        -	0
        // Multiply	            ×	1
        // Divide	            ÷	1
        // Residue	            |	0
        // Minimum	            ⌊	M1
        // Maximum	            ⌈	-M
        // Power	            *	1
        // Binomial	            !	1
        // And	                ∧	1
        // Or	                ∨	0
        // Less	                <	0
        // Less or Equal	    ≤	1
        // Equal	            =	1
        // Greater	            >	0
        // Greater or Equal	    ≥	1
        // Not Equal	        ≠	0
        // Encode	            ⊤	0
        // Union	            ∪	⍬
        // Replicate	        /⌿	1
        // Expand	            \⍀	1
        // Rotate	            ⌽⊖	0
}

template <string_literal lit>
void print_lit() {
    constexpr auto size = sizeof(lit.value);
    constexpr auto contents = lit.value;
    std::cout << "Size: " << size << ", Contents: " << contents << std::endl;
}

template <string_literal lit>
constexpr
void print_int() {
    for (char c : lit) {
        std::cout << (int) (unsigned char)c << '|';
    }
    std::cout << std::endl;
}

constexpr
void print_int(std::string_view sv) {
    for (char c : sv) {
        std::cout << (int) (unsigned char)c << '|';
    }
    std::cout << std::endl;
}

template <string_literal lit, size_t from = 0, size_t to = lit.size()>
constexpr auto dyadic_fn_parse() {
    constexpr std::string_view sv(lit.value);
    constexpr std::string_view tmp = sv.substr(from, to);
    constexpr auto size = utf8_char_size(tmp);
    constexpr std::string_view str = tmp.substr(0, size);
    if constexpr (str == "+") {
        return std::pair{std::pair{plus_sign, zero{}}, from + size};
    } else if constexpr (str == "-") {
        return std::pair{std::pair{minus_sign, zero{}}, from + size};
    } else if constexpr (str == "×") {
        return std::pair{std::pair{times_sign, one{}}, from + size};
    } else if constexpr (str == "÷") {
        return std::pair{std::pair{divide_sign, one{}}, from + size};
    } else if constexpr (str == "⌈") {
        return std::pair{std::pair{upstile_sign, min{}}, from + size};              //TODO: idendity
    } else if constexpr (str == "⌊") {
        return std::pair{std::pair{downstile_sign, max{}}, from + size};            //TODO: idendity
    } else if constexpr (str == "∨") {
        return std::pair{std::pair{logical_or_sign, zero{}}, from + size};
    } else {
        ct_error("operator not supported")();
    }
}

// template <typename StrView>
// constexpr auto dyadic_fn_parse_internal(StrView) {
//     // f(CONSTANT_VALUE(std::make_tuple(101, 202)));
//     constexpr auto sv = StrView::value();
//     constexpr auto size = utf8_char_size(sv);
//     constexpr std::string_view chr = sv.substr(0, size);
//     constexpr std::string_view next = sv.substr(size);
//     if constexpr (chr == "+") {
//         return std::pair{std::pair{plus_sign, 0}, next};
//     } else if constexpr (chr == "-") {
//         return std::pair{std::pair{minus_sign, 0}, next};
//     } else if constexpr (chr == "×") {
//         return std::pair{std::pair{times_sign, 1}, next};
//     } else if constexpr (chr == "÷") {
//         return std::pair{std::pair{divide_sign, 1}, next};
//     } else if constexpr (chr == "⌈") {
//         return std::pair{std::pair{upstile_sign, 0}, next};              //TODO: idendity
//     } else if constexpr (chr == "⌊") {
//         return std::pair{std::pair{downstile_sign, 0}, next};            //TODO: idendity
//     } else if constexpr (chr == "∨") {
//         return std::pair{std::pair{logical_or_sign, 0}, next};
//     } else {
//         ct_error("operator not supported")();
//     }
// }

// template <typename StrView>
// constexpr auto derived_fn_parse_internal(StrView x) {
//     constexpr auto r = dyadic_fn_parse_internal(CONSTANT_VALUE(StrView::value()));
//     constexpr auto fn = r.first.first;
//     constexpr auto id = r.first.second;
//     constexpr auto sv1 = r.second;
//     constexpr auto size = utf8_char_size(sv1);
//     constexpr std::string_view chr = sv1.substr(0, size);

//     if constexpr (chr == "/") {
//         auto acc = [fn, id](auto rng) {
//             return std::accumulate(std::begin(rng), std::end(rng), id, fn);
//         };
//         return std::pair{acc, sv1};
//     } else {
//         ct_error("operator not supported")();
//     }
// }

template <string_literal lit, size_t from = 0, size_t to = lit.size()>
constexpr auto derived_fn_parse() {
    constexpr auto r = dyadic_fn_parse<lit, from, to>();
    constexpr auto fn = r.first.first;
    constexpr auto id = r.first.second;
    constexpr auto next_pos = r.second;
    constexpr auto tmp = std::string_view(lit.value).substr(next_pos, to);
    constexpr auto size = utf8_char_size(tmp);
    constexpr std::string_view next = tmp.substr(0, size);

    if constexpr (next == "/") {
        auto acc = [fn, id](auto rng) {
            using value_type = decltype(*std::begin(rng));
            return std::accumulate(std::begin(rng), std::end(rng), id(value_type{}), fn);
        };
        return std::pair{acc, next_pos + size};
    } else {
        ct_error("operator not supported")();
    }
}

// template <typename StrView>
// constexpr auto sp_comb_parse_internal(StrView) {
//     constexpr auto r0 = derived_fn_parse_internal(CONSTANT_VALUE(StrView::value()));
//     constexpr auto f = r0.first;
//     constexpr auto sv1 = r0.second;

//     constexpr auto r1 = dyadic_fn_parse_internal(CONSTANT_VALUE(sv1));
//     constexpr auto g = r1.first.first;
//     constexpr auto sv2 = r1.second;

//     constexpr auto r2 = derived_fn_parse_internal(CONSTANT_VALUE(sv2));
//     constexpr auto h = r2.first;
//     constexpr auto sv3 = r2.second;

//     auto spc = [f, g, h](auto rng) {
//         return g(f(rng), h(rng));
//     };

//     return std::pair{spc, sv3};
// }

template <string_literal lit, size_t from = 0, size_t to = lit.size()>
constexpr auto sp_comb_parse() {
    constexpr std::string_view sv(lit.value);
    constexpr std::string_view tmp = sv.substr(from, to);

    constexpr auto r0 = derived_fn_parse<lit, from, to>();
    constexpr auto f = r0.first;
    constexpr auto next0 = r0.second;

    constexpr auto r1 = dyadic_fn_parse<lit, next0, to>();
    constexpr auto g = r1.first.first;
    constexpr auto next1 = r1.second;

    constexpr auto r2 = derived_fn_parse<lit, next1, to>();
    constexpr auto h = r2.first;
    constexpr auto next2 = r2.second;

    auto spc = [f, g, h](auto rng) {
        return g(f(rng), h(rng));
    };

    return std::pair{spc, next2};
}


// template <string_literal_view lit>
// constexpr auto sp_comb_parse2() {
//     constexpr std::string_view tmp(lit.sv());
//     // constexpr std::string_view tmp = sv.substr(from, to);

//     constexpr auto r0 = derived_fn_parse<lit.value, lit.from, lit.to>();
//     constexpr auto f = r0.first;
//     constexpr auto next0 = r0.second;

//     constexpr auto r1 = dyadic_fn_parse<lit.value, next0, lit.to>();
//     constexpr auto g = r1.first.first;
//     constexpr auto next1 = r1.second;

//     constexpr auto r2 = derived_fn_parse<lit.value, next1, lit.to>();
//     constexpr auto h = r2.first;
//     constexpr auto next2 = r2.second;

//     auto spc = [f, g, h](auto rng) {
//         return g(f(rng), h(rng));
//     };

//     return std::pair{spc, next2};
// }



int main() {
    auto f1 = return_fn<"-">();
    static_assert(f1(20, 10) == 10);

    auto f2 = return_fn<"+">();
    static_assert(f2(20, 10) == 30);
    static_assert(f2(20) == 20);
    // static_assert(f2() == 20);
    // static_assert(f2(10, 20, 30) == 20);

    // std::vector v = {1, 2, 3, 4, 5};
    // int v[] = {1, 2, 3, 4, 5};
    std::array v = {1, 2, 3, 4, 5};

    // auto acc = std::accumulate(begin(v), end(v), 0, f2);
    // std::cout << acc << std::endl;

    // auto f3 = return_fn<"/">();
    // std::cout << f3(f2, v) << std::endl;

    static_assert(utf8_char_size("+") == 1);
    static_assert(utf8_char_size("×") == 2);
    static_assert(utf8_char_size("⌈") == 3);
    static_assert(utf8_char_size("⌊") == 3);
    static_assert(utf8_char_size("∨") == 3);

    static_assert(dyadic_fn_parse<"+">().second == utf8_char_size("+"));
    static_assert(dyadic_fn_parse<" +", 1>().second == utf8_char_size("+") + 1);
    static_assert(dyadic_fn_parse<"  +", 2>().second == utf8_char_size("+") + 2);
    static_assert(dyadic_fn_parse<"×">().second == utf8_char_size("×"));
    static_assert(dyadic_fn_parse<" ×", 1>().second == utf8_char_size("×") + 1);
    static_assert(dyadic_fn_parse<"  ×", 2>().second == utf8_char_size("×") + 2);
    static_assert(dyadic_fn_parse<"+/">().second == utf8_char_size("+"));
    static_assert(dyadic_fn_parse<" +/", 1>().second == utf8_char_size("+") + 1);
    static_assert(dyadic_fn_parse<"  +/", 2>().second == utf8_char_size("+") + 2);
    static_assert(dyadic_fn_parse<"×/">().second == utf8_char_size("×"));
    static_assert(dyadic_fn_parse<" ×/", 1>().second == utf8_char_size("×") + 1);
    static_assert(dyadic_fn_parse<"  ×/", 2>().second == utf8_char_size("×") + 2);

    // // auto r = derived_fn<"÷/">();
    // auto r = derived_fn_parse<"×/">().first;
    // // auto r = derived_fn<"+/">();
    // std::cout << r(v) << std::endl;
    // std::cout << derived_fn<"÷/">()(std::array{100., 5.}) << std::endl;
    // std::cout << derived_fn<"+/">()(std::array<int,0>()) << std::endl;
    static_assert(derived_fn_parse<"+/">().first(std::array{1, 2, 3, 4, 5}) == 15);
    static_assert(derived_fn_parse<" +/", 1>().first(std::array{1, 2, 3, 4, 5}) == 15);
    static_assert(derived_fn_parse<"  +/", 2>().first(std::array{1, 2, 3, 4, 5}) == 15);
    static_assert(derived_fn_parse<"+/">().second == 2);
    static_assert(derived_fn_parse<" +/", 1>().second == 3);
    static_assert(derived_fn_parse<"  +/", 2>().second == 4);
    static_assert(derived_fn_parse<"×/">().second == 3);
    static_assert(derived_fn_parse<" ×/", 1>().second == 4);
    static_assert(derived_fn_parse<"  ×/", 2>().second == 5);
    static_assert(derived_fn_parse<"⌈/">().second == 4);
    static_assert(derived_fn_parse<" ⌈/", 1>().second == 5);
    static_assert(derived_fn_parse<"  ⌈/", 2>().second == 6);
    static_assert(derived_fn_parse<"⌊/">().second == 4);
    static_assert(derived_fn_parse<" ⌊/", 1>().second == 5);
    static_assert(derived_fn_parse<"  ⌊/", 2>().second == 6);
    static_assert(derived_fn_parse<"+/=">().second == 2);
    static_assert(derived_fn_parse<" +/=", 1>().second == 3);
    static_assert(derived_fn_parse<"  +/=", 2>().second == 4);
    static_assert(derived_fn_parse<"×/=">().second == 3);
    static_assert(derived_fn_parse<" ×/=", 1>().second == 4);
    static_assert(derived_fn_parse<"  ×/=", 2>().second == 5);

    auto min_elem = derived_fn_parse<"⌊/">().first;
    auto max_elem = derived_fn_parse<"⌈/">().first;

    std::cout << min_elem(std::array{1, 2, 3, 4, 5}) << std::endl;
    std::cout << max_elem(std::array{1, 2, 3, 4, 5}) << std::endl;


    static_assert(sp_comb_parse<"⌈/∨⌊/">().second == 11);
    // static_assert(sp_comb_parse<"⌈/∨⌊/">().first(std::array{10, 9, 8}) == 2);
    // static_assert(sp_comb_parse_internal(CONSTANT_VALUE(std::string_view("⌈/∨⌊/"))).second == 11);
    // static_assert(sp_comb_parse2<"⌈/∨⌊/">().second == 11);





    // std::cout << f1(20, 10) << std::endl;
    // std::cout << f2(20, 10) << std::endl;
    // std::cout << f2(20) << std::endl;

    // auto f3 = return_fn<"×">();
    // f3(20, 10);

    // auto f4 = return_fn<"×">();
    // std::cout << f4(4, 4) << std::endl;
}








// template <char C>
// constexpr auto return_fn() {
//     if constexpr (C == '-') {
//         return minus_sign;
//     } else if constexpr (C == '+') {
//         return plus_sign;
//     } else if constexpr (C == '*') {
//         return times_sign;
//     } else if constexpr (C == '/') {
//         return [](auto op, auto arr){ return std::accumulate(std::begin(arr), std::end(arr), 0, op); };
//     } else {
//         ct_error("operator not supported")();
//     }
// }
