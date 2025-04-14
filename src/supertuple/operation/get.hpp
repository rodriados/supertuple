/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple get operation implementation.
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
     * Retrieve a tuple node by its index and returns its value.
     * @tparam I The requested node index.
     * @tparam T The type of the requested node member.
     * @param node The selected tuple node member.
     * @return The node element reference.
     */
    template <id_t I, typename T>
    SUPERTUPLE_CUDA_CONSTEXPR T& get(detail::node_t<I, T>& node) noexcept
    {
        return node;
    }

    /**
     * Retrieve a tuple node by its unique type and returns its value.
     * @tparam T The type of the requested node member.
     * @tparam I The requested node index.
     * @param node The selected tuple node member.
     * @return The node element reference.
     */
    template <typename T, id_t I>
    SUPERTUPLE_CUDA_CONSTEXPR T& get(detail::node_t<I, T>& node) noexcept
    {
        return node;
    }

    /**
     * Retrieve const-qualified tuple node by its index and returns its value.
     * @tparam I The requested node index.
     * @tparam T The type of the requested node member.
     * @param node The selected const-qualified tuple node member.
     * @return The const-qualified node's value.
     */
    template <id_t I, typename T>
    SUPERTUPLE_CUDA_CONSTEXPR const T& get(const detail::node_t<I, T>& node) noexcept
    {
        return node;
    }

    /**
     * Retrieve const-qualified tuple node by its unique type and returns its value.
     * @tparam T The type of the requested node member.
     * @tparam I The requested node index.
     * @param node The selected const-qualified tuple node member.
     * @return The const-qualified node's value.
     */
    template <typename T, id_t I>
    SUPERTUPLE_CUDA_CONSTEXPR const T& get(const detail::node_t<I, T>& node) noexcept
    {
        return node;
    }

    /**
     * Retrieve a tuple node by its index and moves its contents.
     * @tparam I The requested node index.
     * @tparam T The type of the requested node member.
     * @param node The selected tuple node member.
     * @return The node value's move reference.
     */
    template <id_t I, typename T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) get(detail::node_t<I, T>&& node) noexcept
    {
        return std::forward<T>(node);
    }

    /**
     * Retrieve a tuple node by its unique type and moves its contents.
     * @tparam T The type of the requested node member.
     * @tparam I The requested node index.
     * @param node The selected tuple node member.
     * @return The node value's move reference.
     */
    template <typename T, id_t I>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) get(detail::node_t<I, T>&& node) noexcept
    {
        return std::forward<T>(node);
    }
}

SUPERTUPLE_END_NAMESPACE
