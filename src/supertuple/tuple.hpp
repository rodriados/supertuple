/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The main tuple type implementation.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <cstddef>
#include <utility>

#include <supertuple/environment.h>

#include <supertuple/detail/utility.hpp>
#include <supertuple/detail/tuple.hpp>
#include <supertuple/operation/get.hpp>
#include <supertuple/operation/set.hpp>

SUPERTUPLE_BEGIN_NAMESPACE

/**
 * A tuple represents an indexable sequential list of elements of possibly different
 * types. In comparision with a plain struct containing elements of similar types,
 * the tuple must almost always require the same amount of memory and its elements
 * cannot be accessed by field names but offset. Differently from plain structs,
 * a tuple will not allocate memory for elements of empty types.
 * @tparam T The sequence of tuple element types.
 * @since 1.0
 */
template <typename ...T>
class tuple_t : public detail::tuple_t<detail::make_id_sequence_t<sizeof...(T)>, T...>
{
    public:
        SUPERTUPLE_CONSTEXPR static size_t count = sizeof...(T);

    private:
        typedef detail::make_id_sequence_t<count> identity_t;
        typedef detail::tuple_t<identity_t, T...> super_t;

    public:
        using base_tuple_t = tuple_t;

    public:
        /**
         * Typed accessor to an element within the tuple.
         * @tparam I The requested element node index.
         * @since 1.0
         */
        template <id_t I>
        using accessor_t = decltype(detail::access<I>(std::declval<tuple_t>()))&;

        /**
         * The type of a specific indexed tuple element within the tuple.
         * @tparam I The requested element index.
         * @since 1.0
         */
        template <id_t I>
        using element_t = typename std::remove_reference_t<accessor_t<I>>::element_t;

    public:
        SUPERTUPLE_CONSTEXPR tuple_t() = default;
        SUPERTUPLE_CONSTEXPR tuple_t(const tuple_t&) = default;
        SUPERTUPLE_CONSTEXPR tuple_t(tuple_t&&) = default;

        using super_t::tuple_t;

        SUPERTUPLE_INLINE tuple_t& operator=(const tuple_t&) = default;
        SUPERTUPLE_INLINE tuple_t& operator=(tuple_t&&) = default;

        using super_t::operator=;

        /**
         * Retrieve the value of a tuple element by its index.
         * @tparam I The requested element index.
         * @return The tuple element value.
         */
        template <id_t I>
        SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) get() noexcept
        {
            return operation::get<I>(*this);
        }

        /**
         * Retrieve the value of a tuple element by its unique type.
         * @tparam U The requested element type.
         * @return The tuple element value.
         */
        template <typename U>
        SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) get() noexcept
        {
            return operation::get<U>(*this);
        }

        /**
         * Retrieve the value of a const-qualified tuple element by its index.
         * @tparam I The requested element index.
         * @return The const-qualified tuple element value.
         */
        template <id_t I>
        SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) get() const noexcept
        {
            return operation::get<I>(*this);
        }

        /**
         * Retrieve the value of a const-qualified tuple element by its unique type.
         * @tparam U The requested element type.
         * @return The const-qualified tuple element value.
         */
        template <typename U>
        SUPERTUPLE_CUDA_CONSTEXPR decltype(auto) get() const noexcept
        {
            return operation::get<U>(*this);
        }

        /**
         * Update the value of a tuple element by its index.
         * @tparam I The requested element index.
         * @tparam V The tuple element new value type.
         */
        template <id_t I, typename V>
        SUPERTUPLE_CUDA_INLINE void set(V&& value)
        {
            operation::set<I>(*this, std::forward<V>(value));
        }

        /**
         * Update the value of a tuple element by its unique type.
         * @tparam U The requested element unique type.
         * @tparam V The tuple element new value type.
         */
        template <typename U, typename V>
        SUPERTUPLE_CUDA_INLINE void set(V&& value)
        {
            operation::set<U>(*this, std::forward<V>(value));
        }
};

namespace detail
{
    /**
     * Creates a tuple of repeated types.
     * @tparam T The type to be repeated as tuple elements.
     * @tparam I The tuple type index sequence.
     */
    template <typename T, id_t ...I>
    SUPERTUPLE_CUDA_CONSTEXPR auto repeater(id_sequence_t<I...>) noexcept
    -> supertuple::tuple_t<typename identity_t<T, I>::type...>;
}

/**
 * The type of an element in a tuple.
 * @tparam T The target tuple type.
 * @tparam I The index of tuple element.
 * @since 1.0
 */
template <typename T, id_t I>
using tuple_element_t = typename T::template element_t<I>;

/*
 * Deduction guides for generic tuple types.
 * @since 1.0
 */
template <typename ...T> tuple_t(T...) -> tuple_t<T...>;

/**
 * A tuple containing all elements of a single type can have its type representation
 * simplified by a N-tuple, which works in similar ways to an array, but with compile-time
 * size delimitation and validations.
 * @tparam T The tuple elements type.
 * @tparam N The number of elements in the tuple.
 * @since 1.0
 */
template <typename T, id_t N>
class ntuple_t : public decltype(detail::repeater<T>(detail::make_id_sequence_t<N>()))
{
    private:
        typedef detail::make_id_sequence_t<N> identity_t;
        typedef decltype(detail::repeater<T>(identity_t())) super_t;

    public:
        SUPERTUPLE_CONSTEXPR ntuple_t() = default;
        SUPERTUPLE_CONSTEXPR ntuple_t(const ntuple_t&) = default;
        SUPERTUPLE_CONSTEXPR ntuple_t(ntuple_t&&) = default;

        /**
         * Construct a new n-tuple from a raw foreign array.
         * @tparam U The foreign array type to create n-tuple from.
         * @param array The array to copy the n-tuple elements from.
         */
        template <
            typename U
          , typename = std::enable_if_t<
                std::is_pointer_v<std::remove_reference_t<U>> ||
                std::is_array_v<std::remove_reference_t<U>>>>
        SUPERTUPLE_CUDA_CONSTEXPR ntuple_t(U&& array)
          : ntuple_t (array, identity_t())
        {}

        /**
         * Construct a new n-tuple by moving a raw foreign array.
         * @tparam U The foreign array type to create n-tuple from.
         * @param array The array to move into the n-tuple elements.
         */
        template <typename U>
        SUPERTUPLE_CUDA_CONSTEXPR ntuple_t(U (&&array)[N])
          : ntuple_t (std::forward<decltype(array)>(array), identity_t())
        {}

        using super_t::tuple_t;

        SUPERTUPLE_INLINE ntuple_t& operator=(const ntuple_t&) = default;
        SUPERTUPLE_INLINE ntuple_t& operator=(ntuple_t&&) = default;

        using super_t::operator=;

    private:
        /**
         * Construct a new n-tuple by inlining an array.
         * @tparam U The foreign array type to create n-tuple from.
         * @tparam I The n-tuple sequence index for inlining the array.
         * @param array The array to inline.
         */
        template <typename U, id_t ...I>
        SUPERTUPLE_CUDA_CONSTEXPR ntuple_t(U&& array, detail::id_sequence_t<I...>)
          : super_t (array[I]...)
        {}

        /**
         * Construct a new n-tuple by moving the contents of an array.
         * @tparam U The foreign array type to create n-tuple from.
         * @tparam I The n-tuple sequence index for inlining the array.
         * @param array The array to be moved.
         */
        template <typename U, id_t ...I>
        SUPERTUPLE_CUDA_CONSTEXPR ntuple_t(U (&&array)[N], detail::id_sequence_t<I...>)
          : super_t (std::move(array[I])...)
        {}
};

/*
 * Deduction guides for n-tuple types.
 * @since 1.0
 */
template <typename T, id_t N> ntuple_t(const T(&)[N]) -> ntuple_t<T, N>;
template <typename T, id_t N> ntuple_t(T(&&)[N]) -> ntuple_t<T, N>;
template <typename ...T> ntuple_t(const T&...) -> ntuple_t<std::common_type_t<T...>, sizeof...(T)>;
template <typename ...T> ntuple_t(T&&...) -> ntuple_t<std::common_type_t<T...>, sizeof...(T)>;

/**
 * The tuple composed of exactly two elements is a pair. In a pair, each one of the
 * elements can be more easily accessed by aliased methods.
 * @tparam T The first element's type.
 * @tparam U The second element's type.
 * @since 1.0
 */
template <typename T, typename U>
class pair_t : public tuple_t<T, U>
{
    private:
        typedef tuple_t<T, U> super_t;

    public:
        SUPERTUPLE_CONSTEXPR pair_t() noexcept = default;
        SUPERTUPLE_CONSTEXPR pair_t(const pair_t&) = default;
        SUPERTUPLE_CONSTEXPR pair_t(pair_t&&) = default;

        using super_t::tuple_t;

        SUPERTUPLE_INLINE pair_t& operator=(const pair_t&) = default;
        SUPERTUPLE_INLINE pair_t& operator=(pair_t&&) = default;

        using super_t::operator=;

        /**
         * Retrieve the first element of the pair.
         * @return The pair first element reference.
         */
        SUPERTUPLE_CUDA_CONSTEXPR T& first() noexcept
        {
            return operation::get<0>(*this);
        }

        /**
         * Retrieve the const-qualified first element of the pair.
         * @return The pair first element const-qualified reference.
         */
        SUPERTUPLE_CUDA_CONSTEXPR const T& first() const noexcept
        {
            return operation::get<0>(*this);
        }

        /**
         * Retrieve the second element of the pair.
         * @return The pair second element reference.
         */
        SUPERTUPLE_CUDA_CONSTEXPR U& second() noexcept
        {
            return operation::get<1>(*this);
        }

        /**
         * Retrieve the const-qualified second element of the pair.
         * @return The pair second element const-qualified reference.
         */
        SUPERTUPLE_CUDA_CONSTEXPR const U& second() const noexcept
        {
            return operation::get<1>(*this);
        }
};

/*
 * Deduction guides for pair tuple types.
 * @since 1.0
 */
template <typename T, typename U> pair_t(T, U) -> pair_t<T, U>;

/**
 * Compare two tuples by checking whether their elements are equal.
 * @tparam I The tuples index sequence.
 * @tparam T The first tuple elements types.
 * @tparam U The second tuple elements types.
 * @param a The first tuple to be compared.
 * @param b The second tuple to be compared.
 * @return Are the two tuples considered equal?
 */
template <
    id_t ...I
  , typename ...T
  , typename ...U
  , typename = std::void_t<decltype(std::declval<T>() == std::declval<U>())...>>
SUPERTUPLE_CUDA_CONSTEXPR bool operator==(
    const detail::tuple_t<detail::id_sequence_t<I...>, T...>& a
  , const detail::tuple_t<detail::id_sequence_t<I...>, U...>& b
) noexcept {
    return ((operation::get<I>(a) == operation::get<I>(b)) && ...);
}

/**
 * Compare two tuples of different length or uncomparable element types.
 * @tparam I The first tuple index sequence.
 * @tparam J The second tuple index sequence.
 * @tparam T The first tuple elements types.
 * @tparam U The second tuple elements types.
 * @return The tuples cannot possibly be equal.
 */
template <id_t ...I, id_t ...J, typename ...T, typename ...U>
SUPERTUPLE_CUDA_CONSTEXPR bool operator==(
    const detail::tuple_t<detail::id_sequence_t<I...>, T...>& a
  , const detail::tuple_t<detail::id_sequence_t<J...>, U...>& b
) noexcept {
    return false;
}

/**
 * Compare two tuples by checking whether any of their elements are different.
 * @tparam I The first tuple index sequence.
 * @tparam J The second tuple index sequence.
 * @tparam T The first tuple elements types.
 * @tparam U The second tuple elements types.
 * @param a The first tuple to be compared.
 * @param b The second tuple to be compared.
 * @return Are the two tuples considered different?
 */
template <id_t ...I, id_t ...J, typename ...T, typename ...U>
SUPERTUPLE_CUDA_CONSTEXPR bool operator!=(
    const detail::tuple_t<detail::id_sequence_t<I...>, T...>& a
  , const detail::tuple_t<detail::id_sequence_t<J...>, U...>& b
) noexcept {
    return !operator==(a, b);
}

SUPERTUPLE_END_NAMESPACE

/**
 * Inform the size of a generic tuple, allowing it to be deconstructed.
 * @tparam T The tuple elements types.
 * @since 1.0
 */
template <typename ...T>
struct std::tuple_size<SUPERTUPLE_NAMESPACE::tuple_t<T...>>
  : std::integral_constant<size_t, SUPERTUPLE_NAMESPACE::tuple_t<T...>::count> {};

/**
 * Retrieve the type of a tuple element.
 * @tparam I The index of the requested tuple element.
 * @tparam T The tuple elements types.
 * @since 1.0
 */
template <size_t I, typename ...T>
struct std::tuple_element<I, SUPERTUPLE_NAMESPACE::tuple_t<T...>>
  : SUPERTUPLE_NAMESPACE::detail::identity_t<
        typename SUPERTUPLE_NAMESPACE::tuple_t<T...>::template element_t<I>> {};

/**
 * Inform the size of a generic n-tuple, allowing it to be deconstructed.
 * @tparam T The n-tuple elements type.
 * @tparam N The total number of elements in the n-tuple.
 * @since 1.0
 */
template <typename T, size_t N>
struct std::tuple_size<SUPERTUPLE_NAMESPACE::ntuple_t<T, N>>
  : std::integral_constant<size_t, N> {};

/**
 * Retrieve the type of a n-tuple element.
 * @tparam I The index of the requested tuple element.
 * @tparam T The n-tuple elements type.
 * @tparam N The total number of elements in the n-tuple.
 * @since 1.0
 */
template <size_t I, typename T, size_t N>
struct std::tuple_element<I, SUPERTUPLE_NAMESPACE::ntuple_t<T, N>>
  : SUPERTUPLE_NAMESPACE::detail::identity_t<
        typename SUPERTUPLE_NAMESPACE::ntuple_t<T, N>::template element_t<I>> {};

/**
 * Inform the size of a generic pair, allowing it to be deconstructed.
 * @tparam T The pair first element type.
 * @tparam U The pair second element type.
 * @since 1.0
 */
template <typename T, typename U>
struct std::tuple_size<SUPERTUPLE_NAMESPACE::pair_t<T, U>>
  : std::tuple_size<SUPERTUPLE_NAMESPACE::tuple_t<T, U>> {};

/**
 * Retrieve the type of a pair element.
 * @tparam I The index of the requested pair element.
 * @tparam T The pair first element type.
 * @tparam U The pair second element type.
 * @since 1.0
 */
template <size_t I, typename T, typename U>
struct std::tuple_element<I, SUPERTUPLE_NAMESPACE::pair_t<T, U>>
  : std::tuple_element<I, SUPERTUPLE_NAMESPACE::tuple_t<T, U>> {};
