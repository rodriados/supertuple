/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple leaf type implementation.
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
     * Represents a tuple leaf, which holds a single value of a tuple.
     * @tparam I The tuple's leaf's index offset.
     * @tparam T The tuple's leaf's content type.
     * @since 1.0
     */
    template <size_t I, typename T>
    class leaf_t
    {
        public:
            typedef T element_t;

        protected:
            element_t m_value;

        public:
            SUPERTUPLE_CONSTEXPR leaf_t() = default;
            SUPERTUPLE_CONSTEXPR leaf_t(const leaf_t&) = default;
            SUPERTUPLE_CONSTEXPR leaf_t(leaf_t&&) = default;

            /**
             * Constructs a new tuple leaf.
             * @param value The value to be contained by the leaf.
             */
            SUPERTUPLE_CONSTEXPR leaf_t(const element_t& value)
              : m_value (value)
            {}

            /**
             * Constructs a new tuple leaf by moving a foreign value.
             * @tparam U The foreign value's type to be possibly moved.
             * @param value The foreign value to be moved into the leaf.
             */
            template <typename U>
            SUPERTUPLE_CONSTEXPR leaf_t(U&& value)
              : m_value (std::forward<decltype(value)>(value))
            {}

            /**
             * Constructs a new leaf by copying from a foreign tuple's leaf.
             * @tparam U The foreign tuple leaf's element type.
             * @param other The leaf to copy from.
             */
            template <typename U>
            SUPERTUPLE_CONSTEXPR leaf_t(const leaf_t<I, U>& other)
              : m_value (other.m_value)
            {}

            /**
             * Constructs a new leaf by moving from a foreign tuple's leaf.
             * @tparam U The foreign tuple leaf's element type.
             * @param other The leaf to move from.
             */
            template <typename U>
            SUPERTUPLE_CONSTEXPR leaf_t(leaf_t<I, U>&& other)
              : m_value (std::forward<decltype(other.m_value)>(other.m_value))
            {}

            SUPERTUPLE_INLINE leaf_t& operator=(const leaf_t&) = default;
            SUPERTUPLE_INLINE leaf_t& operator=(leaf_t&&) = default;

            /**
             * Copies the contents of a possibly moving foreign value.
             * @tparam U The foreign value's type.
             * @param value The value to be copied into the leaf.
             * @return The current leaf instance.
             */
            template <typename U>
            SUPERTUPLE_INLINE leaf_t& operator=(U&& value)
            {
                return swallow(*this, m_value = std::forward<decltype(value)>(value));
            }

            /**
             * Copies the contents of a foreign tuple's leaf.
             * @tparam U The foreign tuple leaf's element type.
             * @param other The leaf to copy from.
             * @return The current leaf instance.
             */
            template <typename U>
            SUPERTUPLE_INLINE leaf_t& operator=(const leaf_t<I, U>& other)
            {
                return operator=(other.m_value);
            }

            /**
             * Copies the contents of a moving foreign tuple's leaf.
             * @tparam U The foreign tuple leaf's element type.
             * @param other The leaf to move from.
             * @return The current leaf instance.
             */
            template <typename U>
            SUPERTUPLE_INLINE leaf_t& operator=(leaf_t<I, U>&& other)
            {
                return operator=(std::forward<decltype(other.m_value)>(other.m_value));
            }

            /**
             * Provides a reference to the leaf's internal value.
             * @return The reference to the leaf's internal value.
             */
            SUPERTUPLE_CONSTEXPR operator element_t&() noexcept
            {
                return m_value;
            }

            /**
             * Provides a const-qualified reference to the leaf's internal value.
             * @return The const-qualified reference to the leaf's internal value.
             */
            SUPERTUPLE_CONSTEXPR operator const element_t&() const noexcept
            {
                return m_value;
            }

        template <size_t, typename> friend class leaf_t;
    };
}

SUPERTUPLE_END_NAMESPACE
