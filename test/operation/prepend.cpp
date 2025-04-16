/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Test cases for the prepend operation over tuples.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2025-present Rodrigo Siqueira
 */
#include <string>

#include <supertuple/api.h>
#include <catch2/catch_test_macros.hpp>

namespace st = supertuple;

/**
 * Tests the prepend operation on tuples that own all elements.
 * The expected behavior of this operation is the creation of a new tuple containing
 * all the elements of the given tuple and the new element at the beginning.
 * @since 1.0
 */
TEST_CASE("prepend-operation over owning tuples", "[prepend][owning]")
{
    constexpr auto t = st::tuple_t(1, 2, 3);
    constexpr auto r = st::prepend(t, 0);

    STATIC_REQUIRE(decltype(r)::count == 4);
    STATIC_REQUIRE(r == st::tuple_t(0, 1, 2, 3));
}

/**
 * Tests the prepend operation for a moving tuple and element.
 * The expected behavior of this operation is the creation of a new tuple containing
 * all the moved elements of the given tuple and the new element at the beginning.
 * @since 1.0
 */
TEST_CASE("prepend-operation over moved tuples", "[prepend][move]")
{
    auto s = std::string("hello");
    auto t = st::tuple_t(1, std::string("world"));
    auto r = st::prepend(std::move(t), std::move(s));

    STATIC_REQUIRE(decltype(r)::count == 3);
    REQUIRE(r == st::tuple_t(std::string("hello"), 1, std::string("world")));
}
