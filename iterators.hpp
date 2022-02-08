#pragma once

// #include <algorithm>
#include <iterator>
// #include <iostream>
// #include <optional>
// #include <ranges>
// #include <string_view>
// #include <variant>
// #include <vector>

template <std::input_or_output_iterator I>
struct first_iterator {
    using iterator_type	= I;
    using value_type = std::iter_value_t<I>;                 // TODO: If I models indirectly_readable; otherwise, not defined
    using difference_type = std::iter_difference_t<I>;
    using iterator_concept = typename I::iterator_concept;   // TODO: if present; otherwise, not defined
    using iterator_category = typename I::iterator_category; // TODO: if present; otherwise, not defined


    first_iterator() = default;

    explicit
    constexpr first_iterator(I x)
        : first_(x), current_(x)
    {}

    constexpr first_iterator(I first, I current)
        : first_(first), current_(current)
    {}

    constexpr decltype(auto) operator*() const {
        return *first_;
    }

    constexpr auto operator->() const noexcept
        requires std::contiguous_iterator<I> {
        return std::to_address(first_);
    }

    constexpr first_iterator& operator++() {
        ++current_;
        return *this;
    }

    decltype(auto) operator++(int) {
        return current_++;
    }

    constexpr first_iterator operator++(int)
        requires std::forward_iterator<I> {
        first_iterator temp{*this};
        ++*this;
        return temp;
    }

    constexpr first_iterator& operator--()
        requires std::bidirectional_iterator<I> {
        --current_;
        return *this;
    }

    constexpr first_iterator operator--(int)
        requires std::bidirectional_iterator<I> {
        first_iterator temp{*this};
        --*this;
        return temp;
    }

    constexpr first_iterator operator+(difference_type n) const
        requires std::random_access_iterator<I> {
        return first_iterator(first_, current_ + n);
    }

    constexpr first_iterator& operator+=(difference_type n)
        requires std::random_access_iterator<I> {
        current_ += n;
        return *this;
    }

    constexpr first_iterator operator-(difference_type n) const
        requires std::random_access_iterator<I> {
        return first_iterator(first_, current_ - n);
    }

    constexpr first_iterator& operator-=(difference_type n)
        requires std::random_access_iterator<I> {
        current_ -= n;
        return *this;
    }

    template <std::common_with<I> I2>
    friend constexpr bool operator==(first_iterator const& x, first_iterator<I2> const& y) {
        return x.current_ == y.current_;
    }

    template< std::common_with<I> I2 >
    friend constexpr std::strong_ordering operator<=>(first_iterator const& x, first_iterator<I2> const& y) {
        return x.current_ <=> y.current_;
    }

    I first_;
    I current_;
};


template <std::input_or_output_iterator I, std::input_or_output_iterator I2>
struct equal_iterator {
    using iterator_type	= I;
    using value_type = std::iter_value_t<I>;                 // TODO: If I models indirectly_readable; otherwise, not defined
    using difference_type = std::iter_difference_t<I>;
    using iterator_concept = typename I::iterator_concept;   // TODO: if present; otherwise, not defined
    using iterator_category = typename I::iterator_category; // TODO: if present; otherwise, not defined

    equal_iterator() = default;

    constexpr equal_iterator(I f1, I l1, I2 f2, I2 l2)
        : f1_(f1), l1_(l1), f2_(f2), l2_(l2)
    {}

    constexpr decltype(auto) operator*() const {
        if (f1_ == l1_) return false;
        if (f2_ == l2_) return false;
        return *f1_ == *f2_;
    }

    constexpr equal_iterator& operator++() {
        if (f1_ != l1_) ++f1_;
        if (f2_ != l2_) ++f2_;
        return *this;
    }

    constexpr void operator++(int) {
        if (f1_ != l1_) ++f1_;
        if (f2_ != l2_) ++f2_;
    }

    constexpr equal_iterator operator++( int )
        requires std::forward_iterator<I> && std::forward_iterator<I2> {
        auto tmp = *this;
        ++*this;
        return tmp;
    }

    constexpr equal_iterator& operator--()
        requires std::bidirectional_iterator<I> && std::bidirectional_iterator<I2> {
        --f1_;
        --f2_;
        return *this;
    }

    constexpr equal_iterator operator--(int)
        requires std::bidirectional_iterator<I> && std::bidirectional_iterator<I2> {
        auto tmp = *this;
        --*this;
        return tmp;
    }

    constexpr equal_iterator operator+(difference_type n) const
        requires std::random_access_iterator<I> && std::random_access_iterator<I2> {

        auto n1 = std::min(n, std::distance(f1_, l1_));
        auto n2 = std::min(n, std::distance(f2_, l2_));
        return equal_iterator(f1_ + n1, l1_, f2_ + n2, l2_);
    }

    constexpr equal_iterator& operator+=(difference_type n)
        requires std::random_access_iterator<I> && std::random_access_iterator<I2> {

        auto n1 = std::min(n, std::distance(f1_, l1_));
        auto n2 = std::min(n, std::distance(f2_, l2_));
        f1_ += n1;
        f2_ += n2;
        return *this;
    }

    //TODO: check bounds ¿?
    constexpr equal_iterator operator-(difference_type n) const
        requires std::random_access_iterator<I> && std::random_access_iterator<I2> {
        return equal_iterator(f1_ - n, l1_, f2_ - n, l2_);
    }

    constexpr equal_iterator& operator-=(difference_type n)
        requires std::random_access_iterator<I> && std::random_access_iterator<I2> {
        f1_ -= n;
        f2_ -= n;
        return *this;
    }

    template <std::common_with<I> I3, std::common_with<I2> I4>
    friend constexpr bool operator==(equal_iterator const& x, equal_iterator<I3, I4> const& y) {
        return x.f1_ == y.f1_ && x.f2_ == y.f2_;
    }

    template <std::common_with<I> I3, std::common_with<I2> I4>
    friend constexpr std::strong_ordering operator<=>(equal_iterator const& x, equal_iterator<I3, I4> const& y) {
        return x.f1_ <=> y.f1_ && x.f2_ <=> y.f2_;
    }

    I f1_;
    I l1_;
    I2 f2_;
    I2 l2_;
};

