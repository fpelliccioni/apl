#pragma once

#include <cstddef>
#include <string_view>

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

template <size_t N, size_t from = 0, size_t size_ = N>
struct string_literal_view {
    char value[N];

    constexpr string_literal_view(char const (&str)[N]) {
        std::copy_n(str, N, value);
    }

    constexpr size_t size() const {
        return size_;
    }

    constexpr char const* begin() const {
        return value + from;
    }

    constexpr char const* end() const {
        return value + size_;
    }

    constexpr std::string_view sv() const {
        return {begin(), size()};
    }
};
