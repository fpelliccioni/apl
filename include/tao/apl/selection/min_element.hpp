//! \file tao/algorithm/selection/min_element.hpp
// Tao.Algorithm
//
// Copyright (c) 2022 Fernando Pelliccioni.
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TAO_ALGORITHM_SELECTION_MIN_ELEMENT_HPP_
#define TAO_ALGORITHM_SELECTION_MIN_ELEMENT_HPP_

// #include <algorithm>
// #include <iterator>
#include <utility>

#include <tao/algorithm/concepts.hpp>
#include <tao/algorithm/integers.hpp>
#include <tao/algorithm/type_attributes.hpp>

namespace tao { namespace algorithm {

// Bounded ranges
// -------------------------------------------------------

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
I min_element(I f, I l, R r) {
    //precondition:  readable_bounded_range(f, l)
    //postcondition: f != l && *min_element(f, l, r) == stable_sort_copy(f, l, r)[0]
    //complexity:    distance(f, l) - 1 comparisons

    if (f == l) return l;

    I m = f++;
    while (f != l) {
        if (r(*f, *m)) {
            m = f;
        }
        ++f;
    }
    return m;
}

template <ForwardIterator I>
    requires(Readable<I> && TotallyOrdered<ValueType<I>>)
inline
I min_element(I f, I l) {
    //same specs as min_element<I, R>
    return tao::algorithm::min_element(f, l, std::less<>());
}

template <Iterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
ValueType<I> min_value_nonempty(I f, I l, R r) {
    //precondition:     f != l && readable_bounded_range(f, l)
    //postcondition:    min_value_nonempty(f, l, r) == stable_sort_copy(f, l, r)[0]
    //complexity:       distance(f, l) - 1 comparisons
    //                  1 copy construction, distance(f, l) - 1 copy assignments (worst case)

    using T = ValueType<I>;
    T val = *f++;
    while (f != l) {
        if (r(*f, val)) {
            val = *f;
        }
        ++f;
    }
    return val;
}

template <Iterator I>
    requires(Readable<I> && TotallyOrdered<ValueType<I>>)
inline
ValueType<I> min_value_nonempty(I f, I l) {
    //same specs as min_value_nonempty<I, R>
    return tao::algorithm::min_value_nonempty(f, l, std::less<>());
}

template <Iterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
inline
ValueType<I> min_value(I f, I l, R r) {
    //precondition:     readable_bounded_range(f, l)
    //postcondition:    f != l && min_value(f, l, r) == stable_sort_copy(f, l, r)[0]
    //complexity:       distance(f, l) - 1 comparisons
    //                  1 copy construction, distance(f, l) - 1 copy assignments (worst case)

    using T = ValueType<I>;
    if (f == l) return supremum<T>; //supremum(r)
    return tao::algorithm::min_value_nonempty(f, l, r);
}

template <Iterator I>
    requires(Readable<I> && TotallyOrdered<ValueType<I>>)
inline
ValueType<I> min_value(I f, I l) {
    //same specs as min_value<I, R>
    return tao::algorithm::min_value(f, l, std::less<>());
}

// Counted ranges
// -------------------------------------------------------

template <ForwardIterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
std::pair<I, DistanceType<I>> min_element_n(I f, DistanceType<I> n, R r) {
    //precondition:  readable_counted_range(f, n)
    //postcondition: n != 0 && *get<0>(result) == stable_sort_copy_n(f, n, r)[0] &&
    //               *get<1>(result) == n - distance(f, get<0>(result))
    //complexity:    n - 1 comparisons

    if (zero(n)) return {f, n};

    I m = f;
    auto m_n = n;
    step_n(f, n);

    while ( ! zero(n)) {
        if (r(*f, *m)) {
            m = f;
            m_n = n;
        }
        step_n(f, n);
    }
    return {m, m_n};
}

template <ForwardIterator I>
    requires(Readable<I> && TotallyOrdered<ValueType<I>>)
inline
std::pair<I, DistanceType<I>> min_element_n(I f, DistanceType<I> n) {
    //same specs as min_element<I, R>
    return tao::algorithm::min_element_n(f, n, std::less<>());
}

template <Iterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
ValueType<I> min_value_nonempty_n(I f, DistanceType<I> n, R r) {
    //precondition:     n != 0 && readable_counted_range(f, n)
    //postcondition:    min_value_nonempty_n(f, n, r) == stable_sort_copy_n(f, n, r)[0]
    //complexity:       n - 1 comparisons
    //                  1 copy construction, n - 1 copy assignments (worst case)

    using T = ValueType<I>;
    T val = *f++;
    --n;
    while ( ! zero(n)) {
        if (r(*f, val)) {
            val = *f;
        }
        ++f;
        --n;
    }
    return val;
}

template <Iterator I>
    requires(Readable<I> && TotallyOrdered<ValueType<I>>)
inline
ValueType<I> min_value_nonempty_n(I f, DistanceType<I> n) {
    //same specs as min_value_nonempty_n<I, R>
    return tao::algorithm::min_value_nonempty_n(f, n, std::less<>());
}

template <Iterator I, StrictWeakOrdering R>
    requires(Readable<I> && Domain<R, ValueType<I>>)
inline
ValueType<I> min_value_n(I f, DistanceType<I> n, R r) {
    //precondition:     readable_counted_range(f, n)
    //postcondition:    n != 0 && min_value_n(f, n, r) == stable_sort_copy_n(f, n, r)[0]
    //complexity:       n - 1 comparisons
    //                  1 copy construction, n - 1 copy assignments (worst case)

    using T = ValueType<I>;
    if (zero(n)) return supremum<T>; //supremum(r)
    return tao::algorithm::min_value_nonempty_n(f, n, r);
}

template <Iterator I>
    requires(Readable<I> && TotallyOrdered<ValueType<I>>)
inline
ValueType<I> min_value_n(I f, DistanceType<I> n) {
    //same specs as min_value_n<I, R>
    return tao::algorithm::min_value_n(f, n, std::less<>());
}


}} /*tao::algorithm*/

#include <tao/algorithm/concepts_undef.hpp>

#endif /*TAO_ALGORITHM_SELECTION_MIN_ELEMENT_HPP_*/

#ifdef DOCTEST_LIBRARY_INCLUDED
#include <forward_list>
#include <list>
#include <vector>

#include <tao/benchmark/instrumented.hpp>

using namespace tao::algorithm;
using namespace std;

TEST_CASE("[min_element] testing min_element selection algorithm, instrumented, random access") {
    using T = instrumented<int>;
    vector<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};

    instrumented<int>::initialize(0);
    auto m0 = tao::algorithm::min_element(begin(a), end(a), less<>());

    double* count_p = instrumented<int>::counts;
    CHECK(count_p[instrumented_base::comparison] == a.size() - 1);
}

TEST_CASE("[min_element] testing min_element selection algorithm, random access, no natural order, stability check") {
    using T = no_natural_order;
    vector<T> a = {{0, 3}, {1, 6}, {2, 2}, {3, 1}, {4, 4}, {5, 5}, {6, 1}, {7, 6}, {8, 2}, {9, 3}};

    auto salary_cmp = [](no_natural_order const& a, no_natural_order const& b) {
        return a.salary < b.salary;
    };

    auto m0 = tao::algorithm::min_element(begin(a), end(a), salary_cmp);
    CHECK(m0 == next(begin(a), 3));
    CHECK(m0->salary == 1);
    CHECK(m0->id == 3);

    auto m1 = tao::algorithm::min_element(successor(m0), end(a), salary_cmp);
    CHECK(m1 == next(m0, 3));
    CHECK(m1->salary == 1);
    CHECK(m1->id == 6);
}

TEST_CASE("[min_element] testing min_element selection algorithm, random access") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};

    auto m0 = tao::algorithm::min_element(begin(a), end(a), less<>());
    CHECK(m0 == next(begin(a), 3));

    auto m1 = tao::algorithm::min_element(successor(m0), end(a), less<>());
    CHECK(m1 == next(m0, 3));
}

TEST_CASE("[min_element] testing min_element selection algorithm, random access, default relation") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};

    auto m0 = tao::algorithm::min_element(begin(a), end(a));
    CHECK(m0 == next(begin(a), 3));

    auto m1 = tao::algorithm::min_element(successor(m0), end(a));
    CHECK(m1 == next(m0, 3));
}

TEST_CASE("[min_element] testing min_element_n selection algorithm, random access") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};

    auto m0 = min_element_n(begin(a), a.size(), less<>());
    CHECK(get<0>(m0) == next(begin(a), 3));
    CHECK(get<1>(m0) == a.size() - 3);

    auto m1 = min_element_n(successor(get<0>(m0)), get<1>(m0) - 1, less<>());
    CHECK(get<0>(m1) == next(get<0>(m0), 3));
    CHECK(get<1>(m1) == a.size() - 6);
}

TEST_CASE("[min_element] testing min_element_n selection algorithm, random access, default relation") {
    using T = int;
    vector<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};

    auto m0 = min_element_n(begin(a), a.size());
    CHECK(get<0>(m0) == next(begin(a), 3));
    CHECK(get<1>(m0) == a.size() - 3);

    auto m1 = min_element_n(successor(get<0>(m0)), get<1>(m0) - 1);
    CHECK(get<0>(m1) == next(get<0>(m0), 3));
    CHECK(get<1>(m1) == a.size() - 6);
}

TEST_CASE("[min_element] testing min_element selection algorithm, bidirectional") {
    using T = int;
    list<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};

    auto m0 = tao::algorithm::min_element(begin(a), end(a), less<>());
    CHECK(m0 == next(begin(a), 3));

    auto m1 = tao::algorithm::min_element(successor(m0), end(a), less<>());
    CHECK(m1 == next(m0, 3));
}

TEST_CASE("[min_element] testing min_element selection algorithm, bidirectional, default relation") {
    using T = int;
    list<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};

    auto m0 = tao::algorithm::min_element(begin(a), end(a));
    CHECK(m0 == next(begin(a), 3));

    auto m1 = tao::algorithm::min_element(successor(m0), end(a));
    CHECK(m1 == next(m0, 3));
}

TEST_CASE("[min_element] testing min_element_n selection algorithm, bidirectional") {
    using T = int;
    list<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};

    auto m0 = min_element_n(begin(a), a.size(), less<>());
    CHECK(get<0>(m0) == next(begin(a), 3));
    CHECK(get<1>(m0) == a.size() - 3);

    auto m1 = min_element_n(successor(get<0>(m0)), get<1>(m0) - 1, less<>());
    CHECK(get<0>(m1) == next(get<0>(m0), 3));
    CHECK(get<1>(m1) == a.size() - 6);
}

TEST_CASE("[min_element] testing min_element_n selection algorithm, bidirectional, default relation") {
    using T = int;
    list<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};

    auto m0 = min_element_n(begin(a), a.size());
    CHECK(get<0>(m0) == next(begin(a), 3));
    CHECK(get<1>(m0) == a.size() - 3);

    auto m1 = min_element_n(successor(get<0>(m0)), get<1>(m0) - 1);
    CHECK(get<0>(m1) == next(get<0>(m0), 3));
    CHECK(get<1>(m1) == a.size() - 6);
}

TEST_CASE("[min_element] testing min_element selection algorithm, forward") {
    using T = int;
    forward_list<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};

    auto m0 = tao::algorithm::min_element(begin(a), end(a), less<>());
    CHECK(m0 == next(begin(a), 3));

    auto m1 = tao::algorithm::min_element(successor(m0), end(a), less<>());
    CHECK(m1 == next(m0, 3));
}

TEST_CASE("[min_element] testing min_element selection algorithm, forward, default relation") {
    using T = int;
    forward_list<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};

    auto m0 = tao::algorithm::min_element(begin(a), end(a));
    CHECK(m0 == next(begin(a), 3));

    auto m1 = tao::algorithm::min_element(successor(m0), end(a));
    CHECK(m1 == next(m0, 3));
}

TEST_CASE("[min_element] testing min_element_n selection algorithm, forward") {
    using T = int;
    forward_list<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};
    auto n = distance(begin(a), end(a));

    auto m0 = min_element_n(begin(a), n, less<>());
    CHECK(get<0>(m0) == next(begin(a), 3));
    CHECK(get<1>(m0) == n - 3);

    auto m1 = min_element_n(successor(get<0>(m0)), get<1>(m0) - 1, less<>());
    CHECK(get<0>(m1) == next(get<0>(m0), 3));
    CHECK(get<1>(m1) == n - 6);
}

TEST_CASE("[min_element] testing min_element_n selection algorithm, forward, default relation") {
    using T = int;
    forward_list<T> a = {3, 6, 2, 1, 4, 5, 1, 6, 2, 3};
    auto n = distance(begin(a), end(a));

    auto m0 = min_element_n(begin(a), n);
    CHECK(get<0>(m0) == next(begin(a), 3));
    CHECK(get<1>(m0) == n - 3);

    auto m1 = min_element_n(successor(get<0>(m0)), get<1>(m0) - 1);
    CHECK(get<0>(m1) == next(get<0>(m0), 3));
    CHECK(get<1>(m1) == n - 6);
}

#endif /*DOCTEST_LIBRARY_INCLUDED*/
