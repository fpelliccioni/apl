#pragma once

// #include <algorithm>
#include <iterator>
// #include <iostream>
// #include <optional>
#include <ranges>
// #include <string_view>
// #include <variant>
// #include <vector>

#include <iterators.hpp>

template <std::ranges::view V>
class first_view : public std::ranges::view_interface<first_view<V>> {
public:
    first_view() = default;
    first_view(V v) :
        begin_(v.begin()), end_(v.end())
    {}
    auto begin() const { return begin_; }
    auto end() const { return end_; }
private:
    using begin_t = first_iterator<decltype(std::declval<V>().begin())>;
    using end_t = first_iterator<decltype(std::declval<V>().end())>;
    begin_t begin_{};
    end_t end_{};
};

template <class R>
first_view(R&&) -> first_view<std::views::all_t<R>>;


template <std::ranges::view V>
class identity_view : public std::ranges::view_interface<identity_view<V>> {
public:
    identity_view() = default;
    identity_view(V v) :
        begin_(v.begin()), end_(v.end())
    {}
    auto begin() const { return begin_; }
    auto end() const { return end_; }
private:
    using it_t = decltype(std::declval<V>().begin());
    it_t begin_{};
    it_t end_{};
};

template <class R>
identity_view(R&&) -> identity_view<std::views::all_t<R>>;


template <std::ranges::view V, std::ranges::view V2>
class equal_view : public std::ranges::view_interface<equal_view<V, V2>> {
public:
    equal_view() = default;
    equal_view(V v, V2 v2) :
        begin_(v.begin(), v.end(), v2.begin(), v2.end()),
        end_(v.end(), v.end(), v2.end(), v2.end())
    {}
    auto begin() const { return begin_; }
    auto end() const { return end_; }
private:
    using it_t = equal_iterator<decltype(std::declval<V>().begin()), decltype(std::declval<V2>().begin())>;
    it_t begin_{};
    it_t end_{};
};

template <class R, class R2>
equal_view(R&&, R2&&) -> equal_view<std::views::all_t<R>, std::views::all_t<R2>>;
