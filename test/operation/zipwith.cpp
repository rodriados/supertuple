/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Test cases for the zipwith operation over tuples.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#include <catch.hpp>
#include <supertuple.hpp>

namespace st = supertuple;

/**
 * Tests the zipwith operation over tuple instances that own all of their elements.
 * The expected behaviour of this operation is to produce a new tuple of containing
 * the result of a function applied with the elements of both tuples.
 * @since 1.0
 */
TEST_CASE("zipwith-operation over owning tuples", "[zipwith][owning]")
{
    constexpr auto t1 = st::tuple_t(1, 2, 3);
    constexpr auto t2 = st::tuple_t(2, 4, 6);
    constexpr auto f = [](auto x, auto y) { return x + y; };

    constexpr auto r = st::zipwith(t1, t2, f);

    STATIC_REQUIRE(decltype(r)::count == 3);
    STATIC_REQUIRE(r == st::tuple_t(3, 6, 9));
}
