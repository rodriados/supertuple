/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Test cases for general uses of a tuple.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#include <catch.hpp>
#include <supertuple.hpp>

namespace st = supertuple;

/**
 * A general tuple use-case which exploits multiple features that might be combined
 * in diverse meaningful ways.
 * @since 1.0
 */
TEST_CASE("general use-case for a tuple #1", "[reference][accessor]")
{
    double array[] = { 10.1, 11.2, 12.3, 13.4, 14.5, 15.6, 16.7, 17.8, 18.9, 19.1 };

    auto t1 = st::tuple_t(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
    auto t2 = st::tie(array);

    using numbers_t = decltype(t1);

    auto& [a, b, c, d, e, f, g, h, i, j] = t1;

    REQUIRE(b == 1);
    REQUIRE(e == 4);
    REQUIRE(g == 6);
    REQUIRE(j == 9);

    t1 = t2;

    REQUIRE(t1 == st::tuple_t(10, 11, 12, 13, 14, 15, 16, 17, 18, 19));

    REQUIRE(b == 11);
    REQUIRE(e == 14);
    REQUIRE(g == 16);
    REQUIRE(j == 19);

    b = 43;
    g = 89;

    (numbers_t::accessor_t<4>) t1 = 94;
    t1.set<9>(78);

    REQUIRE(t1 == st::tuple_t(10, 43, 12, 13, 94, 15, 89, 17, 18, 78));
    REQUIRE(e == 94);
    REQUIRE(j == 78);
}
