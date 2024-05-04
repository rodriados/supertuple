/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Test cases for the scan operations over tuples.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#include <cmath>

#include <catch.hpp>
#include <supertuple.hpp>

namespace st = supertuple;

/**
 * The specialized power operator for integer values.
 * @param a The base-operand for the power operator.
 * @param b The exponent-operand for the power operator.
 * @return Computes the value of base raised to the exponent-power.
 */
static inline int ipow(const int a, const int b)
{
    return (int) std::pow(a, b);
}

/**
 * Tests the left-scan operation over a tuple instance that owns all of its elements.
 * The expected behaviour of this operation is to produce a value by applying repeatedly
 * the tuple elements with a function.
 * @since 1.0
 */
TEST_CASE("left-scan-operation over owning tuple", "[scanl][owning]")
{
    constexpr auto tuple = st::tuple_t(2, 3, 2);

    auto r = st::scanl(tuple, ipow);

    STATIC_REQUIRE(decltype(r)::count == 3);
    REQUIRE(r == st::tuple_t(2, 8, 64));
}

/**
 * Tests the right-scan operation over a tuple instance that owns all of its elements.
 * The expected behaviour of this operation is to produce a value by applying repeatedly
 * the tuple elements with a function.
 * @since 1.0
 */
TEST_CASE("right-scan-operation over owning tuple", "[scanr][owning]")
{
    constexpr auto tuple = st::tuple_t(2, 3, 2);

    auto r = st::scanr(tuple, ipow);

    STATIC_REQUIRE(decltype(r)::count == 3);
    REQUIRE(r == st::tuple_t(512, 9, 2));
}
