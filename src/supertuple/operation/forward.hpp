/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple forward operation implementation.
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
     * Forwards all of a tuple's elements to a functor.
     * @tparam F The functor type to apply.
     * @tparam I The tuple's indeces.
     * @tparam T The tuple's types.
     * @param t The tuple to be forwarded to the functor.
     * @param lambda The functor to forward the tuple to.
     * @return The produced functor result.
     */
    template <typename F, size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR decltype(auto) forward(
        const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& t
      , F&& lambda
    ) {
        return detail::invoke(
            lambda
          , operation::get<I>(t)...
        );
    }

    /**
     * Forwards all of a moving tuple's elements to a functor.
     * @tparam F The functor type to apply.
     * @tparam I The tuple's indeces.
     * @tparam T The tuple's types.
     * @param t The tuple to be forwarded to the functor.
     * @param lambda The functor to forward the tuple to.
     * @return The produced functor result.
     */
    template <typename F, size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR decltype(auto) forward(
        tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>&& t
      , F&& lambda
    ) {
        return detail::invoke(
            lambda
          , operation::get<I>(std::forward<decltype(t)>(t))...
        );
    }

    /**
     * Macro for forwarding a generic function that cannot be directly cast into
     * a function pointer. This macro simply wraps the function in a lambda to forward
     * the tuple contents as parameters to the given function.
     * @param f The function to forward the tuple into.
     */
    #define SUPERTUPLE_FORWARD_GENERIC_FUNCTION(f)                             \
      [](auto&&... params) -> decltype(auto) {                                 \
        return (f)(std::forward<decltype(params)>(params)...);                 \
      }

    /**
     * Macro for forwarding a type construction, which can never be cast into a
     * function pointer. This macro simply wraps the constructor in a lambda to
     * forward the tuple contents as constructor parameters.
     * @param T The type to forward the tuple into constructor.
     */
    #define SUPERTUPLE_FORWARD_CONSTRUCTOR(...)                                \
      [](auto&&... params) -> decltype(auto) {                                 \
        return __VA_ARGS__ {std::forward<decltype(params)>(params)...};        \
      }
}

SUPERTUPLE_END_NAMESPACE
