/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Test cases for the concatenation operation over tuples.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#include <supertuple.h>
#include <catch2/catch_test_macros.hpp>

namespace st = supertuple;

/**
 * Tests the concatenation operation over tuple instances that own all of their elements.
 * The expected behaviour of this operation is to produce a new tuple with the copied
 * elements from both tuples.
 * @since 1.0
 */
TEST_CASE("concat-operation over owning tuples", "[concat][owning]")
{
    constexpr auto t1 = st::tuple_t(1, 2, 3, 4);
    constexpr auto t2 = st::tuple_t(5, 6, 7);

    constexpr auto r = st::concat(t1, t2);

    STATIC_REQUIRE(decltype(r)::count == 7);
    STATIC_REQUIRE(r == st::tuple_t(1, 2, 3, 4, 5, 6, 7));
}

/**
 * Tests the concatenation operation over tuple instances that may not own their
 * elements, that is, their elements might be references. The expected behaviour
 * of this operation is to produce a new tuple with the elements of both tuples.
 * @since 1.0
 */
TEST_CASE("concat-operation over tuples with references", "[concat][ref]")
{
    int array[] = { 4, 5, 6, 7 };

    auto t1 = st::tuple_t(1, 2, 3);
    auto t2 = st::tie(array);

    const auto r = st::concat(t1, t2);

    for (int i = 0; i < 4; ++i)
        array[i] += 2;

    STATIC_REQUIRE(decltype(r)::count == 7);
    REQUIRE(r == st::tuple_t(1, 2, 3, 6, 7, 8, 9));
}
