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
#include <supertuple/operation/get.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

inline namespace operation
{
    /**
     * Applies a functor to all of a tuple's elements.
     * @tparam F The functor type to apply.
     * @tparam A The types of extra arguments.
     * @tparam I The tuple's indeces.
     * @tparam T The tuple's types.
     * @param t The tuple to apply functor to.
     * @param lambda The functor to apply to the tuple.
     * @param args The remaining functor arguments.
     * @return The new transformed tuple.
     */
    template <typename F, typename ...A, size_t ...I, typename ...T>
    SUPERTUPLE_CUDA_ENABLED inline constexpr decltype(auto) apply(
        const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& t
      , F&& lambda
      , A&&... args
    ) {
        return tuple_t(detail::invoke(
            lambda
          , operation::get<I>(t)
          , std::forward<decltype(args)>(args)...
        )...);
    }

    /**
     * Applies a functor to all of a moving tuple's elements.
     * @tparam F The functor type to apply.
     * @tparam A The types of extra arguments.
     * @tparam I The tuple's indeces.
     * @tparam T The tuple's types.
     * @param t The tuple to apply functor to.
     * @param lambda The functor to apply to the tuple.
     * @param args The remaining functor arguments.
     * @return The new transformed tuple.
     */
    template <typename F, typename ...A, size_t ...I, typename ...T>
    SUPERTUPLE_CUDA_ENABLED inline constexpr decltype(auto) apply(
        tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>&& t
      , F&& lambda
      , A&&... args
    ) {
        return tuple_t(detail::invoke(
            lambda
          , operation::get<I>(std::forward<decltype(t)>(t))
          , std::forward<decltype(args)>(args)...
        )...);
    }
}

SUPERTUPLE_END_NAMESPACE
