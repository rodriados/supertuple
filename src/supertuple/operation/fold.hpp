/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple fold operations implementation.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <utility>

#include <supertuple/environment.h>

#include <supertuple/detail/utility.hpp>
#include <supertuple/detail/tuple.hpp>
#include <supertuple/operation/get.hpp>
#include <supertuple/operation/head.hpp>
#include <supertuple/operation/last.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

namespace detail
{
    /**
     * The base case for the fold algorithm over a tuple.
     * @tparam T The reducing tuple type.
     * @tparam F The functor type to fold the tuple with.
     * @tparam B The reduction base and result value type.
     * @param base The fold-operation base value.
     * @return The result of the fold-operation.
     */
    template <typename T, typename F, typename B>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) fold(
        T&&, F&&, B&& base
      , detail::id_sequence_t<>
    ) {
        return (B) base;
    }

    /**
     * A step of a fold-operation algorithm over a tuple.
     * @tparam T The reducing tuple type.
     * @tparam F The functor type to fold the tuple with.
     * @tparam B The reduction base and result value type.
     * @tparam I The tuple index to act upon.
     * @tparam J The tuple remaining index sequence.
     * @param t The tuple to be folded.
     * @param lambda The functor to fold the tuple with.
     * @param base The fold-operation base value.
     * @return The result of the fold-operation.
     */
    template <typename T, typename F, typename B, id_t I, id_t ...J>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) fold(
        T&& t, F&& lambda, B&& base
      , detail::id_sequence_t<I, J...>
    ) {
        return detail::fold(
            t, lambda
          , detail::invoke(lambda, base, get<I>(t))
          , detail::id_sequence_t<J...>()
        );
    }
}

inline namespace operation
{
    /**
     * Perform a left-fold reduction over a tuple.
     * @tparam F The functor type to fold the tuple with.
     * @tparam B The fold operation base type.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to fold.
     * @param lambda The functor to fold the tuple with.
     * @param base The folding base value.
     * @return The fold resulting value.
     */
    template <typename F, typename B, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) foldl(
        const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t
      , F&& lambda
      , B&& base
    ) {
        return detail::fold(
            t, lambda
          , std::forward<B>(base)
          , detail::id_sequence_t<I...>()
        );
    }

    /**
     * Perform a left-fold reduction without base over a tuple.
     * @tparam F The functor type to fold the tuple with.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to fold.
     * @param lambda The functor to fold the tuple with.
     * @return The fold resulting value.
     */
    template <typename F, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) foldl(
        const detail::tuple_t<detail::id_sequence_t<0, I...>, T...>& t
      , F&& lambda
    ) {
        return detail::fold(
            t, lambda
          , operation::head(t)
          , detail::id_sequence_t<I...>()
        );
    }

    /**
     * Perform a right-fold reduction over a tuple.
     * @tparam F The functor type to fold the tuple with.
     * @tparam B The fold operation base type.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to fold.
     * @param lambda The functor to fold the tuple with.
     * @param base The folding base value.
     * @return The fold resulting value.
     */
    template <typename F, typename B, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) foldr(
        const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t
      , F&& lambda
      , B&& base
    ) {
        constexpr id_t J = sizeof...(I);
        return detail::fold(
            t, detail::flip(lambda)
          , std::forward<B>(base)
          , detail::id_sequence_t<(J-I-1)...>()
        );
    }

    /**
     * Perform a right-fold reduction without base over a tuple.
     * @tparam F The functor type to fold the tuple with.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to fold.
     * @param lambda The functor to fold the tuple with.
     * @return The fold resulting value.
     */
    template <typename F, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) foldr(
        const detail::tuple_t<detail::id_sequence_t<0, I...>, T...>& t
      , F&& lambda
    ) {
        constexpr id_t J = 1 + sizeof...(I);
        return detail::fold(
            t, detail::flip(lambda)
          , operation::last(t)
          , detail::id_sequence_t<(J-I-1)...>()
        );
    }
}

SUPERTUPLE_END_NAMESPACE
