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

inline namespace operation
{
    /**
     * The base case of concatenation of a single tuple.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param a The tuple to be returned.
     * @return The resulting concatenated tuple.
     */
    template <id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR auto concat(
        const detail::tuple_t<detail::id_sequence_t<I...>, T...>& a
    ) -> decltype(auto) {
        return tuple_t<T...>(get<I>(a)...);
    }

    /**
     * The base case of concatenation of a single moving tuple.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param a The tuple to be moved and returned.
     * @return The resulting concatenated tuple.
     */
    template <id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR auto concat(
        detail::tuple_t<detail::id_sequence_t<I...>, T...>&& a
    ) -> decltype(auto) {
        return tuple_t<T...>(get<I>(std::forward<decltype(a)>(a))...);
    }

    /**
     * Concatenate multiple tuples into a single one.
     * @tparam I The first tuple index sequence.
     * @tparam J The second tuple index sequence.
     * @tparam T The first tuple element types.
     * @tparam U The second tuple element types.
     * @tparam Z The types of remaining tuples to concatenate.
     * @param a The first tuple to concatenate.
     * @param b The second tuple to concatenate.
     * @param tail The remaining tuples to concatenate.
     * @return The resulting concatenated tuple.
     */
    template <id_t ...I, id_t ...J, typename ...T, typename ...U, typename ...Z>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) concat(
        const detail::tuple_t<detail::id_sequence_t<I...>, T...>& a
      , const detail::tuple_t<detail::id_sequence_t<J...>, U...>& b
      , Z&&... tail
    ) {
        return concat(
            tuple_t<T..., U...>(
                get<I>(a)...
              , get<J>(b)...)
          , std::forward<Z>(tail)...
        );
    }

    /**
     * Concatenate multiple moving tuples into a single one.
     * @tparam I The first tuple index sequence.
     * @tparam J The second tuple index sequence.
     * @tparam T The first tuple element types.
     * @tparam U The second tuple element types.
     * @tparam Z The types of remaining tuples to concatenate.
     * @param a The first tuple to concatenate.
     * @param b The second tuple to concatenate.
     * @param tail The remaining tuples to concatenate.
     * @return The resulting concatenated tuple.
     */
    template <id_t ...I, id_t ...J, typename ...T, typename ...U, typename ...Z>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) concat(
        detail::tuple_t<detail::id_sequence_t<I...>, T...>&& a
      , detail::tuple_t<detail::id_sequence_t<J...>, U...>&& b
      , Z&&... tail
    ) {
        return concat(
            tuple_t<T..., U...>(
                get<I>(std::forward<decltype(a)>(a))...
              , get<J>(std::forward<decltype(b)>(b))...)
          , std::forward<Z>(tail)...
        );
    }
}

SUPERTUPLE_END_NAMESPACE
