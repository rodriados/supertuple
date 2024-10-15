/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple zip operation implementation.
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
     * Zips two tuples together eventually creating a tuple of pairs with types
     * intercalated from the two original tuples.
     * @tparam I The tuples' sequence indeces.
     * @tparam T The first tuple's element members types.
     * @tparam U The second tuple's element members types.
     * @param a The first tuple to zip.
     * @param b The second tuple to zip.
     * @return The resulting zipped tuple.
     */
    template <size_t ...I, typename ...T, typename ...U>
    SUPERTUPLE_CONSTEXPR decltype(auto) zip(
        const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& a
      , const tuple_t<detail::identity_t<std::index_sequence<I...>>, U...>& b
    ) {
        return tuple_t(
            pair_t<T, U>(
                operation::get<I>(a)
              , operation::get<I>(b)
            )...
        );
    }

    /**
     * Zips two moving tuples together eventually creating a tuple of pairs with
     * types intercalated from the two original tuples.
     * @tparam I The tuples' sequence indeces.
     * @tparam T The first tuple's element members types.
     * @tparam U The second tuple's element members types.
     * @param a The first tuple to zip.
     * @param b The second tuple to zip.
     * @return The resulting zipped tuple.
     */
    template <size_t ...I, typename ...T, typename ...U>
    SUPERTUPLE_CONSTEXPR decltype(auto) zip(
        tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>&& a
      , tuple_t<detail::identity_t<std::index_sequence<I...>>, U...>&& b
    ) {
        return tuple_t(
            pair_t<T, U>(
                operation::get<I>(std::forward<decltype(a)>(a))
              , operation::get<I>(std::forward<decltype(b)>(b))
            )...
        );
    }
}

SUPERTUPLE_END_NAMESPACE
