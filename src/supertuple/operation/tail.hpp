/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple tail operation implementation.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <utility>

#include <supertuple/environment.h>

#include <supertuple/detail/utility.hpp>
#include <supertuple/detail/tuple.hpp>
#include <supertuple/operation/select.hpp>

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
        return select(t, detail::id_sequence_t<I...>());
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
        return select(
            std::forward<decltype(t)>(t)
          , detail::id_sequence_t<I...>()
        );
    }
}

SUPERTUPLE_END_NAMESPACE
