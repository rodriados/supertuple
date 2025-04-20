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
#include <supertuple/detail/tuple.hpp>
#include <supertuple/operation/get.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

namespace detail
{
    /**
     * Zip two generic tuples into a tuple of pairs of combined elements.
     * @tparam T The first tuple type.
     * @tparam U The second tuple type.
     * @param t The first tuple to zip.
     * @param u The second tuple to zip.
     * @return The zip resulting tuple.
     */
    template <typename T, typename U, id_t ...K>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) zip(
        T&& t, U&& u
      , detail::id_sequence_t<K...>
    ) {
        return supertuple::tuple_t(
            supertuple::pair_t<
                typename decltype(access<K>(std::declval<T>()))::element_t
              , typename decltype(access<K>(std::declval<U>()))::element_t>(
                    get<K>(std::forward<T>(t))
                  , get<K>(std::forward<U>(u)))...
        );
    }
}

inline namespace operation
{
    /**
     * Zip two tuples effectively creating a tuple of pairs with elements combined
     * by index from the two original tuples.
     * @tparam I The first tuple index sequence.
     * @tparam J The second tuple index sequence.
     * @tparam T The first tuple element types.
     * @tparam U The second tuple element types.
     * @param t The first tuple to zip.
     * @param u The second tuple to zip.
     * @return The zip resulting tuple.
     */
    template <id_t ...I, id_t ...J, typename ...T, typename ...U>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) zip(
        const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t
      , const detail::tuple_t<detail::id_sequence_t<J...>, U...>& u
    ) {
        constexpr auto A = sizeof...(T), B = sizeof...(U);
        return detail::zip(t, u, detail::make_id_sequence_t<(A < B ? A : B)>());
    }

    /**
     * Zip two moving tuples effectively creating a tuple of pairs with elements
     * combined by index from the two original tuples.
     * @tparam I The first tuple index sequence.
     * @tparam J The second tuple index sequence.
     * @tparam T The first tuple element types.
     * @tparam U The second tuple element types.
     * @param t The first tuple to zip.
     * @param u The second tuple to zip.
     * @return The zip resulting tuple.
     */
    template <id_t ...I, id_t ...J, typename ...T, typename ...U>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) zip(
        detail::tuple_t<detail::id_sequence_t<I...>, T...>&& t
      , detail::tuple_t<detail::id_sequence_t<J...>, U...>&& u
    ) {
        constexpr auto A = sizeof...(T), B = sizeof...(U);
        return detail::zip(
            std::forward<decltype(t)>(t)
          , std::forward<decltype(u)>(u)
          , detail::make_id_sequence_t<(A < B ? A : B)>()
        );
    }
}

SUPERTUPLE_END_NAMESPACE
