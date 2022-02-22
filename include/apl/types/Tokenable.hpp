#pragma once

#include <apl/tokenizer/Token.hpp>

template <typename T>
concept Tokenable = requires(T x) {
    { x.getToken() } -> std::same_as<Token>;
};

// package APL.types;

// import APL.tokenizer.Token;

// public interface Tokenable {
//     Token getToken();
// }