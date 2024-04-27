/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple fold operations implementation.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <utility>

#include <supertuple/environment.h>
#include <supertuple/tuple.hpp>

#include <supertuple/detail/utility.hpp>
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
    SUPERTUPLE_CONSTEXPR decltype(auto) fold(
        T&&, F&&, B&& base
      , std::index_sequence<>
    ) {
        return std::remove_reference_t<B>(base);
    }

    /**
     * A step of a fold-operation algorithm over a tuple.
     * @tparam T The reducing tuple type.
     * @tparam F The functor type to fold the tuple with.
     * @tparam B The reduction base and result value type.
     * @tparam I The tuple index to act upon.
     * @tparam J The tuple sequence indeces.
     * @param t The tuple to be folded.
     * @param lambda The functor used to create the new elements.
     * @param base The fold-operation base value.
     * @return The result of the fold-operation.
     */
    template <typename T, typename F, typename B, size_t I, size_t ...J>
    SUPERTUPLE_CONSTEXPR decltype(auto) fold(
        T&& t, F&& lambda, B&& base
      , std::index_sequence<I, J...>
    ) {
        return detail::fold(
            t, lambda
          , detail::invoke(lambda, base, operation::get<I>(t))
          , std::index_sequence<J...>()
        );
    }
}

inline namespace operation
{
    /**
     * Performs a left-fold reduction over a tuple.
     * @tparam F The functor type to fold the tuple with.
     * @tparam B The fold operation base type.
     * @tparam I The tuple sequence indeces.
     * @tparam T The tuple's element members types.
     * @param t The tuple to fold.
     * @param lambda The functor used to fold the tuple with.
     * @param base The folding base value.
     * @return The fold resulting value.
     */
    template <typename F, typename B, size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR decltype(auto) foldl(
        const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& t
      , F&& lambda
      , B&& base
    ) {
        return detail::fold(
            t, lambda, base
          , std::index_sequence<I...>()
        );
    }

    /**
     * Performs a left-fold reduction without base over a tuple.
     * @tparam F The functor type to fold the tuple with.
     * @tparam I The tuple sequence indeces.
     * @tparam T The tuple's element members types.
     * @param t The tuple to fold.
     * @param lambda The functor used to fold the tuple with.
     * @return The fold resulting value.
     */
    template <typename F, size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR decltype(auto) foldl(
        const tuple_t<detail::identity_t<std::index_sequence<0, I...>>, T...>& t
      , F&& lambda
    ) {
        return detail::fold(
            t, lambda, operation::head(t)
          , std::index_sequence<I...>()
        );
    }

    /**
     * Performs a right-fold reduction over a tuple.
     * @tparam F The functor type to fold the tuple with.
     * @tparam B The fold operation base type.
     * @tparam I The tuple sequence indeces.
     * @tparam T The tuple's element members types.
     * @param t The tuple to fold.
     * @param lambda The functor used to fold the tuple with.
     * @param base The folding base value.
     * @return The fold resulting value.
     */
    template <typename F, typename B, size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR decltype(auto) foldr(
        const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& t
      , F&& lambda
      , B&& base
    ) {
        constexpr size_t J = sizeof...(I);
        return detail::fold(
            t, detail::flip(lambda), base
          , std::index_sequence<(J-I-1)...>()
        );
    }

    /**
     * Performs a right-fold reduction without base over a tuple.
     * @tparam F The functor type to fold the tuple with.
     * @tparam I The tuple sequence indeces.
     * @tparam T The tuple's element members types.
     * @param t The tuple to fold.
     * @param lambda The functor used to fold the tuple with.
     * @return The fold resulting value.
     */
    template <typename F, size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR decltype(auto) foldr(
        const tuple_t<detail::identity_t<std::index_sequence<0, I...>>, T...>& t
      , F&& lambda
    ) {
        constexpr size_t J = 1 + sizeof...(I);
        return detail::fold(
            t, detail::flip(lambda), operation::last(t)
          , std::index_sequence<(J-I-1)...>()
        );
    }
}

SUPERTUPLE_END_NAMESPACE
