/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple set operation implementation.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <utility>

#include <supertuple/environment.h>
#include <supertuple/detail/utility.hpp>
#include <supertuple/detail/node.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

inline namespace operation
{
    /**
     * Move a value into a tuple node by its index.
     * @tparam I The requested node index.
     * @tparam T The type of requested node member.
     * @tparam V The type of value to be moved into node.
     * @param node The selected tuple node member.
     * @param value The value to move into the node.
     */
    template <id_t I, typename T, typename V>
    SUPERTUPLE_CUDA_INLINE void set(detail::node_t<I, T>& node, V&& value)
    {
        node = std::forward<V>(value);
    }

    /**
     * Move a value into a tuple node by its unique type.
     * @tparam T The unique type of requested node member.
     * @tparam I The requested node index.
     * @tparam V The type of value to be moved into node.
     * @param node The selected tuple node member.
     * @param value The value to move into the node.
     */
    template <typename T, id_t I, typename V>
    SUPERTUPLE_CUDA_INLINE void set(detail::node_t<I, T>& node, V&& value)
    {
        node = std::forward<V>(value);
    }
}

SUPERTUPLE_END_NAMESPACE
