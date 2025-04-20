/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple scan operations implementation.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <utility>

#include <supertuple/environment.h>

#include <supertuple/detail/utility.hpp>
#include <supertuple/operation/fold.hpp>
#include <supertuple/operation/head.hpp>
#include <supertuple/operation/last.hpp>
#include <supertuple/operation/append.hpp>
#include <supertuple/operation/prepend.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

inline namespace operation
{
    /**
     * Perform a left-fold scan reduction over a tuple.
     * @tparam F The functor type to fold the tuple with.
     * @tparam B The fold operation base type.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to fold.
     * @param lambda The functor used to fold the tuple with.
     * @param base The folding base value.
     * @return The fold resulting value with intermediate steps.
     */
    template <typename F, typename B, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) scanl(
        const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t
      , F&& lambda, B&& base
    ) {
        return detail::fold(
            [&lambda] (auto&& r, auto&& curr) {
                return append(r, detail::invoke(lambda, last(r), curr)); }
          , t, tuple_t<B>(base)
          , detail::id_sequence_t<I...>()
        );
    }

    /**
     * Perform a left-fold scan reduction without base over a tuple.
     * @tparam F The functor type to fold the tuple with.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to fold.
     * @param lambda The functor used to fold the tuple with.
     * @return The fold resulting value with intermediate steps
     */
    template <typename F, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) scanl(
        const detail::tuple_t<detail::id_sequence_t<0, I...>, T...>& t
      , F&& lambda
    ) {
        return detail::fold(
            [&lambda] (auto&& r, auto&& curr) {
                return append(r, detail::invoke(lambda, last(r), curr)); }
          , t, tuple_t(head(t))
          , detail::id_sequence_t<I...>()
        );
    }

    /**
     * Perform a right-fold scan reduction over a tuple.
     * @tparam F The functor type to fold the tuple with.
     * @tparam B The fold operation base type.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to fold.
     * @param lambda The functor used to fold the tuple with.
     * @param base The folding base value.
     * @return The fold resulting value with intermediate steps.
     */
    template <typename F, typename B, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) scanr(
        const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t
      , F&& lambda, B&& base
    ) {
        return detail::fold(
            [&lambda] (auto&& r, auto&& curr) {
                return prepend(r, detail::invoke(lambda, curr, head(r))); }
          , t, tuple_t<B>(base)
          , detail::id_reverse_sequence_t<I...>()
        );
    }

    /**
     * Performs a right-fold scan reduction without base over a tuple.
     * @tparam F The functor type to fold the tuple with.
     * @tparam I The tuple index sequence.
     * @tparam T The tuple element types.
     * @param t The tuple to fold.
     * @param lambda The functor used to fold the tuple with.
     * @return The fold resulting value with intermediate steps
     */
    template <typename F, id_t ...I, typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) scanr(
        const detail::tuple_t<detail::id_sequence_t<0, I...>, T...>& t
      , F&& lambda
    ) {
        return detail::fold(
            [&lambda] (auto&& r, auto&& curr) {
                return prepend(r, detail::invoke(lambda, curr, head(r))); }
          , t, tuple_t(last(t))
          , detail::id_reverse_sequence_t<(I-1)...>()
        );
    }
}

SUPERTUPLE_END_NAMESPACE
