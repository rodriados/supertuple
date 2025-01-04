/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Utility types and functions for tuples implementations.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <utility>

#include <supertuple/environment.h>

SUPERTUPLE_BEGIN_NAMESPACE

namespace detail
{
    /**
     * Returns the type unchanged. This is useful to produce a repeating list of the
     * given type parameter.
     * @tpatam T The identity type.
     * @since 1.0
     */
    template <typename T, size_t = 0>
    struct identity_t { using type = T; };

    /**
     * Returns the first parameter from a variadic list of elements. This function
     * is useful when dealing with type-packs and it is needed to extract the first.
     * @tparam T The type of the value to be returned.
     * @tparam U The type of the values to ignore.
     * @return The given return value.
     */
    template <typename T, typename ...U>
    SUPERTUPLE_CONSTEXPR decltype(auto) ret1(T&& target, U&&...) noexcept
    {
        return std::forward<decltype(target)>(target);
    }

    /**
     * Invokes a functor that takes no arguments.
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
     * Seamlessly invokes a functor depending on whether its a free function,
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
     * Flips the first two parameters of a functor.
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
