#pragma once

#include <utility>

template <typename To, typename From>
bool instanceof(From* x) {
    return dynamic_cast<To>(x) != nullptr;
}

template <typename T, typename U>
int compare(T x, U y) {
    if (x == y) return 0;
    if (x < y) return -1;
    return 1;
}

template <typename T, typename U>
int compare(T* x, U* y) {
    return compare(*x, *y);
}

template <typename To1, typename To2, typename From1, typename From2>
std::pair<bool, int> compareToAs(From1* x, From2* y) {
    auto* cx = dynamic_cast<To1>(x);
    if (cx == nullptr) return {false, 0};

    auto* cy = dynamic_cast<To2>(y);
    if (cy == nullptr) return {false, 0};

    return {true, compare(cx, cy)};
}
