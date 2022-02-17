#pragma once

#include <type_traits>

#include <apl/helpers/ct_error.hpp>
#include <apl/helpers/simple_functions.hpp>

auto monadic_or_dyadic = [](auto monadic, auto dyadic, auto... x){
    if constexpr (sizeof...(x) == 1) {
        return monadic(x...);
    } else if constexpr (sizeof...(x) == 2) {
        return dyadic(x...);
    } else {
        ct_error("invalid number of operands")();
    }
};

// + ----------------------------------------------------------------
auto plus_sign = [](auto... x) {
    return monadic_or_dyadic(fns::conjugate, fns::plus, x...);
};

// - ----------------------------------------------------------------
auto minus_sign = [](auto... x) {
    return monadic_or_dyadic(fns::negate, fns::substract, x...);
};

// × ----------------------------------------------------------------
auto times_sign = [](auto... x){
    return monadic_or_dyadic(fns::direction, fns::times, x...);
};

// ÷ ----------------------------------------------------------------
auto divide_sign = [](auto... x){
    return monadic_or_dyadic(fns::reciprocal, fns::divided_by, x...);
};

// ⌈ ----------------------------------------------------------------
auto upstile_sign = [](auto... x){
    return monadic_or_dyadic(fns::ceiling, fns::maximum, x...);
};

// ⌊ ----------------------------------------------------------------
auto downstile_sign = [](auto... x){
    return monadic_or_dyadic(fns::floor, fns::minimum, x...);
};

// ∨ ----------------------------------------------------------------
auto logical_or_sign = [](auto... x){
    return monadic_or_dyadic(fns::not_defined, fns::gcd, x...);
};


// (⌈/∨⌊/)10 9 8

