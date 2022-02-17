#pragma once

#include <type_traits>

#include <apl/helpers/ct_error.hpp>

// TODO ----------------------------------------------------------------
// This is not a function, this is an operator
// template <typename Op>
// auto identity() {
//     if constexpr (std::is_same_v<Op, decltype(fns::plus)>) {
//         return 0;
//     } else if constexpr (std::is_same_v<Op, decltype(times)>) {
//         return 1;
//     } else {
//         ct_error("invalid function")();
//     }
// }

// auto replicate = not_implemented;
// auto reduce = return [](auto op, auto arr){ return std::accumulate(std::begin(arr), std::end(arr), 0, op); };
auto slash_sign = [](auto op, auto arr) {
    // return std::accumulate(std::begin(arr), std::end(arr), identity<decltype(op)>(), op);
    return std::accumulate(std::begin(arr), std::end(arr), 0, op);
};


