#pragma once

#include <cstdint>
#include <cstddef>
#include <string_view>

template <size_t N>
constexpr
bool bit_set(char x) {
    return x & (1 << N);
}

constexpr
size_t utf8_char_size(std::string_view x) {
    if (x.size() < 1) return 0;
    if (uint8_t(x[0]) <= uint8_t(0b01111111)) return 1;               //0xxxxxxx

    if (x.size() < 2) return 0;
    if (uint8_t(x[0]) <= uint8_t(0b11011111) &&
        bit_set<7>(x[1]) && ! bit_set<6>(x[1])) return 2;             //110yyyyy 10xxxxxx

    if (x.size() < 3) return 0;
    if (uint8_t(x[0]) <= uint8_t(0b11101111) &&
        bit_set<7>(x[1]) && ! bit_set<6>(x[1]) &&
        bit_set<7>(x[2]) && ! bit_set<6>(x[2])) return 3;             //1110zzzz 10yyyyyy 10xxxxxx

    if (x.size() < 4) return 0;
    if (uint8_t(x[0]) <= uint8_t(0b11110111) &&
        bit_set<7>(x[1]) && ! bit_set<6>(x[1]) &&
        bit_set<7>(x[2]) && ! bit_set<6>(x[2]) &&
        bit_set<7>(x[3]) && ! bit_set<6>(x[3])) return 4;             //11110uuu 10uuzzzz 10yyyyyy 10xxxxxx

    return 0;
}

constexpr
bool valid_utf8_char(std::string_view x) {
    return utf8_char_size(x) != 0;
}