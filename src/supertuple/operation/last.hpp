/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple last operation implementation.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <utility>

#include <supertuple/environment.h>
#include <supertuple/tuple.hpp>

#include <supertuple/detail/utility.hpp>
#include <supertuple/operation/get.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

inline namespace operation
{
    /**
     * Retrieves and returns the value of the last leaf of a tuple.
     * @tparam I The tuple sequence indeces to match from tuple.
     * @tparam T The list of tuple's element members types.
     * @param t The tuple to get the last element from.
     * @return The last value of tuple.
     */
    template <size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR decltype(auto) last(
        const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& t
    ) noexcept {
        constexpr size_t J = sizeof...(T);
        return operation::get<J - 1>(t);
    }

    /**
     * Retrieves and moves the value of the last leaf of a tuple.
     * @tparam I The tuple sequence indeces to match from tuple.
     * @tparam T The list of tuple's element members types.
     * @param t The tuple to get the last element from.
     * @return The last value of tuple.
     */
    template <size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR decltype(auto) last(
        tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>&& t
    ) noexcept {
        constexpr size_t J = sizeof...(T);
        return operation::get<J - 1>(std::forward<decltype(t)>(t));
    }
}

SUPERTUPLE_END_NAMESPACE
