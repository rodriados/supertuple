/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple scan operations implementation.
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
#include <supertuple/operation/prepend.hpp>
#include <supertuple/operation/reverse.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

namespace detail
{
    /**
     * The base case for the scan algorithm over a tuple.
     * @tparam T The reducing tuple type.
     * @tparam F The functor type to fold the tuple with.
     * @tparam B The reduction base and result value type.
     * @param base The scan-operation base value.
     * @return The result of the scan-operation.
     */
    template <typename T, typename F, typename B>
    SUPERTUPLE_CONSTEXPR decltype(auto) scan(
        T&&, F&&, B&& base
      , std::index_sequence<>
    ) {
        return tuple_t<B>(base);
    }

    /**
     * A step of a scan-operation algorithm over a tuple.
     * @tparam T The reducing tuple type.
     * @tparam F The functor type to fold the tuple with.
     * @tparam B The reduction base and result value type.
     * @tparam I The tuple index to act upon.
     * @tparam J The tuple sequence indeces.
     * @param t The tuple to be folded.
     * @param lambda The functor used to create the new elements.
     * @param base The scan-operation base value.
     * @return The result of the scan-operation.
     */
    template <typename T, typename F, typename B, size_t I, size_t ...J>
    SUPERTUPLE_CONSTEXPR decltype(auto) scan(
         T&& t, F&& lambda, B&& base
      , std::index_sequence<I, J...>
    ) {
        return operation::prepend(
            detail::scan(
                t, lambda
              , detail::invoke(lambda, base, operation::get<I>(t))
              , std::index_sequence<J...>())
          , std::remove_reference_t<B>(base)
        );
    }
}

inline namespace operation
{
    /**
     * Performs a left-scan reduction with over a tuple.
     * @tparam F The functor type to fold the tuple with.
     * @tparam B The fold operation base type.
     * @tparam I The tuple sequence indeces.
     * @tparam T The tuple's element members types.
     * @param t The tuple to fold.
     * @param lambda The functor used to fold the tuple with.
     * @param base The folding base value.
     * @return The fold result with intermediate steps.
     */
    template <typename F, typename B, size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR decltype(auto) scanl(
        const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& t
      , F&& lambda
      , B&& base
    ) {
        return detail::scan(
            t, lambda, base
          , std::index_sequence<I...>()
        );
    }

    /**
     * Performs a left-scan reduction without base over a tuple.
     * @tparam F The functor type to fold the tuple with.
     * @tparam I The tuple sequence indeces.
     * @tparam T The tuple's element members types.
     * @param t The tuple to fold.
     * @param lambda The functor used to fold the tuple with.
     * @return The fold result with intermediate steps.
     */
    template <typename F, size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR decltype(auto) scanl(
        const tuple_t<detail::identity_t<std::index_sequence<0, I...>>, T...>& t
      , F&& lambda
    ) {
        return detail::scan(
            t, lambda, operation::head(t)
          , std::index_sequence<I...>()
        );
    }

    /**
     * Performs a right-scan reduction with over a tuple.
     * @tparam F The functor type to fold the tuple with.
     * @tparam B The fold operation base type.
     * @tparam I The tuple sequence indeces.
     * @tparam T The tuple's element members types.
     * @param t The tuple to fold.
     * @param lambda The functor used to fold the tuple with.
     * @param base The folding base value.
     * @return The fold result with intermediate steps.
     */
    template <typename F, typename B, size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR decltype(auto) scanr(
        const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& t
      , F&& lambda
      , B&& base
    ) {
        constexpr size_t J = sizeof...(I);
        return operation::reverse(
            detail::scan(
                t, detail::flip(lambda), base
              , std::index_sequence<(J-I-1)...>())
        );
    }

    /**
     * Performs a right-scan reduction without base over a tuple.
     * @tparam F The functor type to fold the tuple with.
     * @tparam I The tuple sequence indeces.
     * @tparam T The tuple's element members types.
     * @param t The tuple to fold.
     * @param lambda The functor used to fold the tuple with.
     * @return The fold result with intermediate steps.
     */
    template <typename F, size_t ...I, typename ...T>
    SUPERTUPLE_CONSTEXPR decltype(auto) scanr(
        const tuple_t<detail::identity_t<std::index_sequence<0, I...>>, T...>& t
      , F&& lambda
    ) {
        constexpr size_t J = 1 + sizeof...(I);
        return operation::reverse(
            detail::scan(
                t, detail::flip(lambda), operation::last(t)
              , std::index_sequence<(J-I-1)...>())
        );
    }
}

SUPERTUPLE_END_NAMESPACE
