/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple tie operation implementation.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <supertuple/environment.h>
#include <supertuple/tuple.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

inline namespace operation
{
    /**
     * Gathers variables references into a tuple instance, allowing them to capture
     * values directly from value tuples.
     * @tparam T The gathered variables types.
     * @param ref The gathered variables references.
     * @return The new tuple of references.
     */
    template <typename ...T>
    SUPERTUPLE_CUDA_ENABLED inline constexpr decltype(auto) tie(T&... ref) noexcept
    {
        return tuple_t<T&...>(ref...);
    }

    /**
     * Gathers an array's elements' references into a tuple instance, allowing them
     * to capture values directly from value tuples.
     * @tparam T The array's elements' type.
     * @tparam N The size of the given array.
     * @param ref The target array's reference.
     * @return The new tuple of references.
     */
    template <typename T, size_t N>
    SUPERTUPLE_CUDA_ENABLED inline constexpr decltype(auto) tie(T (&ref)[N]) noexcept
    {
        return ntuple_t<T&, N>(ref);
    }

    /**
     * Gathers move-references from an array's elements into a tuple instance, allowing
     * them to be moved directly into other variables.
     * @tparam T The array's elements' type.
     * @tparam N The size of the given array.
     * @param ref The target array's move-reference.
     * @return The new tuple of move-references.
     */
    template <typename T, size_t N>
    SUPERTUPLE_CUDA_ENABLED inline constexpr decltype(auto) tie(T (&&ref)[N]) noexcept
    {
        return ntuple_t<T&&, N>(std::forward<decltype(ref)>(ref));
    }
}

SUPERTUPLE_END_NAMESPACE
