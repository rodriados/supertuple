/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Test cases for the append operation over tuples.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2025-present Rodrigo Siqueira
 */
#include <string>

#include <supertuple/api.h>
#include <catch2/catch_test_macros.hpp>

namespace st = supertuple;

/**
 * Tests the append operation on tuples that own all elements.
 * The expected behavior of this operation is the creation of a new tuple containing
 * all the elements of the given tuple and the new element at the end.
 * @since 1.0
 */
TEST_CASE("append-operation over owning tuples", "[append][owning]")
{
    constexpr auto t = st::tuple_t(1, 2, 3);
    constexpr auto r = st::append(t, 4);

    STATIC_REQUIRE(decltype(r)::count == 4);
    STATIC_REQUIRE(r == st::tuple_t(1, 2, 3, 4));
}

/**
 * Tests the append operation for a moving tuple and element.
 * The expected behavior of this operation is the creation of a new tuple containing
 * all the moved elements of the given tuple and the new element at the end.
 * @since 1.0
 */
TEST_CASE("append-operation over moved tuples", "[append][move]")
{
    auto s = std::string("hello");
    auto t = st::tuple_t(1, std::string("world"));
    auto r = st::append(std::move(t), std::move(s));

    STATIC_REQUIRE(decltype(r)::count == 3);
    REQUIRE(r == st::tuple_t(1, std::string("world"), std::string("hello")));
}

