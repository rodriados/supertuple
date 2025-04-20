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
#include <supertuple/detail/tuple.hpp>
#include <supertuple/operation/get.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

namespace detail
{
    /**
     * Concatenate two tuples into a single one.
     * @tparam I The first tuple index sequence.
     * @tparam J The second tuple index sequence.
     * @tparam T The first tuple element types.
     * @tparam U The second tuple element types.
     * @param t The first tuple to concatenate.
     * @param u The second tuple to concatenate.
     * @return The resulting concatenated tuple.
     */
    template <id_t ...I, id_t ...J, typename ...T, typename ...U>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) concat(
        const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t
      , detail::tuple_t<detail::id_sequence_t<J...>, U...>&& u
    ) {
        return supertuple::tuple_t<T..., U...>(
            get<I>(t)...
          , get<J>(std::forward<decltype(u)>(u))...
        );
    }

    /**
     * Concatenate two moving tuples into a single one.
     * @tparam I The first tuple index sequence.
     * @tparam J The second tuple index sequence.
     * @tparam T The first tuple element types.
     * @tparam U The second tuple element types.
     * @param t The first tuple to concatenate.
     * @param u The second tuple to concatenate.
     * @return The resulting concatenated tuple.
     */
    template <id_t ...I, id_t ...J, typename ...T, typename ...U>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) concat(
        detail::tuple_t<detail::id_sequence_t<I...>, T...>&& t
      , detail::tuple_t<detail::id_sequence_t<J...>, U...>&& u
    ) {
        return supertuple::tuple_t<T..., U...>(
            get<I>(std::forward<decltype(t)>(t))...
          , get<J>(std::forward<decltype(u)>(u))...
        );
    }
}

inline namespace operation
{
    /**
     * The base case for concatenation recursion.
     * @return The empty tuple.
     */
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) concat()
    {
        return tuple_t();
    }

    /**
     * Concatenate multiple tuples into a single one.
     * @tparam T The first tuple type.
     * @tparam Z The types of remaining tuples to concatenate.
     * @param t The first tuple to concatenate.
     * @param tail The remaining tuples to concatenate.
     * @return The resulting concatenated tuple.
     */
    template <typename T, typename ...Z>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) concat(T&& t, Z&&... tail)
    {
        return detail::concat(
            std::forward<T>(t)
          , concat(std::forward<Z>(tail)...)
        );
    }
}

SUPERTUPLE_END_NAMESPACE
