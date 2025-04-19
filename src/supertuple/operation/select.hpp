/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple select operation implementation.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2025-present Rodrigo Siqueira
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
     * Select elements by index from tuple.
     * @tparam K The selected tuple element indeces.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to have elements selected from.
     * @return The new tuple with selected elements.
     */
    template <id_t ...K, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) select(
        const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t
      , std::index_sequence<K...>
    ) {
        using in_tuple_t  = tuple_t<T...>;
        using out_tuple_t = tuple_t<typename in_tuple_t::template element_t<K>...>;
        return out_tuple_t(get<K>(t)...);
    }

    /**
     * Select elements by index from moving tuple.
     * @tparam K The selected tuple element indeces.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to have elements selected from.
     * @return The new tuple with selected elements.
     */
    template <id_t ...K, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) select(
        detail::tuple_t<detail::id_sequence_t<I...>, T...>&& t
      , std::index_sequence<K...>
    ) {
        using in_tuple_t  = tuple_t<T...>;
        using out_tuple_t = tuple_t<typename in_tuple_t::template element_t<K>...>;
        return out_tuple_t(get<K>(std::forward<decltype(t)>(t))...);
    }
}

SUPERTUPLE_END_NAMESPACE
