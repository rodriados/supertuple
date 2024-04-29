/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The tuple convert operation implementation.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <utility>

#include <supertuple/environment.h>
#include <supertuple/operation/get.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

namespace detail
{
    /**
     * The conversion utility wrapper, which carries a reference to a tuple until
     * the conversion is actually performed. When converting a moving tuple, the
     * tuple is owned by this type.
     * @tparam T The type of tuple to be converted.
     * @since 1.0
     */
    template <typename T>
    class converter_t
    {
        protected:
            typedef T reference_t;
            typedef std::remove_reference_t<T> wrapped_t;

        protected:
            reference_t m_ref;

        public:
            SUPERTUPLE_CONSTEXPR converter_t() noexcept = delete;
            SUPERTUPLE_CONSTEXPR converter_t(const converter_t&) noexcept = delete;
            SUPERTUPLE_CONSTEXPR converter_t(converter_t&&) noexcept = delete;

            /**
             * Acquires a reference or ownership of the tuple to convert.
             * @param t The tuple reference or instance to be converted.
             */
            SUPERTUPLE_CONSTEXPR converter_t(reference_t&& t)
              : m_ref (std::forward<decltype(t)>(t))
            {}

            SUPERTUPLE_CONSTEXPR converter_t& operator=(const converter_t&) noexcept = delete;
            SUPERTUPLE_CONSTEXPR converter_t& operator=(converter_t&&) noexcept = delete;

            /**
             * Converts the wrapped tuple into the requested type.
             * @tparam U The type to which the tuple must convert to.
             * @return An instance of the tuple converted to the requested type.
             */
            template <typename U>
            SUPERTUPLE_CONSTEXPR operator U() &&
            {
                return forward<U>(std::make_index_sequence<wrapped_t::count>());
            }

        private:
            /**
             * Forwards the wrapped tuple elements to the conversion target type.
             * @tparam U The type to which the tuple must convert to.
             * @return A new instance of the conversion target type.
             */
            template <typename U, size_t ...I>
            SUPERTUPLE_CONSTEXPR U forward(std::index_sequence<I...>)
            {
                return U {operation::get<I>(std::forward<decltype(m_ref)>(m_ref))...};
            }
    };

    template <typename T> converter_t(T&) -> converter_t<T&>;
    template <typename T> converter_t(const T&) -> converter_t<const T&>;
    template <typename T> converter_t(T&&) -> converter_t<T>;
}

inline namespace operation
{
    /**
     * Converts a tuple to a generic compatible type.
     * @tparam T The type of the tuple to be converted.
     * @param t The tuple instance to be converted.
     * @return A generic-convertible tuple wrapper instance.
     */
    template <typename T>
    SUPERTUPLE_CONSTEXPR decltype(auto) convert(T&& t)
    {
        return detail::converter_t(std::forward<decltype(t)>(t));
    }
}

SUPERTUPLE_END_NAMESPACE
