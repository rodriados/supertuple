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
     * Concatenates two tuples into a single one.
     * @tparam I The first tuple sequence indeces.
     * @tparam J The second tuple sequence indeces.
     * @tparam T The first tuple's element members types.
     * @tparam U The second tuple's element members types.
     * @param a The first tuple to concatenate.
     * @param b The second tuple to concatenate.
     * @return The resulting concatenated tuple.
     */
    template <size_t ...I, size_t ...J, typename ...T, typename ...U>
    SUPERTUPLE_CUDA_ENABLED inline constexpr decltype(auto) concat(
        const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& a
      , const tuple_t<detail::identity_t<std::index_sequence<J...>>, U...>& b
    ) {
        return tuple_t<T..., U...>(
            operation::get<I>(a)...
          , operation::get<J>(b)...
        );
    }

    /**
     * Concatenates two tuples by moving them into a single one.
     * @tparam I The first tuple sequence indeces.
     * @tparam J The second tuple sequence indeces.
     * @tparam T The first tuple's element members types.
     * @tparam U The second tuple's element members types.
     * @param a The first tuple to concatenate.
     * @param b The second tuple to concatenate.
     * @return The resulting concatenated tuple.
     */
    template <size_t ...I, size_t ...J, typename ...T, typename ...U>
    SUPERTUPLE_CUDA_ENABLED inline constexpr decltype(auto) concat(
        tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>&& a
      , tuple_t<detail::identity_t<std::index_sequence<J...>>, U...>&& b
    ) {
        return tuple_t<T..., U...>(
            operation::get<I>(std::forward<decltype(a)>(a))...
          , operation::get<J>(std::forward<decltype(b)>(b))...
        );
    }
}

SUPERTUPLE_END_NAMESPACE
