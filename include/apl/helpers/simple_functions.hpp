#pragma once

#include <algorithm>
#include <numeric>

#include <apl/helpers/ct_error.hpp>

namespace fns {

auto not_defined = [](auto a){ ct_error("not defined")(); };

//TODO
auto not_implemented = [](auto a){ ct_error("not implemented yet")(); };

// + ----------------------------------------------------------------
auto conjugate = [](auto a){ return a; };
auto plus = [](auto a, auto b){ return a + b; };

// - ----------------------------------------------------------------
auto negate = [](auto a){ return -a; };
auto substract = [](auto a, auto b){ return a - b; };

// × ----------------------------------------------------------------
auto direction = not_implemented;
auto times = [](auto a, auto b){ return a * b; };

// ÷ ----------------------------------------------------------------
auto reciprocal = not_implemented;
auto divided_by = [](auto a, auto b){ return a / b; };

// ⌈ ----------------------------------------------------------------
auto ceiling = not_implemented;
auto maximum = [](auto a, auto b){ return std::max(a, b); };

// ⌊ ----------------------------------------------------------------
auto floor = not_implemented;
auto minimum = [](auto a, auto b){ return std::min(a, b); };


// ∨ ----------------------------------------------------------------
// Monadic Logical Or is not defined.
auto gcd = [](auto a, auto b){ return std::gcd(a, b); };


}