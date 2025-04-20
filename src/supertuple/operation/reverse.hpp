/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple reverse operation implementation.
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
     * Reverse the order of the elements of a tuple.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to reverse.
     * @return The reversed tuple.
     */
    template <id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) reverse(
        const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t
    ) {
        return select(t, detail::id_reverse_sequence_t<I...>());
    }

    /**
     * Reverse the order of the elements of a moving tuple.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to reverse.
     * @return The reversed tuple.
     */
    template <id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) reverse(
        detail::tuple_t<detail::id_sequence_t<I...>, T...>&& t
    ) {
        return select(
            std::forward<decltype(t)>(t)
          , detail::id_reverse_sequence_t<I...>()
        );
    }
}

SUPERTUPLE_END_NAMESPACE
