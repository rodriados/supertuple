/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file An example usage for geometry implementation.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#include <cmath>
#include <cstdint>
#include <cassert>

#include <iostream>
#include <functional>
#include <string>
#include <utility>

#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <supertuple.hpp>

namespace st = supertuple;

/*
 * This example uses tuples to implement geometry and linear algebra operations,
 * for points and vectors. These operations may be optimized by the compiler and
 * even be executed on compile-time if possible, while also producing functional
 * and expressive code.
 * @since 1.0
 */

inline static constexpr auto add      = [](auto&& x, auto && y) { return x + y; };
inline static constexpr auto subtract = [](auto&& x, auto && y) { return x - y; };
inline static constexpr auto multiply = [](auto&& x, auto && y) { return x * y; };
inline static constexpr auto divide   = [](auto&& x, auto && y) { return x / y; };
inline static constexpr auto fpow     = [](auto&& x, auto && y) { return std::pow(x, y); };

// Ignoring warning for anonymous structs which are prohibited by ISO C++ standard,
// but is supported by all major compilers. We exploit these anonymous structs to
// allow coordinates to be accessed by their different axis-names within distinct
// coordinated systems at the same time.
SUPERTUPLE_DISABLE_GCC_WARNING_BEGIN("-Wpedantic")

namespace geometry
{
    /**
     * The representation of a coordinate system for a generic D-dimensional space.
     * Due to the purposedly arbitrary number of dimensions, there are no special
     * axis or dimension identifiers to coordinates higher than 4 dimensions.
     * @tparam D The coordinate system's space dimensionality.
     * @tparam T The type for the coordinate dimensions' values.
     * @since 1.0
     */
    template <size_t D, typename T = int64_t>
    struct coordinate_t
    {
        typedef T dimension_t;
        inline static constexpr size_t dimensionality = D;

        static_assert(dimensionality > 0, "a coordinate must be at least 1-dimensional");
        static_assert(std::is_arithmetic<dimension_t>::value, "a coordinate must have arithmetic type");

        union {
            dimension_t value[D] {};
        };
    };

    /**
     * The representation of a coordinate system for a generic 1-dimensional space.
     * As an 1-dimensional value is a scalar, such coordinate system can be interpreted
     * as and seamlessly converted to its scalar type.
     * @tparam T The type for the coordinate dimension's value.
     * @since 1.0
     */
    template <typename T>
    struct coordinate_t<1, T>
    {
        typedef T dimension_t;
        inline static constexpr size_t dimensionality = 1;

        static_assert(std::is_arithmetic<dimension_t>::value, "a coordinate must have arithmetic type");

        union {
            dimension_t value[1] {};
            struct { dimension_t a; };
            struct { dimension_t i; };
            struct { dimension_t x; };
        };

        /**
         * Converts the coordinate value into its scalar value, a particularity
         * possible only 1-dimensional coordinate systems.
         * @return The point's 1-dimensional scalar value.
         */
        inline constexpr operator dimension_t() const noexcept
        {
            return value;
        }
    };

    /**
     * The representation of a coordinate system for a generic 2-dimensional space.
     * At this dimensionality, the coordinates in the system might be referred to
     * as or named with different 2-letter combinations.
     * @tparam T The type for the coordinate dimension's value.
     * @since 1.0
     */
    template <typename T>
    struct coordinate_t<2, T>
    {
        typedef T dimension_t;
        inline static constexpr size_t dimensionality = 2;

        static_assert(std::is_arithmetic<dimension_t>::value, "a coordinate must have arithmetic type");

        union {
            dimension_t value[2] {};
            struct { dimension_t a, b; };
            struct { dimension_t i, j; };
            struct { dimension_t x, y; };
        };
    };

    /**
     * The representation of a coordinate system for a generic 3-dimensional space.
     * At this dimensionality, the coordinates in the system might be referred to
     * as or named with different 3-letter combinations.
     * @tparam T The type for the coordinate dimension's value.
     * @since 1.0
     */
    template <typename T>
    struct coordinate_t<3, T>
    {
        typedef T dimension_t;
        inline static constexpr size_t dimensionality = 3;

        static_assert(std::is_arithmetic<dimension_t>::value, "a coordinate must have arithmetic type");

        union {
            dimension_t value[3] {};
            struct { dimension_t a, b, c; };
            struct { dimension_t i, j, k; };
            struct { dimension_t x, y, z; };
        };
    };

    /*
     * Deduction guides for generic coordinate types.
     * @since 1.0
     */
    template <typename ...T> coordinate_t(T...)
        -> coordinate_t<sizeof...(T), std::common_type_t<T...>>;

    /**
     * Represents a simple point or vector for a generic D-dimensional space.
     * @tparam D The point's dimensionality.
     * @tparam T The point's coordinates' type.
     * @since 1.0
     */
    template <size_t D, typename T = int64_t>
    class point_t : public geometry::coordinate_t<D, T>
    {
      private:
        typedef geometry::coordinate_t<D, T> underlying_t;

      public:
        using typename underlying_t::dimension_t;
        using underlying_t::dimensionality;

      public:
        inline constexpr point_t() noexcept = default;
        inline constexpr point_t(const point_t&) noexcept = default;
        inline constexpr point_t(point_t&&) noexcept = default;

        /**
         * Instantiates a new point from a general list of coordinate values.
         * @tparam U The list of coordinate parameter types.
         * @param value The point's coordinates' values.
         */
        template <
            typename ...U
          , typename = typename std::enable_if<(
                std::is_convertible<U, dimension_t>::value && ... &&
                (underlying_t::dimensionality == sizeof...(U))
            )>::type
        >
        inline constexpr point_t(const U&... value)
          : underlying_t {static_cast<dimension_t>(value)...}
        {}

        /**
         * Instantiates a new point from a tuple.
         * @tparam U The tuple's contents types.
         * @param tuple The tuple to build a point from.
         */
        template <typename ...U>
        inline constexpr point_t(const st::tuple_t<U...>& tuple)
          : point_t (tuple, std::make_index_sequence<sizeof...(U)>())
        {}

        inline point_t& operator=(const point_t&) noexcept = default;
        inline point_t& operator=(point_t&&) noexcept = default;

        /**
         * Gives direct access to a const-qualified point's coordinate value.
         * @param offset The requested point coordinate offset.
         * @return The point's requested const-qualified coordinate value.
         */
        inline constexpr const dimension_t& operator[](int offset) const noexcept
        {
            return underlying_t::value[offset];
        }

      private:
        /**
         * Instantiates a new point by deconstructing a tuple.
         * @tparam I The tuple's indeces.
         * @tparam U The tuple's elements type.
         * @param tuple The tuple to build a new point from.
         */
        template <typename ...U, size_t ...I>
        inline constexpr point_t(const st::tuple_t<U...>& tuple, std::index_sequence<I...>)
          : point_t(st::get<I>(tuple)...)
        {}
    };

    /*
     * Deduction guides for generic point types.
     * @since 1.0
     */
    template <typename ...T> point_t(T...) -> point_t<sizeof...(T), std::common_type_t<T...>>;
    template <typename ...T> point_t(st::tuple_t<T...>) -> point_t<sizeof...(T), std::common_type_t<T...>>;
    template <typename T, size_t N> point_t(st::ntuple_t<T, N>) -> point_t<N, T>;

    /**
     * The equality operator for two coordinates of equal dimensionalities.
     * @tparam D The coordinates' dimensionality value.
     * @tparam T The first coordinate's dimension type.
     * @tparam U The second coordinate's dimension type.
     * @param a The first coordinate instance.
     * @param b The second coordinate instance.
     * @return Are both coordinates equal?
     */
    template <size_t D, typename T, typename U>
    inline constexpr bool operator==(
        const coordinate_t<D, T>& a
      , const coordinate_t<D, U>& b
    ) noexcept {
        return st::tie(a.value) == st::tie(b.value);
    }

    /**
     * The equality operator for coodinates with different dimensionalities.
     * @tparam A The first coordinate's dimensionality value.
     * @tparam B The second coordinate's dimensionality value.
     * @tparam T The first coordinate's dimension type.
     * @tparam U The second coordinate's dimension type.
     * @return Are both coodinates equal?
     */
    template <size_t A, size_t B, typename T, typename U>
    inline constexpr bool operator==(
        const coordinate_t<A, T>&
      , const coordinate_t<B, U>&
    ) noexcept {
        return false;
    }

    /**
     * The inequality operator for two generic coordinates.
     * @tparam A The first coordinate's dimensionality value.
     * @tparam B The second coordinate's dimensionality value.
     * @tparam T The first coordinate's dimension type.
     * @tparam U The second coordinate's dimension type.
     * @param a The first coordinate instance.
     * @param b The second coordinate instance.
     * @return Are the coordinates different?
     */
    template <size_t A, size_t B, typename T, typename U>
    inline constexpr bool operator!=(
        const coordinate_t<A, T>& a
      , const coordinate_t<B, U>& b
    ) noexcept {
        return !geometry::operator==(a, b);
    }

    /**
     * The operator for the sum of two vectors.
     * @tparam D The vectors' dimensionality.
     * @tparam T The first vector's coordinates' type.
     * @tparam U The second vector's coordinates' type.
     * @param a The first vector's instance.
     * @param b The second vector's instance.
     * @return The resulting vector sum.
     */
    template <size_t D, typename T, typename U>
    inline constexpr auto operator+(
        const point_t<D, T>& a
      , const point_t<D, U>& b
    ) noexcept {
        return point_t(st::zipwith(st::tie(a.value), st::tie(b.value), ::add));
    }

    /**
     * The operator for the subtraction of two vectors.
     * @tparam D The vectors' dimensionality.
     * @tparam T The first vector's coordinates' type.
     * @tparam U The second vector's coordinates' type.
     * @param a The first vector's instance.
     * @param b The second vector's instance.
     * @return The resulting vector subtraction.
     */
    template <size_t D, typename T, typename U>
    inline constexpr auto operator-(
        const point_t<D, T>& a
      , const point_t<D, U>& b
    ) noexcept {
        return point_t(st::zipwith(st::tie(a.value), st::tie(b.value), ::subtract));
    }

    /**
     * The operator for a vector's scalar product.
     * @tparam D The vector's dimensionality.
     * @tparam T The vector's coordinates' type.
     * @tparam S The scalar type.
     * @param v The vector's instance.
     * @param scalar The scalar value.
     * @return The resulting vector.
     */
    template <size_t D, typename T, typename S>
    inline constexpr auto operator*(
        const point_t<D, T>& v
      , const S& scalar
    ) noexcept {
        return point_t(st::apply(st::tie(v.value), ::multiply, scalar));
    }

    /**
     * The operator for a vector's scalar product with assumed commutativity.
     * @tparam S The scalar type.
     * @tparam D The vector's dimensionality.
     * @tparam T The vector's coordinates' type.
     * @param scalar The scalar value.
     * @param v The vector's instance.
     * @return The resulting vector.
     */
    template <typename S, size_t D, typename T>
    inline constexpr auto operator*(
        const S& scalar
      , const point_t<D, T>& v
    ) noexcept {
        return point_t(st::apply(st::tie(v.value), ::multiply, scalar));
    }

    /**
     * The operator for the dot product of two vectors.
     * @tparam D The vectors' dimensionality.
     * @tparam T The first vector's coordinates' type.
     * @tparam U The second vector's coordinates' type.
     * @param a The first vector's instance.
     * @param b The second vector's instance.
     * @return The resulting dot product value.
     */
    template <size_t D, typename T, typename U>
    inline constexpr auto dot(
        const point_t<D, T>& a
      , const point_t<D, U>& b
    ) noexcept {
        return st::foldl(
            st::zipwith(st::tie(a.value), st::tie(b.value), ::multiply)
          , ::add
        );
    }

    /**
     * The operator for the cross product of two 3-dimensional vectors.
     * @tparam T The first vector's coordinates' type.
     * @tparam U The second vector's coordinates' type.
     * @param a The first vector's instance.
     * @param b The second vector's instance.
     * @return The resulting vector.
     */
    template <typename T, typename U>
    inline constexpr auto cross(
        const point_t<3, T>& a
      , const point_t<3, U>& b
    ) noexcept {
        return point_t {
            (a.y * b.z - a.z * b.y)
          , (a.z * b.x - a.x * b.z)
          , (a.x * b.y - a.y * b.x)
        };
    }

    /**
     * The operator for the length of a vector.
     * @tparam D The vector's dimensionality.
     * @tparam T The vector's coordinates' type.
     * @param v The vector's instance.
     * @return The resulting length value.
     */
    template <size_t D, typename T>
    inline constexpr double length(const point_t<D, T>& v) noexcept
    {
        return std::sqrt(st::foldl(
            st::apply(st::tie(v.value), ::fpow, 2.)
          , ::add
        ));
    }

    /**
     * The operator for the normalization of a vector.
     * @tparam D The vector's dimensionality.
     * @tparam T The vector's coordinates' type.
     * @param v The vector's instance.
     * @return The resulting normalized vector.
     */
    template <size_t D, typename T>
    inline constexpr auto normalize(const point_t<D, T>& v) noexcept
    {
        return point_t(st::apply(st::tie(v.value), ::divide, geometry::length(v)));
    }

    /**
     * The distance operator for two generic points.
     * @tparam D The points' dimensionality value.
     * @tparam T The first point's coordinate type.
     * @tparam U The second point's coordinate type.
     * @param a The first point instance.
     * @param b The second point instance.
     * @return The Euclidean distance between the points.
     */
    template <size_t D, typename T, typename U>
    inline constexpr double distance(
        const point_t<D, T>& a
      , const point_t<D, U>& b
    ) noexcept {
        return std::sqrt(st::foldl(
            st::zipwith(
                st::tie(a.value)
              , st::tie(b.value)
              , [](auto&& x, auto&& y) { return std::pow(y - x, 2.); })
          , ::add
        ));
    }
}

SUPERTUPLE_DISABLE_GCC_WARNING_END("-Wpedantic")

/**
 * Formats a point to an output stream.
 * @tparam D The point's dimensionality value.
 * @tparam T The point's coordinate type.
 * @param stream The stream to format the point to.
 * @param point The point to be formatted.
 * @return The resulting output stream.
 */
template <size_t D, typename T>
inline std::ostream& operator<<(std::ostream& stream, const geometry::point_t<D, T>& point) noexcept
{
    size_t index = 0;
    const auto f = [&](std::ostream& os, const auto& element) -> std::ostream& {
        const char *start = (index == 0)  ? "(" : ", ";
        const char *end   = (++index < D) ? ""  : ")";
        return os << start << element << end; };
    return st::foldl(st::tie(point.value), f, stream);
}

/**
 * An example test case for operations with 2-dimensional points or vectors.
 * @since 1.0
 */
TEST_CASE("operations for 2-dimensional geometry", "[geometry]")
{
    const auto p1 = geometry::point_t(1, 2);
    const auto p2 = geometry::point_t(5, 7);

    REQUIRE(p1 + p2 == geometry::point_t(6, 9));
    REQUIRE(p2 - p1 == geometry::point_t(4, 5));

    REQUIRE(4 * p1 == geometry::point_t(4, 8));
    REQUIRE(p2 * 2 == geometry::point_t(10, 14));

    REQUIRE(geometry::length(p1) == std::sqrt(5));
    REQUIRE(geometry::length(p2) == std::sqrt(74));

    REQUIRE(geometry::dot(p1, p2) == 19);
    REQUIRE(geometry::distance(p1, p2) == std::sqrt(41));
}

/**
 * An example test case for operations with 3-dimensional points or vectors.
 * @since 1.0
 */
TEST_CASE("operations for 3-dimensional geometry", "[geometry]")
{
    const auto p1 = geometry::point_t(1, 2, 3);
    const auto p2 = geometry::point_t(2, 3, 4);

    REQUIRE(p1 + p2 == geometry::point_t(3, 5, 7));
    REQUIRE(p2 - p1 == geometry::point_t(1, 1, 1));

    REQUIRE(3 * p1 == geometry::point_t(3, 6, 9));
    REQUIRE(p2 * 2 == geometry::point_t(4, 6, 8));

    REQUIRE(geometry::length(p1) == std::sqrt(14));
    REQUIRE(geometry::length(p2) == std::sqrt(29));

    REQUIRE(geometry::dot(p1, p2) == 20);
    REQUIRE(geometry::distance(p1, p2) == std::sqrt(3));
    REQUIRE(geometry::cross(p1, p2) == geometry::point_t(-1, 2, -1));
}
