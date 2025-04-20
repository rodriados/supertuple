/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple prepend operation implementation.
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
     * Prepend an element to the beginning of a tuple.
     * @tparam E The type of the element to prepend to tuple.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to have an element prepended to.
     * @param element The element to prepend to the tuple.
     * @return The resulting tuple.
     */
    template <typename E, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) prepend(
        const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t
      , E&& element
    ) {
        return tuple_t<E, T...>(
            std::forward<E>(element)
          , get<I>(t)...
        );
    }

    /**
     * Prepend an element to the beginning of a moving tuple.
     * @tparam E The type of the element to prepend to tuple.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to have an element prepended to.
     * @param element The element to prepend to the tuple.
     * @return The resulting tuple.
     */
    template <typename E, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) prepend(
        detail::tuple_t<detail::id_sequence_t<I...>, T...>&& t
      , E&& element
    ) {
        return tuple_t<E, T...>(
            std::forward<E>(element)
          , get<I>(std::forward<decltype(t)>(t))...
        );
    }
}

SUPERTUPLE_END_NAMESPACE
