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
#include <supertuple/detail/tuple.hpp>
#include <supertuple/operation/get.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

namespace detail
{
    /**
     * Zip two generic tuples combining paired elements with a functor.
     * @tparam F The functor type to combine elements with.
     * @tparam T The first tuple type.
     * @tparam U The second tuple type.
     * @param lambda The functor to combine the elements with.
     * @param t The first tuple to zip.
     * @param u The second tuple to zip.
     * @return The zip resulting tuple.
     */
    template <typename F, typename T, typename U, id_t ...K>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) zipwith(
        F&& lambda, T&& t, U&& u
      , detail::id_sequence_t<K...>
    ) {
        return supertuple::tuple_t(
            detail::invoke(
                lambda
              , get<K>(std::forward<T>(t))
              , get<K>(std::forward<U>(u)))...
        );
    }
}

inline namespace operation
{
    /**
     * Zip two tuples by combining elements pairwise with a given functor.
     * @tparam F The functor type to combine elements with.
     * @tparam I The first tuple index sequence.
     * @tparam J The second tuple index sequence.
     * @tparam T The first tuple element types.
     * @tparam U The second tuple element types.
     * @param t The first tuple to zip.
     * @param u The second tuple to zip.
     * @param lambda The functor to combine the elements with.
     * @return The resulting tuple.
     */
    template <typename F, id_t ...I, id_t ...J, typename ...T, typename ...U>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) zipwith(
        const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t
      , const detail::tuple_t<detail::id_sequence_t<J...>, U...>& u
      , F&& lambda
    ) {
        constexpr auto A = sizeof...(T), B = sizeof...(U);
        return detail::zipwith(lambda, t, u, detail::make_id_sequence_t<(A < B ? A : B)>());
    }

    /**
     * Zip two moving tuples by combining elements pairwise with a given functor.
     * @tparam F The functor type to combine elements with.
     * @tparam I The first tuple index sequence.
     * @tparam J The second tuple index sequence.
     * @tparam T The first tuple element types.
     * @tparam U The second tuple element types.
     * @param t The first tuple to zip.
     * @param u The second tuple to zip.
     * @param lambda The functor to combine the elements with.
     * @return The resulting tuple.
     */
    template <typename F, id_t ...I, id_t ...J, typename ...T, typename ...U>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) zipwith(
        detail::tuple_t<detail::id_sequence_t<I...>, T...>&& t
      , detail::tuple_t<detail::id_sequence_t<J...>, U...>&& u
      , F&& lambda
    ) {
        constexpr auto A = sizeof...(T), B = sizeof...(U);
        return detail::zipwith(
            lambda
          , std::forward<decltype(t)>(t)
          , std::forward<decltype(u)>(u)
          , detail::make_id_sequence_t<(A < B ? A : B)>()
        );
    }
}

SUPERTUPLE_END_NAMESPACE
