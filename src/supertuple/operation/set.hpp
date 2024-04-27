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
     * Modifies a tuple leaf by moving a value into it.
     * @tparam I The requested leaf index.
     * @tparam T The type of requested leaf member.
     * @param leaf The selected tuple leaf member.
     * @param value The value to move into the leaf.
     */
    template <size_t I, typename T, typename U>
    SUPERTUPLE_INLINE void set(detail::leaf_t<I, T>& leaf, U&& value)
    {
        leaf.value = std::forward<decltype(value)>(value);
    }
}

SUPERTUPLE_END_NAMESPACE
