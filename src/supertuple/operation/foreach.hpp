/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple foreach and rforeach operation implementation.
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
     * Iterates over a tuple's elements using a functor.
     * @tparam F The functor type to apply.
     * @tparam A The types of extra arguments.
     * @tparam I The tuple's indeces.
     * @tparam T The tuple's types.
     * @param t The tuple to iterate over.
     * @param lambda The functor to apply to the tuple.
     * @param args The remaining functor arguments.
     */
    template <typename F, typename ...A, size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR void foreach(
        tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& t
      , F&& lambda
      , A&&... args
    ) {
        ((void) detail::invoke(
            lambda
          , operation::get<I>(t)
          , std::forward<decltype(args)>(args)...
        ), ...);
    }

    /**
     * Iterates over a const-qualified tuple's elements using a functor.
     * @tparam F The functor type to apply.
     * @tparam A The types of extra arguments.
     * @tparam I The tuple's indeces.
     * @tparam T The tuple's types.
     * @param t The tuple to iterate over.
     * @param lambda The functor to apply to the tuple.
     * @param args The remaining functor arguments.
     */
    template <typename F, typename ...A, size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR void foreach(
        const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& t
      , F&& lambda
      , A&&... args
    ) {
        ((void) detail::invoke(
            lambda
          , operation::get<I>(t)
          , std::forward<decltype(args)>(args)...
        ), ...);
    }

    /**
     * Iterates over a moving tuple's elements using a functor.
     * @tparam F The functor type to apply.
     * @tparam A The types of extra arguments.
     * @tparam I The tuple's indeces.
     * @tparam T The tuple's types.
     * @param t The tuple to iterate over.
     * @param lambda The functor to apply to the tuple.
     * @param args The remaining functor arguments.
     */
    template <typename F, typename ...A, size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR void foreach(
        tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>&& t
      , F&& lambda
      , A&&... args
    ) {
        ((void) detail::invoke(
            lambda
          , operation::get<I>(std::forward<decltype(t)>(t))
          , std::forward<decltype(args)>(args)...
        ), ...);
    }

    /**
     * Iterates over a tuple's elements, in reverse, using a functor.
     * @tparam F The functor type to apply.
     * @tparam A The types of extra arguments.
     * @tparam I The tuple's indeces.
     * @tparam T The tuple's types.
     * @param t The tuple to iterate over.
     * @param lambda The functor to apply to the tuple.
     * @param args The remaining functor arguments.
     */
    template <typename F, typename ...A, size_t ...I, typename ...T, size_t J = sizeof...(I)>
    SUPERTUPLE_CONSTEXPR void rforeach(
        tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& t
      , F&& lambda
      , A&&... args
    ) {
        ((void) detail::invoke(
            lambda
          , operation::get<J-I-1>(t)
          , std::forward<decltype(args)>(args)...
        ), ...);
    }

    /**
     * Iterates over a const-qualified tuple's elements, in reverse, using a functor.
     * @tparam F The functor type to apply.
     * @tparam A The types of extra arguments.
     * @tparam I The tuple's indeces.
     * @tparam T The tuple's types.
     * @param t The tuple to iterate over.
     * @param lambda The functor to apply to the tuple.
     * @param args The remaining functor arguments.
     */
    template <typename F, typename ...A, size_t ...I, typename ...T, size_t J = sizeof...(I)>
    SUPERTUPLE_CONSTEXPR void rforeach(
        const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& t
      , F&& lambda
      , A&&... args
    ) {
        ((void) detail::invoke(
            lambda
          , operation::get<J-I-1>(t)
          , std::forward<decltype(args)>(args)...
        ), ...);
    }

    /**
     * Iterates over a moving tuple's elements, in reverse, using a functor.
     * @tparam F The functor type to apply.
     * @tparam A The types of extra arguments.
     * @tparam I The tuple's indeces.
     * @tparam T The tuple's types.
     * @param t The tuple to iterate over.
     * @param lambda The functor to apply to the tuple.
     * @param args The remaining functor arguments.
     */
    template <typename F, typename ...A, size_t ...I, typename ...T, size_t J = sizeof...(I)>
    SUPERTUPLE_CONSTEXPR void rforeach(
        tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>&& t
      , F&& lambda
      , A&&... args
    ) {
        ((void) detail::invoke(
            lambda
          , operation::get<J-I-1>(std::forward<decltype(t)>(t))
          , std::forward<decltype(args)>(args)...
        ), ...);
    }
}

SUPERTUPLE_END_NAMESPACE
