/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple init operation implementation.
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
     * Return tuple with its last element removed.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to remove last element from.
     * @return The new tuple with last element removed.
     */
    template <id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) init(
        const detail::tuple_t<detail::id_sequence_t<0, I...>, T...>& t
    ) {
        using in_tuple_t = tuple_t<T...>;
        using out_tuple_t = tuple_t<tuple_element_t<in_tuple_t, I-1>...>;
        return out_tuple_t(get<I-1>(t)...);
    }

    /**
     * Return moving tuple with its last element removed.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to remove last element from.
     * @return The new tuple with last element removed.
     */
    template <id_t ...I, typename ...T, typename U>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) init(
        detail::tuple_t<detail::id_sequence_t<0, I...>, T..., U>&& t
    ) {
        using in_tuple_t = tuple_t<T...>;
        using out_tuple_t = tuple_t<tuple_element_t<in_tuple_t, I-1>...>;
        return out_tuple_t(get<I-1>(std::forward<decltype(t)>(t))...);
    }
}

SUPERTUPLE_END_NAMESPACE
