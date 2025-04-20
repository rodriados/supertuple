/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Test cases for the reverse operation over tuples.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2025-present Rodrigo Siqueira
 */
#include <string>

#include <supertuple/api.h>
#include <catch2/catch_test_macros.hpp>

namespace st = supertuple;

/**
 * Tests the reverse operation on tuples that own all elements.
 * The expected behavior of this operation is the creation of a new tuple containing
 * all the elements of the given tuple but in a reversed order.
 * @since 1.0
 */
TEST_CASE("reverse-operation over owning tuples", "[reverse][owning]")
{
    constexpr auto t = st::tuple_t(1, 2, 3, 4);
    constexpr auto r = st::reverse(t);

    STATIC_REQUIRE(decltype(r)::count == 4);
    STATIC_REQUIRE(r == st::tuple_t(4, 3, 2, 1));
}

/**
 * Tests the reverse operation for a moving tuple.
 * The expected behavior of this operation is the creation of a new tuple containing
 * all the moved elements of the given tuple but in reversed order.
 * @since 1.0
 */
TEST_CASE("reverse-operation over moved tuples", "[reverse][move]")
{
    auto s1 = std::string("hello");
    auto s2 = std::string("world");
    auto t = st::tuple_t(std::move(s1), 1, 2, std::move(s2));
    auto r = st::reverse(std::move(t));

    STATIC_REQUIRE(decltype(r)::count == 4);
    REQUIRE(r == st::tuple_t(std::string("world"), 2, 1, std::string("hello")));
}
