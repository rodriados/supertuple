/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The casting functions to and from standard C++ tuples.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2025-present Rodrigo Siqueira
 */
#pragma once

#include <tuple>
#include <utility>

#include <supertuple/environment.h>
#include <supertuple/tuple.hpp>
#include <supertuple/detail/utility.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

namespace detail
{
    /**
     * Convert a standard C++ tuple into a supertuple instance.
     * @tparam T The standard C++ tuple type.
     * @param t The source standard C++ tuple instance.
     * @return The new supertuple instance.
     */
    template <typename T, id_t ...K>
    SUPERTUPLE_CONSTEXPR decltype(auto) from_std(T&& t, detail::id_sequence_t<K...>)
    {
        using U = std::remove_cv_t<std::remove_reference_t<T>>;
        return supertuple::tuple_t<std::tuple_element_t<K, U>...>(
            std::get<K>(std::forward<decltype(t)>(t))...);
    }

    /**
     * Convert a supertuple into a standard C++ tuple instance.
     * @tparam T The supertuple type.
     * @param t The source supertuple instance.
     * @return The new standard C++ tuple instance.
     */
    template <typename T, id_t ...K>
    SUPERTUPLE_CONSTEXPR decltype(auto) to_std(T&& t, detail::id_sequence_t<K...>)
    {
        using U = std::remove_cv_t<std::remove_reference_t<T>>;
        return std::tuple<std::tuple_element_t<K, U>...>(
            supertuple::get<K>(std::forward<decltype(t)>(t))...);
    }
}

/**
 * Convert a standard C++ tuple into a supertuple.
 * @tparam T The tuple element types.
 * @param t The source standard C++ tuple instance.
 * @return The new supertuple instance.
 */
template <typename ...T>
SUPERTUPLE_CONSTEXPR decltype(auto) from_std(const std::tuple<T...>& t)
{
    return detail::from_std(t, detail::make_id_sequence_t<sizeof...(T)>());
}

/**
 * Convert a moving standard C++ tuple into a supertuple.
 * @tparam T The tuple element types.
 * @param t The source standard C++ tuple instance.
 * @return The new supertuple instance.
 */
template <typename ...T>
SUPERTUPLE_CONSTEXPR decltype(auto) from_std(std::tuple<T...>&& t)
{
    return detail::from_std(
        std::forward<decltype(t)>(t)
      , detail::make_id_sequence_t<sizeof...(T)>()
    );
}

/**
 * Convert a supertuple into a standard C++ tuple.
 * @tparam T The tuple element types.
 * @param t The source supertuple instance.
 * @return The new standard C++ tuple instance.
 */
template <typename ...T>
SUPERTUPLE_CONSTEXPR decltype(auto) to_std(const tuple_t<T...>& t)
{
    return detail::to_std(t, detail::make_id_sequence_t<sizeof...(T)>());
}

/**
 * Convert a moving supertuple into a standard C++ tuple.
 * @tparam T The tuple element types.
 * @param t The source supertuple instance.
 * @return The new standard C++ tuple instance.
 */
template <typename ...T>
SUPERTUPLE_CONSTEXPR decltype(auto) to_std(tuple_t<T...>&& t)
{
    return detail::to_std(
        std::forward<decltype(t)>(t)
      , detail::make_id_sequence_t<sizeof...(T)>()
    );
}

SUPERTUPLE_END_NAMESPACE
