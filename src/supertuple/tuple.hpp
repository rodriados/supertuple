/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The main tuple type implementation.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <utility>

#include <supertuple/environment.h>

#include <supertuple/detail/leaf.hpp>
#include <supertuple/detail/utility.hpp>
#include <supertuple/operation/get.hpp>
#include <supertuple/operation/set.hpp>

SUPERTUPLE_DISABLE_NVCC_WARNING_BEGIN(20012)

SUPERTUPLE_BEGIN_NAMESPACE

/**
 * A tuple represents an indexable sequential list of elements of possibly different
 * types. In comparision with a plain struct containing elements of similar types,
 * the tuple must require the same amount of memory and its elements cannot be accessed
 * by field names but offset.
 * @tparam T The tuple's sequence of element types.
 * @since 1.0
 */
template <typename ...T>
class tuple_t : public tuple_t<detail::identity_t<std::make_index_sequence<sizeof...(T)>>, T...>
{
    public:
        static constexpr size_t count = sizeof...(T);

    private:
        typedef detail::identity_t<std::make_index_sequence<count>> identity_t;
        typedef tuple_t<identity_t, T...> underlying_t;

    public:
        using base_tuple_t = tuple_t;

    public:
      #if SUPERTUPLE_COMPILER == SUPERTUPLE_OPT_COMPILER_NVCC
        using underlying_t::tuple_t;
      #else
        using underlying_t::underlying_t;
      #endif
        using underlying_t::operator=;
};

namespace detail
{
    /**
     * Accesses the internal declared type of a tuple leaf.
     * @tparam I The index of the leaf to be accessed in the tuple.
     * @tparam T The extracted tuple element type.
     */
    template <size_t I, typename T>
    SUPERTUPLE_CONSTEXPR auto access(leaf_t<I, T>) noexcept
    -> leaf_t<I, T>;

    /**
     * Creates a tuple with repeated types.
     * @tparam T The type to be repeated as tuple elements.
     * @tparam I The tuple's type index sequence.
     */
    template <typename T, size_t ...I>
    SUPERTUPLE_CONSTEXPR auto repeater(std::index_sequence<I...>) noexcept
    -> tuple_t<typename identity_t<T, I>::type...>;
}

/**
 * The base tuple type.
 * @tparam I The sequence indeces for the tuple elements' types.
 * @tparam T The list of tuple elements' types.
 * @since 1.0
 */
template <size_t ...I, typename ...T>
class tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>
  : public detail::leaf_t<I, T>...
{
    private:
        typedef detail::identity_t<std::index_sequence<I...>> identity_t;

    public:
        /**
         * Provides typed access to an element within the tuple.
         * @tparam J The requested element index.
         * @since 1.0
         */
        template <size_t J>
        using accessor_t = decltype(detail::access<J>(std::declval<tuple_t>()))&;

        /**
         * Retrieves the type of a specific tuple element by its index.
         * @tparam J The requested element index.
         * @since 1.0
         */
        template <size_t J>
        using element_t = typename std::remove_reference_t<accessor_t<J>>::element_t;

    public:
        SUPERTUPLE_CONSTEXPR tuple_t() = default;
        SUPERTUPLE_CONSTEXPR tuple_t(const tuple_t&) = default;
        SUPERTUPLE_CONSTEXPR tuple_t(tuple_t&&) = default;

        /**
         * Creates a new tuple instance from a list of foreign values.
         * @tparam U The foreign values' types to build the tuple from.
         * @param value The list of foreign values to create the tuple with.
         */
        template <
            typename ...U
          , typename = std::enable_if_t<sizeof...(U) == sizeof...(T)>>
        SUPERTUPLE_CONSTEXPR tuple_t(U&&... value)
          : detail::leaf_t<I, T> (std::forward<decltype(value)>(value))...
        {}

        /**
         * Creates a new tuple instance from a tuple of foreign types.
         * @tparam U The types of foreign tuple instance to copy from.
         * @param other The foreign tuple which values must be copied from.
         */
        template <typename ...U>
        SUPERTUPLE_CONSTEXPR tuple_t(const tuple_t<identity_t, U...>& other)
          : detail::leaf_t<I, T> (static_cast<const detail::leaf_t<I, U>&>(other))...
        {}

        /**
         * Creates a new tuple instance by moving a tuple of foreign types.
         * @tparam U The types of foreign tuple instance to move from.
         * @param other The foreign tuple which values must be moved from.
         */
        template <typename ...U>
        SUPERTUPLE_CONSTEXPR tuple_t(tuple_t<identity_t, U...>&& other)
          : detail::leaf_t<I, T> (std::forward<detail::leaf_t<I, U>>(other))...
        {}

        SUPERTUPLE_INLINE tuple_t& operator=(const tuple_t&) = default;
        SUPERTUPLE_INLINE tuple_t& operator=(tuple_t&&) = default;

        /**
         * Copies the values from a foreign tuple instance.
         * @tparam U The types of foreign tuple instance to copy from.
         * @param other The tuple the values must be copied from.
         * @return The current tuple instance.
         */
        template <typename ...U>
        SUPERTUPLE_INLINE tuple_t& operator=(const tuple_t<identity_t, U...>& other)
        {
            return swallow(*this, accessor_t<I>(*this) = static_cast<const detail::leaf_t<I, U>&>(other)...);
        }

        /**
         * Moves the values from a foreign tuple instance.
         * @tparam U The types of the foreign tuple instance to move from.
         * @param other The tuple the values must be moved from.
         * @return The current tuple instance.
         */
        template <typename ...U>
        SUPERTUPLE_INLINE tuple_t& operator=(tuple_t<identity_t, U...>&& other)
        {
            return swallow(*this, accessor_t<I>(*this) = std::forward<detail::leaf_t<I, U>>(other)...);
        }

        /**
         * Retrieves the value of a tuple member by its index.
         * @tparam J The requested member's index.
         * @return The member's value.
         */
        template <size_t J>
        SUPERTUPLE_CONSTEXPR auto get() noexcept -> decltype(auto)
        {
            return operation::get<J>(*this);
        }

        /**
         * Retrieves the value of a const-qualified tuple member by its index.
         * @tparam J The requested member's index.
         * @return The const-qualified member's value.
         */
        template <size_t J>
        SUPERTUPLE_CONSTEXPR auto get() const noexcept -> decltype(auto)
        {
            return operation::get<J>(*this);
        }

        /**
         * Updates the value of a tuple member by its index.
         * @tparam J The requested member's index.
         * @tparam U The member's new value's type.
         */
        template <size_t J, typename U>
        SUPERTUPLE_INLINE void set(U&& value)
        {
            operation::set<J>(*this, std::forward<decltype(value)>(value));
        }
};

/**
 * The type of an element in a tuple.
 * @tparam T The target tuple type.
 * @tparam I The index of tuple element.
 * @since 1.0
 */
template <typename T, size_t I>
using tuple_element_t = typename T::template element_t<I>;

/*
 * Deduction guides for generic tuple types.
 * @since 1.0
 */
template <typename ...T> tuple_t(T...) -> tuple_t<T...>;

/**
 * A tuple containing all elements of a single type can have its representation
 * simplified by a N-tuple, which works in similar ways to an array, but with compile-time
 * size delimitation and validations.
 * @tparam T The tuple's elements' type.
 * @tparam N The number of elements in the tuple.
 * @since 1.0
 */
template <typename T, size_t N>
class ntuple_t : public decltype(detail::repeater<T>(std::make_index_sequence<N>()))
{
    private:
        typedef std::make_index_sequence<N> indexer_t;
        typedef decltype(detail::repeater<T>(indexer_t())) underlying_t;

    public:
        SUPERTUPLE_CONSTEXPR ntuple_t() noexcept = default;
        SUPERTUPLE_CONSTEXPR ntuple_t(const ntuple_t&) = default;
        SUPERTUPLE_CONSTEXPR ntuple_t(ntuple_t&&) = default;

        /**
         * Creates a new tuple from a raw foreign array.
         * @tparam U The foreign array's type to create tuple from.
         * @param array The array to initialize the tuple's values from.
         */
        template <
            typename U
          , typename = std::enable_if_t<
                std::is_pointer_v<std::remove_reference_t<U>> ||
                std::is_array_v<std::remove_reference_t<U>>>>
        SUPERTUPLE_CONSTEXPR ntuple_t(U&& array)
          : ntuple_t (indexer_t(), array)
        {}

        /**
         * Creates a new tuple by moving a raw foreign array.
         * @tparam U The foreign array's type to create tuple from.
         * @param array The array to move into the tuple's values.
         */
        template <typename U>
        SUPERTUPLE_CONSTEXPR ntuple_t(U (&&array)[N])
          : ntuple_t (indexer_t(), std::forward<decltype(array)>(array))
        {}

      #if SUPERTUPLE_COMPILER == SUPERTUPLE_OPT_COMPILER_NVCC
        using underlying_t::tuple_t;
      #else
        using underlying_t::underlying_t;
      #endif

        SUPERTUPLE_INLINE ntuple_t& operator=(const ntuple_t&) = default;
        SUPERTUPLE_INLINE ntuple_t& operator=(ntuple_t&&) = default;

        using underlying_t::operator=;

    private:
        /**
         * Creates a new tuple by inlining an array.
         * @tparam U The foreign array type to create tuple from.
         * @tparam I The tuple's sequence index for inlining the array.
         * @param array The array to inline.
         */
        template <typename U, size_t ...I>
        SUPERTUPLE_CONSTEXPR ntuple_t(std::index_sequence<I...>, U&& array)
          : underlying_t (array[I]...)
        {}

        /**
         * Creates a new tuple by moving the contents of an array.
         * @tparam U The foreign array type to create tuple from.
         * @tparam I The tuple's sequence index for inlining the array.
         * @param array The array to be moved.
         */
        template <typename U, size_t ...I>
        SUPERTUPLE_CONSTEXPR ntuple_t(std::index_sequence<I...>, U (&&array)[N])
          : underlying_t (std::move(array[I])...)
        {}
};

/*
 * Deduction guides for n-tuple types.
 * @since 1.0
 */
template <typename T, size_t N> ntuple_t(const T(&)[N]) -> ntuple_t<T, N>;
template <typename T, size_t N> ntuple_t(T(&&)[N]) -> ntuple_t<T, N>;
template <typename ...T> ntuple_t(const T&...) -> ntuple_t<std::common_type_t<T...>, sizeof...(T)>;
template <typename ...T> ntuple_t(T&&...) -> ntuple_t<std::common_type_t<T...>, sizeof...(T)>;

/**
 * The tuple composed of exactly two elements is a pair. In a pair, each
 * of the elements can be more easily accessed by aliased methods.
 * @tparam T The first element's type.
 * @tparam U The second element's type.
 * @since 1.0
 */
template <typename T, typename U>
class pair_t : public tuple_t<T, U>
{
    private:
        typedef tuple_t<T, U> underlying_t;

    public:
        SUPERTUPLE_CONSTEXPR pair_t() noexcept = default;
        SUPERTUPLE_CONSTEXPR pair_t(const pair_t&) = default;
        SUPERTUPLE_CONSTEXPR pair_t(pair_t&&) = default;

      #if SUPERTUPLE_COMPILER == SUPERTUPLE_OPT_COMPILER_NVCC
        using underlying_t::tuple_t;
      #else
        using underlying_t::underlying_t;
      #endif

        SUPERTUPLE_INLINE pair_t& operator=(const pair_t&) = default;
        SUPERTUPLE_INLINE pair_t& operator=(pair_t&&) = default;

        using underlying_t::operator=;

        /**
         * Retrieves the first element of the pair.
         * @return The pair's first element's reference.
         */
        SUPERTUPLE_CONSTEXPR auto first() const noexcept -> const T&
        {
            return operation::get<0>(*this);
        }

        /**
         * Retrieves the second element of the pair.
         * @return The pair's second element's reference.
         */
        SUPERTUPLE_CONSTEXPR auto second() const noexcept -> const U&
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
 * Compares two tuples by checking whether their elements are equal.
 * @tparam I The tuples' sequence indeces.
 * @tparam T The first tuple's element members types.
 * @tparam U The second tuple's element members types.
 * @param a The first tuple to be compared.
 * @param b The second tuple to be compared.
 * @return Are the two tuples considered equal?
 */
template <
    size_t ...I, typename ...T, typename ...U
  , typename = std::void_t<decltype(std::declval<T>() == std::declval<U>())...>>
SUPERTUPLE_CONSTEXPR bool operator==(
    const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& a
  , const tuple_t<detail::identity_t<std::index_sequence<I...>>, U...>& b
) noexcept {
    return ((operation::get<I>(a) == operation::get<I>(b)) && ...);
}

/**
 * Compares two tuples of different length or uncomparable element types.
 * @tparam I The first tuple's sequence indeces.
 * @tparam J The second tuple's sequence indeces.
 * @tparam T The first tuple's element members types.
 * @tparam U The second tuple's element members types.
 * @return The tuples cannot possibly be equal.
 */
template <size_t ...I, size_t ...J, typename ...T, typename ...U>
SUPERTUPLE_CONSTEXPR bool operator==(
    const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>&
  , const tuple_t<detail::identity_t<std::index_sequence<J...>>, U...>&
) noexcept {
    return false;
}

/**
 * Compares two tuples by checking whether any of their elements are different.
 * @tparam I The first tuple's sequence indeces.
 * @tparam J The second tuple's sequence indeces.
 * @tparam T The first tuple's element members types.
 * @tparam U The second tuple's element members types.
 * @param a The first tuple to be compared.
 * @param b The second tuple to be compared.
 * @return Are the two tuples considered different?
 */
template <size_t ...I, size_t ...J, typename ...T, typename ...U>
SUPERTUPLE_CONSTEXPR bool operator!=(
    const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& a
  , const tuple_t<detail::identity_t<std::index_sequence<J...>>, U...>& b
) noexcept {
    return !operator==(a, b);
}

SUPERTUPLE_END_NAMESPACE

/**
 * Informs the size of a generic tuple, allowing it to be deconstructed.
 * @tparam T The tuple's elements' types.
 * @since 1.0
 */
template <typename ...T>
struct std::tuple_size<SUPERTUPLE_NAMESPACE::tuple_t<T...>>
  : std::integral_constant<size_t, SUPERTUPLE_NAMESPACE::tuple_t<T...>::count> {};

/**
 * Retrieves the deconstruction type of a tuple's element.
 * @tparam I The index of the requested tuple element.
 * @tparam T The tuple's elements' types.
 * @since 1.0
 */
template <size_t I, typename ...T>
struct std::tuple_element<I, SUPERTUPLE_NAMESPACE::tuple_t<T...>>
  : SUPERTUPLE_NAMESPACE::detail::identity_t<
        typename SUPERTUPLE_NAMESPACE::tuple_t<T...>::template element_t<I>> {};

/**
 * Informs the size of a generic n-tuple, allowing it to be deconstructed.
 * @tparam T The n-tuple's elements' type.
 * @tparam N The total number of elements in the n-tuple.
 * @since 1.0
 */
template <typename T, size_t N>
struct std::tuple_size<SUPERTUPLE_NAMESPACE::ntuple_t<T, N>>
  : std::integral_constant<size_t, N> {};

/**
 * Retrieves the deconstruction type of a n-tuple's element.
 * @tparam I The index of the requested tuple element.
 * @tparam T The n-tuple's elements' type.
 * @tparam N The total number of elements in the n-tuple.
 * @since 1.0
 */
template <size_t I, typename T, size_t N>
struct std::tuple_element<I, SUPERTUPLE_NAMESPACE::ntuple_t<T, N>>
  : SUPERTUPLE_NAMESPACE::detail::identity_t<
        typename SUPERTUPLE_NAMESPACE::ntuple_t<T, N>::template element_t<I>> {};

/**
 * Informs the size of a generic pair, allowing it to be deconstructed.
 * @tparam T The pair's first element type.
 * @tparam U The pair's second element type.
 * @since 1.0
 */
template <typename T, typename U>
struct std::tuple_size<SUPERTUPLE_NAMESPACE::pair_t<T, U>>
  : std::tuple_size<SUPERTUPLE_NAMESPACE::tuple_t<T, U>> {};

/**
 * Retrieves the deconstruction type of a pair's element.
 * @tparam I The index of the requested pair element.
 * @tparam T The pair's first element type.
 * @tparam U The pair's second element type.
 * @since 1.0
 */
template <size_t I, typename T, typename U>
struct std::tuple_element<I, SUPERTUPLE_NAMESPACE::pair_t<T, U>>
  : std::tuple_element<I, SUPERTUPLE_NAMESPACE::tuple_t<T, U>> {};

SUPERTUPLE_DISABLE_NVCC_WARNING_END(20012)
