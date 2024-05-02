/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Test cases the apply operation over tuples.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#include <catch.hpp>
#include <supertuple.hpp>

namespace st = supertuple;

/**
 * Tests the apply operation over a tuple instance that owns all of its elements.
 * The expected behaviour of this operation is to produce a new tuple where each
 * element is created by applying a function to a tuple's elements.
 * @since 1.0
 */
TEST_CASE("apply-operation over owning tuples", "[apply][owning]")
{
    auto tuple = st::tuple_t(1, 2, 3, 4);
    auto f = [](auto x, auto y) { return x + y; };

    const auto r = st::apply(tuple, f, 2);

    REQUIRE(r == st::tuple_t(3, 4, 5, 6));
}
