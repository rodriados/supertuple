/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file An example usage for geometry implementation.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2025-present Rodrigo Siqueira
 */
#include <cmath>

#include <supertuple.h>
#include <catch2/catch_test_macros.hpp>

namespace st = supertuple;

/*
 * This example uses tuples to implement geometry and linear algebra operations,
 * for points and vectors. These operations may be optimized by the compiler and
 * even be executed on compile-time if possible, while also producing functional
 * and expressive code.
 * @since 1.1
 */

inline static constexpr auto add      = [](auto&& x, auto&& y) { return x + y; };
inline static constexpr auto fpow     = [](auto&& x, auto&& y) { return std::pow(x, y); };
inline static constexpr auto diffpow2 = [](auto&& x, auto&& y) { return fpow(y - x, 2.); };

namespace geometry
{
    /**
     * Represents a simple point or vector for a D-dimensional space.
     * @tparam D The point's dimensionality.
     * @since 1.1
     */
    template <size_t D>
    using point_t = st::ntuple_t<double, D>;

    /**
     * Calculates the length of a vector from the origin to the point.
     * @tparam D The point's dimensionality.
     * @param p The point to calculate the vector length of.
     * @return The vector length from origin to the point.
     */
    template <size_t D>
    inline constexpr double length(const point_t<D>& p) noexcept
    {
        return std::sqrt(st::foldl(
            st::apply(p, ::fpow, 2.)
          , ::add
        ));
    }

    /**
     * Calculates the euclidean distance between two generic points.
     * @tparam D The points' dimensionality.
     * @param a The first point instance.
     * @param b The second point instance.
     * @return The euclidean distance between the points.
     */
    template <size_t D>
    inline constexpr double distance(
        const point_t<D>& a
      , const point_t<D>& b
    ) noexcept {
        return std::sqrt(st::foldl(
            st::zipwith(a, b, ::diffpow2)
          , ::add
        ));
    }
}

/**
 * An example test case for geometry operations with 3-dimensional points. Although
 * quite simple, this test can be replicated easily for different dimensionalities.
 * @since 1.1
 */
TEST_CASE("operations with 3-dimensional points", "[example][geometry]")
{
    const auto p1 = geometry::point_t<3>(1, 2, 3);
    const auto p2 = geometry::point_t<3>(2, 3, 4);
    const auto p3 = geometry::point_t<3>(4, 5, 6);

    SECTION("calculate the vector length from origin to a point") {
        REQUIRE(geometry::length(p1) == std::sqrt(14));
        REQUIRE(geometry::length(p2) == std::sqrt(29));
        REQUIRE(geometry::length(p3) == std::sqrt(77));
    }

    SECTION("calculate the distance between points") {
        REQUIRE(geometry::distance(p1, p2) == std::sqrt( 3));
        REQUIRE(geometry::distance(p1, p3) == std::sqrt(27));
        REQUIRE(geometry::distance(p2, p3) == std::sqrt(12));
    }
}
