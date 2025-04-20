/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The base tuple type implementation.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2025-present Rodrigo Siqueira
 */
#pragma once

#include <utility>

#include <supertuple/detail/utility.hpp>
#include <supertuple/detail/node.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

namespace detail
{
    /**
     * Base tuple implementation based on indexed node inheritance.
     * This tuple type is the internal base for full tuple types. The public API
     * tuple wraps this implementation and provide user-facing access. Operators
     * may act over this layer due to the easier access to the index sequence.
     * @tparam S A compile-time index sequence of elements.
     * @tparam T The element types stored in the tuple.
     * @since 1.2
     */
    template <typename S, typename ...T>
    class tuple_t;

    /**
     * The concrete base tuple storage type for a pack of node elements.
     * @tparam I The index sequence to identify the tuple.
     * @tparam T The list of tuple node elements types.
     * @since 1.2
     */
    template <id_t ...I, typename ...T>
    class tuple_t<id_sequence_t<I...>, T...> : public node_t<I, T>...
    {
        private:
            typedef id_sequence_t<I...> identity_t;

        public:
            SUPERTUPLE_CONSTEXPR static size_t count = sizeof...(I);

        static_assert(count == sizeof...(T), "impossible tuple type");

        public:
            SUPERTUPLE_CONSTEXPR tuple_t() = default;
            SUPERTUPLE_CONSTEXPR tuple_t(const tuple_t&) = default;
            SUPERTUPLE_CONSTEXPR tuple_t(tuple_t&&) = default;

            /**
             * Construct a new tuple from individual element values.
             * @tparam U The types of values to build the tuple from.
             * @param value The list of values to create the tuple with.
             */
            template <
                typename ...U
              , typename = std::enable_if_t<count == sizeof...(U)>>
            SUPERTUPLE_CUDA_CONSTEXPR tuple_t(U&&... value)
              : node_t<I, T> (std::forward<U>(value))...
            {}

            /**
             * Construct a new tuple by copying a foreign-typed tuple.
             * @tparam U The element types of the foreign tuple to copy from.
             * @param other The foreign tuple to copy elements from.
             */
            template <typename ...U>
            SUPERTUPLE_CUDA_CONSTEXPR tuple_t(const tuple_t<identity_t, U...>& other)
              : node_t<I, T> (static_cast<const node_t<I, U>&>(other))...
            {}

            /**
             * Construct a new tuple by moving from a foreign-typed tuple.
             * @tparam U The element types of the foreign tuple to move from.
             * @param other The foreign tuple to move elements from.
             */
            template <typename ...U>
            SUPERTUPLE_CUDA_CONSTEXPR tuple_t(tuple_t<identity_t, U...>&& other)
              : node_t<I, T> (std::forward<node_t<I, U>>(other))...
            {}

            SUPERTUPLE_INLINE tuple_t& operator=(const tuple_t&) = default;
            SUPERTUPLE_INLINE tuple_t& operator=(tuple_t&&) = default;

            /**
             * Assign from a foreign-typed tuple.
             * @tparam U The element types of the foreign tuple to assign from.
             * @param other The foreign tuple to assign elements from.
             */
            template <typename ...U>
            SUPERTUPLE_CUDA_INLINE tuple_t& operator=(const tuple_t<identity_t, U...>& other)
            {
                return _(this, node_t<I, T>::operator=(static_cast<const node_t<I, U>&>(other))...);
            }

            /**
             * Assign from a foreign-typed moving tuple.
             * @tparam U The element types of the foreign tuple to move-assign from.
             * @param other The foreign tuple to move-assign elements from.
             */
            template <typename ...U>
            SUPERTUPLE_CUDA_INLINE tuple_t& operator=(tuple_t<identity_t, U...>&& other)
            {
                return _(this, node_t<I, T>::operator=(std::forward<node_t<I, U>>(other))...);
            }
    };
}

SUPERTUPLE_END_NAMESPACE
