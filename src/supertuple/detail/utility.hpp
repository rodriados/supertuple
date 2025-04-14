/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Utility types and functions for tuples implementations.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <cstddef>
#include <utility>

#include <supertuple/environment.h>

SUPERTUPLE_BEGIN_NAMESPACE

/**
 * The tuple element identifier and indexing type.
 * This type should be used to index and identify elements within a tuple.
 * @since 1.2
 */
using id_t = size_t;

namespace detail
{
    /**
     * Keep the given type unchanged.
     * This type is useful for some functional contexts and to produce a repetible
     * copy of the given type if needed.
     * @tpatam T The identity type.
     * @since 1.0
     */
    template <typename T, id_t = 0>
    struct identity_t { using type = T; };

    /**
     * Auxiliary type for enumerating elements in a tuple.
     * @tparam I The enumeration of the elements in tuple.
     * @since 1.2
     */
    template <id_t ...I>
    using id_sequence_t = std::integer_sequence<id_t, I...>;

    /**
     * Auxiliary type for creating an id sequence.
     * @tparam I The number of elements to enumerate in the sequence.
     * @since 1.2
     */
    template <id_t I>
    using make_id_sequence_t = std::make_integer_sequence<id_t, I>;

    /**
     * Auxiliary function to return a reference to the given first parameter.
     * @tparam T The type of the value to be returned.
     * @tparam W The type of the values to ignore.
     * @param _this The pointer to the reference to be returned.
     * @return The given return value reference.
     */
    template <typename T, typename ...W>
    SUPERTUPLE_CUDA_CONSTEXPR T& _(T *_this, W&&...) noexcept
    {
        return *_this;
    }

    /**
     * Swap the contents of two variables of mutually convertible types.
     * @tparam T The first variable type.
     * @tparam U The second variable type.
     * @param a The reference to the first variable to have its contents swapped.
     * @param b The reference to the second variable to have its contents swapped.
     */
    template <typename T, typename U>
    SUPERTUPLE_CONSTEXPR void swap(T& a, U& b)
    {
        T x = std::move(a);
          a = std::move(b);
          b = std::move(x);
    }

    /**
     * Invoke a functor that takes no arguments.
     * @tparam F The functor type.
     * @param lambda The functor instance to be invoked.
     * @return The functor invokation result.
     */
    template <typename F>
    SUPERTUPLE_CONSTEXPR decltype(auto) invoke(const F& lambda)
    {
        return (lambda)();
    }

    /**
     * Seamlessly invoke a functor depending on whether its a free function,
     * a lambda or an unbound member function pointer.
     * @tparam F The functor type.
     * @tparam O The first invoking parameter type or object type to bind to.
     * @tparam A The remaining invoking arguments types.
     * @param lambda The functor instance to be invoked.
     * @param object The possible object instance to bind the functor to.
     * @param args The remaining invoking arguments.
     * @return The functor invokation result.
     */
    template <typename F, typename O, typename ...A>
    SUPERTUPLE_CONSTEXPR decltype(auto) invoke(const F& lambda, O&& object, A&&... args)
    {
        if constexpr (std::is_member_function_pointer_v<F>) {
            return (object.*lambda)(std::forward<decltype(args)>(args)...);
        } else {
            return (lambda)(
                std::forward<decltype(object)>(object)
              , std::forward<decltype(args)>(args)...
            );
        }
    }

    /**
     * Flip the first two parameters of a functor.
     * @tparam F The functor type.
     * @param lambda The functor to have its parameters order flipped.
     * @return The given functor with flipped parameter order.
     */
    template <typename F>
    SUPERTUPLE_CONSTEXPR decltype(auto) flip(const F& lambda)
    {
        return [&](auto&& x, auto&& y, auto&&... z) constexpr -> decltype(auto) {
            return (lambda)(
                std::forward<decltype(y)>(y)
              , std::forward<decltype(x)>(x)
              , std::forward<decltype(z)>(z)...);
        };
    }
}

SUPERTUPLE_END_NAMESPACE
