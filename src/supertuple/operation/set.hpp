/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple set operation implementation.
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
     * Moves a value into a tuple leaf by its index.
     * @tparam I The requested leaf index.
     * @tparam T The type of requested leaf member.
     * @tparam V The type of value to be moved into leaf.
     * @param leaf The selected tuple leaf member.
     * @param value The value to move into the leaf.
     */
    template <size_t I, typename T, typename V>
    SUPERTUPLE_INLINE void set(detail::leaf_t<I, T>& leaf, V&& value)
    {
        leaf = std::forward<decltype(value)>(value);
    }

    /**
     * Moves a value into a tuple leaf by its unique type.
     * @tparam T The unique type of requested leaf member.
     * @tparam I The requested leaf index.
     * @tparam V The type of value to be moved into leaf.
     * @param leaf The selected tuple leaf member.
     * @param value The value to move into the leaf.
     */
    template <typename T, size_t I, typename U>
    SUPERTUPLE_INLINE void set(detail::leaf_t<I, T>& leaf, U&& value)
    {
        leaf = std::forward<decltype(value)>(value);
    }
}

SUPERTUPLE_END_NAMESPACE
