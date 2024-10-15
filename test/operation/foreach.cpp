/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Test cases the foreach operations over tuples.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#include <catch.hpp>
#include <supertuple.h>

namespace st = supertuple;

/**
 * Tests the foreach operation over a tuple instance that does not own its elements.
 * The expected behaviour of this operation is to modify the original values referenced
 * by the tuple, by applying a function over them.
 * @since 1.0
 */
TEST_CASE("foreach-operation over reference tuples", "[foreach][ref]")
{
    int index = 0;
    int array[] = { 1, 2, 3, 4 };

    auto tuple = st::tie(array);
    auto f = [](auto& x, auto& y) { x = x + (++y); };

    st::foreach(tuple, f, index);

    REQUIRE(array[0] == 2);
    REQUIRE(array[1] == 4);
    REQUIRE(array[2] == 6);
    REQUIRE(array[3] == 8);
}

/**
 * Tests the rforeach operation over a tuple instance that does not own its elements.
 * The expected behaviour of this operation is to modify the original values referenced
 * by the tuple, by applying a function over them from the end to the beginning.
 * @since 1.0
 */
TEST_CASE("rforeach-operation over reference tuples", "[rforeach][ref]")
{
    int index = 0;
    int array[] = { 1, 2, 3, 4 };

    auto tuple = st::tie(array);
    auto f = [](auto& x, auto& y) { x = x + (++y); };

    st::rforeach(tuple, f, index);

    REQUIRE(array[0] == 5);
    REQUIRE(array[1] == 5);
    REQUIRE(array[2] == 5);
    REQUIRE(array[3] == 5);
}
