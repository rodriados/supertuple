/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple node container type implementation.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <utility>

#include <supertuple/environment.h>
#include <supertuple/detail/utility.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

namespace detail
{
    /**
     * A node for a single element in a tuple, optimized for empty types.
     * This node is the fundamental building block of a tuple, holding one single
     * element of type T. It uses Empty Base Optimization to minimize memory usage
     * by not requiring space allocation for empty element types.
     * @tparam I The index of this element in the tuple.
     * @tparam T The type of the element stored in this node.
     * @since 1.0
     */
    template <id_t I, typename T, bool = std::is_empty_v<T>>
    struct node_t;

    /**
     * The node specialization for non-empty types. This node stores the element
     * in a member variable, thus allocating memory space for it.
     * @tparam I The index of this element in the tuple.
     * @tparam T The type of the element stored in this node.
     * @since 1.0
     */
    template <id_t I, typename T>
    struct node_t<I, T, false>
    {
        typedef T element_t;

        element_t m_value;

        SUPERTUPLE_CONSTEXPR node_t() = default;
        SUPERTUPLE_CONSTEXPR node_t(const node_t&) = default;
        SUPERTUPLE_CONSTEXPR node_t(node_t&&) = default;

        /**
         * Construct a node with a foreign forwarded value.
         * @tparam U The type of the foreign value to store.
         * @param value The value to store in the node.
         */
        template <typename U>
        SUPERTUPLE_CUDA_CONSTEXPR node_t(U&& value)
          : m_value (std::forward<U>(value))
        {}

        /**
         * Construct a node by moving from a foreign node.
         * @tparam U The type of the foreign node element.
         * @param other The foreign node to move from.
         */
        template <id_t J, typename U>
        SUPERTUPLE_CUDA_CONSTEXPR node_t(node_t<J, U>&& other)
          : m_value (std::forward<U>(other))
        {}

        SUPERTUPLE_INLINE node_t& operator=(const node_t&) = default;
        SUPERTUPLE_INLINE node_t& operator=(node_t&&) = default;

        /**
         * Assign a new value of foreign type to the node.
         * @tparam U The type of the foreign value to assign.
         * @param value The value to assign to the node.
         * @return Reference to this node.
         */
        template <typename U>
        SUPERTUPLE_CUDA_INLINE node_t& operator=(U&& value)
        {
            return _(this, m_value = std::forward<U>(value));
        }

        /**
         * Assign a new value by moving from a foreign node.
         * @tparam U The type of the foreign node element.
         * @param other The foreign node to move from.
         * @return Reference to this node.
         */
        template <id_t J, typename U>
        SUPERTUPLE_CUDA_INLINE node_t& operator=(node_t<J, U>&& other)
        {
            return operator=(std::forward<U>(other));
        }

        /**
         * Conversion operator to access the stored element in the node.
         * @return Reference to the stored element.
         */
        SUPERTUPLE_CUDA_CONSTEXPR operator element_t&() noexcept
        {
            return m_value;
        }

        /**
         * Conversion operator to access the stored const-qualified element.
         * @return Const-qualified reference to the stored element.
         */
        SUPERTUPLE_CUDA_CONSTEXPR operator const element_t&() const noexcept
        {
            return m_value;
        }
    };

    /**
     * The node specialization for empty types, using Empty Base Optimization.
     * This node inherits from empty type T to avoid memory allocation for it.
     * @tparam I The index of this element in the tuple.
     * @tparam T The type of the element stored in this node.
     * @since 1.2
     */
    template <id_t I, typename T>
    struct node_t<I, T, true> : public T
    {
        typedef T element_t;

        SUPERTUPLE_CONSTEXPR node_t() noexcept = default;
        SUPERTUPLE_CONSTEXPR node_t(const node_t&) noexcept = default;
        SUPERTUPLE_CONSTEXPR node_t(node_t&&) noexcept = default;

        /**
         * Construct a node with a foreign forwarded value.
         * @tparam U The type of the foreign value to store.
         * @param value The value to store in the node.
         */
        template <typename U>
        SUPERTUPLE_CUDA_CONSTEXPR node_t(U&& value)
          : element_t (std::forward<U>(value))
        {}

        /**
         * Construct a node by moving from a foreign node.
         * @tparam U The type of the foreign node element.
         * @param other The foreign node to move from.
         */
        template <id_t J, typename U>
        SUPERTUPLE_CUDA_CONSTEXPR node_t(node_t<J, U>&& other)
          : element_t (std::forward<U>(other))
        {}

        SUPERTUPLE_INLINE node_t& operator=(const node_t&) noexcept = default;
        SUPERTUPLE_INLINE node_t& operator=(node_t&&) noexcept = default;

        /**
         * Assign a new value of foreign type to the node.
         * @tparam U The type of the foreign value to assign.
         * @param value The value to assign to the node.
         * @return Reference to this node.
         */
        template <typename U>
        SUPERTUPLE_CUDA_INLINE node_t& operator=(U&& value)
        {
            return _(this, element_t::operator=(std::forward<U>(value)));
        }

        /**
         * Assign a new value by moving from a foreign node.
         * @tparam U The type of the foreign node element.
         * @param other The foreign node to move from.
         * @return Reference to this node.
         */
        template <id_t J, typename U>
        SUPERTUPLE_CUDA_INLINE node_t& operator=(node_t<J, U>&& other)
        {
            return operator=(std::forward<U>(other));
        }
    };

    /**
     * Extracts the internal node type from a tuple index implicit conversion.
     * @tparam I The index of the node to be extract from a tuple.
     * @tparam T The extracted tuple node element type.
     */
    template <id_t I, typename T>
    SUPERTUPLE_CUDA_CONSTEXPR auto access(node_t<I, T>) noexcept -> node_t<I, T>;
}

SUPERTUPLE_END_NAMESPACE
