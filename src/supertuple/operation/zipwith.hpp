/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple zipwith operation implementation.
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
     * Zips two tuples together by combining paired elements with a given functor.
     * Therefore, the resulting tuple does not contain pairs, but the result of
     * each consecutive operation.
     * @tparam F The functor type to combine the values with.
     * @tparam I The tuples' sequence indeces.
     * @tparam T The first tuple's element members types.
     * @tparam U The second tuple's element members types.
     * @param a The first tuple to zip.
     * @param b The second tuple to zip.
     * @param lambda The functor used to combine the elements.
     * @return The resulting tuple.
     */
    template <typename F, size_t ...I, typename ...T, typename ...U>
    SUPERTUPLE_CONSTEXPR decltype(auto) zipwith(
        const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& a
      , const tuple_t<detail::identity_t<std::index_sequence<I...>>, U...>& b
      , F&& lambda
    ) {
        return tuple_t(
            detail::invoke(
                lambda
              , operation::get<I>(a)
              , operation::get<I>(b)
            )...
        );
    }

    /**
     * Zips two moving tuples together by combining paired elements with a given
     * functor. Therefore, the resulting tuple does not contain pairs, but the result
     * of each consecutive operation.
     * @tparam F The functor type to combine the values with.
     * @tparam I The tuples' sequence indeces.
     * @tparam T The first tuple's element members types.
     * @tparam U The second tuple's element members types.
     * @param a The first tuple to zip.
     * @param b The second tuple to zip.
     * @param lambda The functor used to combine the elements.
     * @return The resulting tuple.
     */
    template <typename F, size_t ...I, typename ...T, typename ...U>
    SUPERTUPLE_CONSTEXPR decltype(auto) zipwith(
        tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>&& a
      , tuple_t<detail::identity_t<std::index_sequence<I...>>, U...>&& b
      , F&& lambda
    ) {
        return tuple_t(
            detail::invoke(
                lambda
              , operation::get<I>(std::forward<decltype(a)>(a))
              , operation::get<I>(std::forward<decltype(b)>(b))
            )...
        );
    }
}

SUPERTUPLE_END_NAMESPACE
