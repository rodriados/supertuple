/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Test cases for the zip operation over tuples.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#include <catch.hpp>
#include <supertuple.hpp>

namespace st = supertuple;

/**
 * Tests the zip operation over tuple instances that own all of their elements. The
 * expected behaviour of this operation is to produce a new tuple of pairs containing
 * the elements of both tuples.
 * @since 1.0
 */
TEST_CASE("zip-operation over owning tuples", "[zip][owning]")
{
    constexpr auto t1 = st::tuple_t(1, 2, 3);
    constexpr auto t2 = st::tuple_t(2, 4, 6);

    constexpr auto r = st::zip(t1, t2);

    STATIC_REQUIRE(decltype(r)::count == 3);
    STATIC_REQUIRE(r == st::tuple_t(
        st::pair_t(1, 2)
      , st::pair_t(2, 4)
      , st::pair_t(3, 6)));
}
