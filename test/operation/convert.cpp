/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Test cases for the convert operation over tuples.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2025-present Rodrigo Siqueira
 */
#include <string>

#include <supertuple/api.h>
#include <catch2/catch_test_macros.hpp>

namespace st = supertuple;

/**
 * Tests the convert operation to a compatible struct.
 * The expected behavior of this operation is to be able to convert a generic tuple
 * into a compatible struct type.
 * @since 1.0
 */
TEST_CASE("convert-operation to compatible struct", "[convert]")
{
    struct test_target_t {
        int i;
        float f;
        char c;
    };

    constexpr auto t = st::tuple_t(1, 2.0f, 'a');
    constexpr test_target_t r = st::convert(t);

    STATIC_REQUIRE(r.i == 1);
    STATIC_REQUIRE(r.f == 2.0f);
    STATIC_REQUIRE(r.c == 'a');
}

/**
 * Tests the convert operation with moved tuples to a compatible struct.
 * The expected behavior of this operation is to be able to convert a generic tuple
 * into a temporary owning struct so it can then be converted into a compatible type.
 * @since 1.0
 */
TEST_CASE("convert-operation with moved tuples to struct", "[convert][move]")
{
    struct test_target_t {
        int i;
        float f;
        std::string s;
    };

    auto s = std::string("hello");
    auto t = st::tuple_t(42, 3.14f, s);
    auto r = test_target_t(st::convert(std::move(t)));

    REQUIRE(r.i == 42);
    REQUIRE(r.f == 3.14f);
    REQUIRE(r.s == "hello");
}
