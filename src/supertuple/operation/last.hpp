/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple last operation implementation.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <utility>

#include <supertuple/environment.h>

#include <supertuple/detail/utility.hpp>
#include <supertuple/detail/tuple.hpp>
#include <supertuple/operation/get.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

inline namespace operation
{
    /**
     * Retrieve the last element of a tuple.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to get the last element of.
     * @return The last element of the tuple.
     */
    template <id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) last(
        const detail::tuple_t<detail::id_sequence_t<0, I...>, T...>& t
    ) noexcept {
        constexpr size_t J = sizeof...(T);
        return get<J-1>(t);
    }

    /**
     * Retrieve the last element of a moving tuple.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to get the last element of.
     * @return The last element of the tuple.
     */
    template <id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) last(
        detail::tuple_t<detail::id_sequence_t<0, I...>, T...>&& t
    ) noexcept {
        constexpr size_t J = sizeof...(T);
        return get<J-1>(std::forward<decltype(t)>(t));
    }
}

SUPERTUPLE_END_NAMESPACE
