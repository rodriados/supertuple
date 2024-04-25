/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple append operation implementation.
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
     * Appends an elements to the end of a tuple.
     * @tparam E The type of the element to append to tuple.
     * @tparam I The tuple sequence indeces to match from tuple.
     * @tparam T The list of tuple's element members types.
     * @param t The tuple to have an element appended to.
     * @param element The element to append to the tuple.
     * @return The resulting tuple.
     */
    template <typename E, size_t ...I, typename ...T>
    SUPERTUPLE_CUDA_ENABLED inline constexpr decltype(auto) append(
        const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& t
      , const E& element
    ) {
        return tuple_t<T..., E>(
            operation::get<I>(t)...
          , element
        );
    }

    /**
     * Appends an elements to the end and moves a tuple.
     * @tparam E The type of the element to append to tuple.
     * @tparam I The tuple sequence indeces to match from tuple.
     * @tparam T The list of tuple's element members types.
     * @param t The tuple to have an element appended to.
     * @param element The element to append to the tuple.
     * @return The resulting tuple.
     */
    template <typename E, size_t ...I, typename ...T>
    SUPERTUPLE_CUDA_ENABLED inline constexpr decltype(auto) append(
        tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>&& t
      , E&& element
    ) {
        return tuple_t<T..., E>(
            operation::get<I>(std::forward<decltype(t)>(t))...
          , std::forward<decltype(element)>(element)
        );
    }
}

SUPERTUPLE_END_NAMESPACE
