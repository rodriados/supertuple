/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple concat operation implementation.
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
     * The base case of concatenation of a single tuple.
     * @tparam I The tuple's sequence indeces.
     * @tparam T The tuple's element member types.
     * @param a The tuple to be returned.
     * @return The resulting concatenated tuple.
     */
    template <size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR auto concat(
        const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& a
    ) -> decltype(auto) {
        return tuple_t<T...>(operation::get<I>(a)...);
    }

    /**
     * The base case of moving concatenation of a single tuple.
     * @tparam I The tuple's sequence indeces.
     * @tparam T The tuple's element member types.
     * @param a The tuple to be moved and returned.
     * @return The resulting concatenated tuple.
     */
    template <size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR auto concat(
        tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>&& a
    ) -> decltype(auto) {
        return tuple_t<T...>(operation::get<I>(std::forward<decltype(a)>(a))...);
    }

    /**
     * Concatenates multiple tuples into a single one.
     * @tparam I The first tuple sequence indeces.
     * @tparam J The second tuple sequence indeces.
     * @tparam T The first tuple's element member types.
     * @tparam U The second tuple's element member types.
     * @tparam Z The types of remaining tuples to concatenate.
     * @param a The first tuple to concatenate.
     * @param b The second tuple to concatenate.
     * @param tail The remaining tuples to concatenate.
     * @return The resulting concatenated tuple.
     */
    template <size_t ...I, size_t ...J, typename ...T, typename ...U, typename ...Z>
    SUPERTUPLE_CONSTEXPR decltype(auto) concat(
        const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& a
      , const tuple_t<detail::identity_t<std::index_sequence<J...>>, U...>& b
      , const Z&... tail
    ) {
        return concat(
            tuple_t<T..., U...>(
                operation::get<I>(a)...
              , operation::get<J>(b)...)
          , tail...
        );
    }

    /**
     * Concatenates multiple tuples by moving them into a single one.
     * @tparam I The first tuple sequence indeces.
     * @tparam J The second tuple sequence indeces.
     * @tparam T The first tuple's element member types.
     * @tparam U The second tuple's element member types.
     * @tparam Z The types of remaining tuples to concatenate.
     * @param a The first tuple to concatenate.
     * @param b The second tuple to concatenate.
     * @param tail The remaining tuples to concatenate.
     * @return The resulting concatenated tuple.
     */
    template <size_t ...I, size_t ...J, typename ...T, typename ...U, typename ...Z>
    SUPERTUPLE_CONSTEXPR decltype(auto) concat(
        tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>&& a
      , tuple_t<detail::identity_t<std::index_sequence<J...>>, U...>&& b
      , Z&&... tail
    ) {
        return concat(
            tuple_t<T..., U...>(
                operation::get<I>(std::forward<decltype(a)>(a))...
              , operation::get<J>(std::forward<decltype(b)>(b))...)
          , std::forward<decltype(tail)>(tail)...
        );
    }
}

SUPERTUPLE_END_NAMESPACE
