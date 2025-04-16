/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple forward operation implementation.
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
     * Forwards all elements of a tuple as functor parameters.
     * @tparam F The functor type to forward tuple to.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to forward into the functor.
     * @param lambda The functor to forward tuple as parameters to.
     * @return The produced functor result.
     */
    template <typename F, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) forward(
        const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t
      , F&& lambda
    ) {
        return detail::invoke(lambda, get<I>(t)...);
    }

    /**
     * Forwards all elements of a moving tuple as functor parameters.
     * @tparam F The functor type to forward tuple to.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to forward into the functor.
     * @param lambda The functor to forward tuple as parameters to.
     * @return The produced functor result.
     */
    template <typename F, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) forward(
        detail::tuple_t<detail::id_sequence_t<I...>, T...>&& t
      , F&& lambda
    ) {
        return detail::invoke(
            lambda
          , get<I>(std::forward<decltype(t)>(t))...
        );
    }
}

SUPERTUPLE_END_NAMESPACE

/**
 * Macro for forwarding a generic function that cannot be directly cast into a function
 * pointer. This macro simply wraps the function in a lambda to forward the tuple
 * contents as parameters to the given function.
 * @param f The function to forward the tuple into.
 */
#define SUPERTUPLE_FORWARD_GENERIC_FUNCTION(f)              \
  [](auto&&... args) -> decltype(auto) {                    \
    return (f)(std::forward<decltype(args)>(args)...);      \
  }

/**
 * Macro for forwarding a type construction, which can never be cast into a function
 * pointer. This macro simply wraps the constructor in a lambda to forward the tuple
 * contents as constructor parameters.
 * @param T The type to forward the tuple into constructor.
 */
#define SUPERTUPLE_FORWARD_CONSTRUCTOR(T)                   \
  [](auto&&... args) -> decltype(auto) {                    \
    return T {std::forward<decltype(args)>(args)...};       \
  }
