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
    struct leaf_t
    {
        typedef T element_t;
        element_t value;

        SUPERTUPLE_CUDA_ENABLED inline constexpr leaf_t() = default;
        SUPERTUPLE_CUDA_ENABLED inline constexpr leaf_t(const leaf_t&) = default;
        SUPERTUPLE_CUDA_ENABLED inline constexpr leaf_t(leaf_t&&) = default;

        /**
         * Constructs a new tuple leaf.
         * @param value The value to be contained by the leaf.
         */
        SUPERTUPLE_CUDA_ENABLED inline constexpr leaf_t(const element_t& value)
          : value (value)
        {}

        /**
         * Constructs a new tuple leaf by moving a foreign value.
         * @tparam U The foreign value's type to be possibly moved.
         * @param value The foreign value to be moved into the leaf.
         */
        template <typename U>
        SUPERTUPLE_CUDA_ENABLED inline constexpr leaf_t(U&& value)
          : value (std::forward<decltype(value)>(value))
        {}

        /**
         * Constructs a new leaf by copying from a foreign tuple's leaf.
         * @tparam U The foreign tuple leaf's element type.
         * @param other The leaf to copy from.
         */
        template <typename U>
        SUPERTUPLE_CUDA_ENABLED inline constexpr leaf_t(const leaf_t<I, U>& other)
          : value (other.value)
        {}

        /**
         * Constructs a new leaf by moving from a foreign tuple's leaf.
         * @tparam U The foreign tuple leaf's element type.
         * @param other The leaf to move from.
         */
        template <typename U>
        SUPERTUPLE_CUDA_ENABLED inline constexpr leaf_t(leaf_t<I, U>&& other)
          : value (std::forward<decltype(other.value)>(other.value))
        {}

        SUPERTUPLE_CUDA_ENABLED inline leaf_t& operator=(const leaf_t&) = default;
        SUPERTUPLE_CUDA_ENABLED inline leaf_t& operator=(leaf_t&&) = default;

        /**
         * Copies the contents of a foreign tuple's leaf.
         * @tparam U The foreign tuple leaf's element type.
         * @param other The leaf to copy from.
         * @return The current leaf instance.
         */
        template <typename U>
        SUPERTUPLE_CUDA_ENABLED inline leaf_t& operator=(const leaf_t<I, U>& other)
        {
            return swallow(*this, value = other.value);
        }

        /**
         * Moves the contents of a foreign tuple's leaf.
         * @tparam U The foreign tuple leaf's element type.
         * @param other The leaf to move from.
         * @return The current leaf instance.
         */
        template <typename U>
        SUPERTUPLE_CUDA_ENABLED inline leaf_t& operator=(leaf_t<I, U>&& other)
        {
            return swallow(*this, value = std::forward<decltype(other.value)>(other.value));
        }
    };
}

SUPERTUPLE_END_NAMESPACE
