/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple head operation implementation.
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
     * Retrieve the first element of a tuple.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to get the first element of.
     * @return The first element of the tuple.
     */
    template <id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) head(
        const detail::tuple_t<detail::id_sequence_t<0, I...>, T...>& t
    ) noexcept {
        return get<0>(t);
    }

    /**
     * Retrieve the first element of a moving tuple.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to get the first element of.
     * @return The first element of the tuple.
     */
    template <id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) head(
        detail::tuple_t<detail::id_sequence_t<0, I...>, T...>&& t
    ) noexcept {
        return get<0>(std::forward<decltype(t)>(t));
    }
}

SUPERTUPLE_END_NAMESPACE
