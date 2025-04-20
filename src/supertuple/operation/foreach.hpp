/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple foreach and rforeach operation implementation.
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

namespace detail
{
    /**
     * Iterate over the elements of a tuple in the given sequence order.
     * @tparam F The functor type to apply.
     * @tparam T The generic tuple type.
     * @tparam A The functor extra arguments types.
     * @tparam K The tuple index sequence order.
     * @param lambda The functor to apply to the tuple.
     * @param t The tuple to iterate over.
     * @param args The extra functor arguments.
     */
    template <typename F, typename T, typename ...A, id_t ...K>
    SUPERTUPLE_CUDA_INLINE decltype(auto) foreach(
        F&& lambda, T&& t
      , detail::id_sequence_t<K...>
      , A&&... args
    ) {
        ((void) detail::invoke(
            lambda
          , get<K>(std::forward<T>(t))
          , std::forward<A>(args)...
        ), ...);
    }
}

inline namespace operation
{
    /**
     * Iterate over the elements of a tuple using a functor.
     * @tparam F The functor type to apply.
     * @tparam A The functor extra arguments types.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to iterate over.
     * @param lambda The functor to apply to the tuple.
     * @param args The extra functor arguments.
     */
    template <typename F, typename ...A, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_INLINE void foreach(
        detail::tuple_t<detail::id_sequence_t<I...>, T...>& t
      , F&& lambda, A&&... args
    ) {
        detail::foreach(
            lambda, t
          , detail::id_sequence_t<I...>()
          , std::forward<A>(args)...
        );
    }

    /**
     * Iterate over the elements of a const-qualified tuple using a functor.
     * @tparam F The functor type to apply.
     * @tparam A The functor extra arguments types.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to iterate over.
     * @param lambda The functor to apply to the tuple.
     * @param args The extra functor arguments.
     */
    template <typename F, typename ...A, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_INLINE void foreach(
        const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t
      , F&& lambda, A&&... args
    ) {
        detail::foreach(
            lambda, t
          , detail::id_sequence_t<I...>()
          , std::forward<A>(args)...
        );
    }

    /**
     * Iterate over the elements of a moving tuple using a functor.
     * @tparam F The functor type to apply.
     * @tparam A The functor extra arguments types.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to iterate over.
     * @param lambda The functor to apply to the tuple.
     * @param args The extra functor arguments.
     */
    template <typename F, typename ...A, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_INLINE void foreach(
        detail::tuple_t<detail::id_sequence_t<I...>, T...>&& t
      , F&& lambda, A&&... args
    ) {
        detail::foreach(
            lambda
          , std::forward<decltype(t)>(t)
          , detail::id_sequence_t<I...>()
          , std::forward<A>(args)...
        );
    }

    /**
     * Iterate over the elements of a tuple in reverse using a functor.
     * @tparam F The functor type to apply.
     * @tparam A The functor extra arguments types.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to iterate over in reverse.
     * @param lambda The functor to apply to the tuple.
     * @param args The extra functor arguments.
     */
    template <typename F, typename ...A, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_INLINE void rforeach(
        detail::tuple_t<detail::id_sequence_t<I...>, T...>& t
      , F&& lambda, A&&... args
    ) {
        detail::foreach(
            lambda, t
          , detail::id_reverse_sequence_t<I...>()
          , std::forward<A>(args)...
        );
    }

    /**
     * Iterate over the elements of a const-qualified tuple in reverse using a functor.
     * @tparam F The functor type to apply.
     * @tparam A The functor extra arguments types.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to iterate over.
     * @param lambda The functor to apply to the tuple.
     * @param args The extra functor arguments.
     */
    template <typename F, typename ...A, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_INLINE void rforeach(
        const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t
      , F&& lambda, A&&... args
    ) {
        detail::foreach(
            lambda, t
          , detail::id_reverse_sequence_t<I...>()
          , std::forward<A>(args)...
        );
    }

    /**
     * Iterate over the elements of a moving tuple in reverse using a functor.
     * @tparam F The functor type to apply.
     * @tparam A The functor extra arguments types.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to iterate over.
     * @param lambda The functor to apply to the tuple.
     * @param args The extra functor arguments.
     */
    template <typename F, typename ...A, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_INLINE void rforeach(
        detail::tuple_t<detail::id_sequence_t<I...>, T...>&& t
      , F&& lambda, A&&... args
    ) {
        detail::foreach(
            lambda
          , std::forward<decltype(t)>(t)
          , detail::id_reverse_sequence_t<I...>()
          , std::forward<A>(args)...
        );
    }
}

SUPERTUPLE_END_NAMESPACE
