/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple apply operation implementation.
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
     * Apply a functor to all elements of a tuple.
     * @tparam F The functor type to apply.
     * @tparam A The types of extra functor arguments.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to apply functor to.
     * @param lambda The functor to apply to the tuple.
     * @param args The extra functor arguments.
     * @return The new transformed tuple.
     */
    template <typename F, typename ...A, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) apply(
        const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t
      , F&& lambda, A&&... args
    ) {
        return tuple_t(
            detail::invoke(
                lambda, get<I>(t)
              , std::forward<A>(args)...
            )...
        );
    }

    /**
     * Apply a functor to all elements of a moving tuple.
     * @tparam F The functor type to apply.
     * @tparam A The types of extra functor arguments.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to apply functor to.
     * @param lambda The functor to apply to the tuple.
     * @param args The extra functor arguments.
     * @return The new transformed tuple.
     */
    template <typename F, typename ...A, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) apply(
        detail::tuple_t<detail::id_sequence_t<I...>, T...>&& t
      , F&& lambda, A&&... args
    ) {
        return tuple_t(
            detail::invoke(
                lambda
              , get<I>(std::forward<decltype(t)>(t))
              , std::forward<A>(args)...
            )...
        );
    }
}

SUPERTUPLE_END_NAMESPACE
