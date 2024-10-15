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
#include <supertuple/operation/get.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

inline namespace operation
{
    /**
     * Prepends an elements to the beginning of a tuple.
     * @tparam E The type of the element to prepend to tuple.
     * @tparam I The tuple sequence indeces to match from tuple.
     * @tparam T The list of tuple's element members types.
     * @param t The tuple to have an element prepended to.
     * @param element The element to prepend to the tuple.
     * @return The resulting tuple.
     */
    template <typename E, size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR decltype(auto) prepend(
        const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& t
      , const E& element
    ) {
        return tuple_t<E, T...>(
            element
          , operation::get<I>(t)...
        );
    }

    /**
     * Prepends an elements to the beginning and moves a tuple.
     * @tparam E The type of the element to prepend to tuple.
     * @tparam I The tuple sequence indeces to match from tuple.
     * @tparam T The list of tuple's element members types.
     * @param t The tuple to have an element prepended to.
     * @param element The element to prepend to the tuple.
     * @return The resulting tuple.
     */
    template <typename E, size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR decltype(auto) prepend(
        tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>&& t
      , E&& element
    ) {
        return tuple_t<E, T...>(
            std::forward<decltype(element)>(element)
          , operation::get<I>(std::forward<decltype(t)>(t))...
        );
    }
}

SUPERTUPLE_END_NAMESPACE
