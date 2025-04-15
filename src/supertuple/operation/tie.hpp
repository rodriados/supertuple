/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple tie operation implementation.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <utility>

#include <supertuple/environment.h>
#include <supertuple/tuple.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

inline namespace operation
{
    /**
     * Gather variable references into a tuple instance, allowing them to capture
     * values directly from compatible value tuples.
     * @tparam T The gathered variable types.
     * @param ref The gathered variable references.
     * @return The new tuple of references.
     */
    template <typename ...T>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) tie(T&... ref) noexcept
    {
        return tuple_t<T&...>(ref...);
    }

    /**
     * Gather the references of each element of a plain array into a tuple instance,
     * allowing them to capture values directly from compatible value tuples.
     * @tparam T The array elements type.
     * @tparam N The size of the given array.
     * @param ref The target array reference.
     * @return The new tuple of references.
     */
    template <typename T, size_t N>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) tie(T (&ref)[N]) noexcept
    {
        return ntuple_t<T&, N>(ref);
    }

    /**
     * Gather move-references of each element of an array from an array, allowing
     * them to be moved directly into compatible variables.
     * @tparam T The array elements type.
     * @tparam N The size of the given array.
     * @param ref The target array move-reference.
     * @return The new tuple of move-references.
     */
    template <typename T, size_t N>
    SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) tie(T (&&ref)[N]) noexcept
    {
        return ntuple_t<T&&, N>(std::forward<decltype(ref)>(ref));
    }
}

SUPERTUPLE_END_NAMESPACE
