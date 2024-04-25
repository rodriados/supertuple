/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple tail operation implementation.
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
     * Returns a tuple with its first leaf removed.
     * @tparam I The tuple sequence indeces to match from tuple.
     * @tparam T The list of tuple's element members types.
     * @param t The tuple to have its first element removed.
     * @return The new tuple with removed head.
     */
    template <size_t ...I, typename ...T>
    SUPERTUPLE_CUDA_ENABLED inline constexpr decltype(auto) tail(
        const tuple_t<detail::identity_t<std::index_sequence<0, I...>>, T...>& t
    ) {
        return tuple_t<tuple_element_t<tuple_t<T...>, I>...>(
            operation::get<I>(t)...
        );
    }

    /**
     * Moves a tuple with its first leaf removed.
     * @tparam I The tuple sequence indeces to match from tuple.
     * @tparam T The list of tuple's element members types.
     * @param t The tuple to have its first element removed.
     * @return The new tuple with removed head.
     */
    template <size_t ...I, typename ...T>
    SUPERTUPLE_CUDA_ENABLED inline constexpr decltype(auto) tail(
        tuple_t<detail::identity_t<std::index_sequence<0, I...>>, T...>&& t
    ) {
        return tuple_t<tuple_element_t<tuple_t<T...>, I>...>(
            operation::get<I>(std::forward<decltype(t)>(t))...
        );
    }
}

SUPERTUPLE_END_NAMESPACE
