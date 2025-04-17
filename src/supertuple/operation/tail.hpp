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
#include <supertuple/detail/tuple.hpp>
#include <supertuple/operation/get.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

inline namespace operation
{
    /**
     * Return tuple with its first element removed.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to remove first element from.
     * @return The new tuple with first element removed.
     */
    template <id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) tail(
        const detail::tuple_t<detail::id_sequence_t<0, I...>, T...>& t
    ) {
        using in_tuple_t = tuple_t<T...>;
        using out_tuple_t = tuple_t<tuple_element_t<in_tuple_t, I>...>;
        return out_tuple_t(get<I>(t)...);
    }

    /**
     * Return moving tuple with its first element removed.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to remove first element from.
     * @return The new tuple with first element removed.
     */
    template <id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) tail(
        detail::tuple_t<detail::id_sequence_t<0, I...>, T...>&& t
    ) {
        using in_tuple_t = tuple_t<T...>;
        using out_tuple_t = tuple_t<tuple_element_t<in_tuple_t, I>...>;
        return out_tuple_t(get<I>(std::forward<decltype(t)>(t))...);
    }
}

SUPERTUPLE_END_NAMESPACE
