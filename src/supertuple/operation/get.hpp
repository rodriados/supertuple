/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple get operation implementation.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <utility>

#include <supertuple/environment.h>
#include <supertuple/detail/leaf.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

inline namespace operation
{
    /**
     * Retrieves the requested tuple leaf and returns its value.
     * @tparam I The requested leaf index.
     * @tparam T The type of the requested leaf member.
     * @param leaf The selected tuple leaf member.
     * @return The leaf's value.
     */
    template <size_t I, typename T>
    SUPERTUPLE_CONSTEXPR T& get(detail::leaf_t<I, T>& leaf) noexcept
    {
        return leaf.value;
    }

    /**
     * Retrieves the requested const-qualified tuple leaf and returns its value.
     * @tparam I The requested leaf index.
     * @tparam T The type of the requested leaf member.
     * @param leaf The selected const-qualified tuple leaf member.
     * @return The const-qualified leaf's value.
     */
    template <size_t I, typename T>
    SUPERTUPLE_CONSTEXPR const T& get(const detail::leaf_t<I, T>& leaf) noexcept
    {
        return leaf.value;
    }

    /**
     * Retrieves the requested tuple leaf and moves its contents.
     * @tparam I The requested leaf index.
     * @tparam T The type of the requested leaf member.
     * @param leaf The selected tuple leaf member.
     * @return The leaf value's move reference.
     */
    template <size_t I, typename T>
    SUPERTUPLE_CONSTEXPR decltype(auto) get(detail::leaf_t<I, T>&& leaf) noexcept
    {
        return std::forward<decltype(leaf.value)>(leaf.value);
    }
}

SUPERTUPLE_END_NAMESPACE
