/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple reverse operation implementation.
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
     * Reverses a tuple.
     * @tparam I The tuple sequence indeces.
     * @tparam T The tuple's element members types.
     * @param t The tuple to be reversed.
     * @return The reversed tuple.
     */
    template <size_t ...I, typename ...T>
    SUPERTUPLE_CUDA_ENABLED inline constexpr decltype(auto) reverse(
        const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& t
    ) {
        constexpr size_t J = sizeof...(T);
        return tuple_t<tuple_element_t<tuple_t<T...>, J-I-1>...>(
            operation::get<J-I-1>(t)...
        );
    }

    /**
     * Moves a tuple into its reversed counter-part.
     * @tparam I The tuple sequence indeces.
     * @tparam T The tuple's element members types.
     * @param t The tuple to be reversed.
     * @return The reversed tuple.
     */
    template <size_t ...I, typename ...T>
    SUPERTUPLE_CUDA_ENABLED inline constexpr decltype(auto) reverse(
        tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>&& t
    ) {
        constexpr size_t J = sizeof...(T);
        return tuple_t<tuple_element_t<tuple_t<T...>, J-I-1>...>(
            operation::get<J-I-1>(std::forward<decltype(t)>(t))...
        );
    }
}

SUPERTUPLE_END_NAMESPACE
