/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Test cases for general uses of a tuple.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#include <supertuple.h>
#include <catch2/catch_test_macros.hpp>

namespace st = supertuple;

/**
 * A general tuple use-case which exploits multiple features that might be combined
 * in diverse meaningful ways.
 * @since 1.0
 */
TEST_CASE("general use-cases for tuples", "[reference][accessor]")
{
    auto tuple = st::tuple_t(0, 1, 2, 3);
    auto& [a, b, c, d] = tuple;

    /**
     * Test whether a tuple can be deconstructed using C++ standard tuple syntax.
     * It is expected that the tuple can distribute its values' references to a
     * list of variables without initially modifying them.
     * @since 1.0
     */
    SECTION("tuples can be destructured") {
        REQUIRE(a == 0);
        REQUIRE(b == 1);
        REQUIRE(c == 2);
        REQUIRE(d == 3);
    }

    /**
     * Test whether the destructured variables can be modified by the tuple. It
     * is expected that changing the destructured values or the tuple directly
     * must change the other as well.
     * @since 1.0
     */
    SECTION("destructured tuples keep their references") {
        double array[] = {10., 11., 12., 13.};

        tuple = st::tie(array);

        REQUIRE(a == 10);
        REQUIRE(b == 11);
        REQUIRE(c == 12);
        REQUIRE(d == 13);

        b = 43;
        c = 89;

        REQUIRE(tuple == st::tuple_t(10, 43, 89, 13));
    }

    /**
     * Test whether accessors can be used to access and modify tuples. It is expected
     * that accessors keep references intact, thus allowing them to change variables
     * that were previously destructured from the tuple.
     * @since 1.0
     */
    SECTION("tuples can be modified using accessors") {
        (decltype(tuple)::accessor_t<2>) tuple = 9;

        REQUIRE(a == 0);
        REQUIRE(b == 1);
        REQUIRE(c == 9);
        REQUIRE(d == 3);

        REQUIRE(tuple == st::tuple_t(0, 1, 9, 3));
    }
}
