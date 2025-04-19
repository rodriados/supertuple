/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Test cases for casting tuples with standard C++ types.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2025-present Rodrigo Siqueira
 */
#include <supertuple/api.h>
#include <catch2/catch_test_macros.hpp>

namespace st = supertuple;

/**
 * Tests the casting operation from the standard C++ tuple type into a supertuple.
 * The expected behavior of this operation is that both the element types and their
 * corresponding values are correctly acquired from the standard C++ tuple instance.
 * @since 1.2
 */
TEST_CASE("cast from std tuple to supertuple", "[cast][ref]")
{
    SECTION("simple tuples are converted") {
        auto tuple = std::tuple(1, 2.3, 'c');
        auto result = st::from_std(tuple);

        STATIC_REQUIRE(
            std::tuple_size_v<decltype(result)> ==
            std::tuple_size_v<decltype(tuple)>);

        REQUIRE(st::get<0>(result) == 1);
        REQUIRE(st::get<1>(result) == 2.3);
        REQUIRE(st::get<2>(result) == 'c');
    }

    SECTION("reference types are preserved") {
        int array[3] = {1, 2, 3};

        auto tuple = std::tie(array[0], array[1], array[2]);
        auto result = st::from_std(tuple);

        STATIC_REQUIRE(
            std::tuple_size_v<decltype(result)> ==
            std::tuple_size_v<decltype(tuple)>);

        array[1] = 7;

        REQUIRE(st::get<0>(result) == 1);
        REQUIRE(st::get<1>(result) == 7);
        REQUIRE(st::get<2>(result) == 3);
    }
}

/**
 * Tests the casting operation from a supertuple into the standard C++ tuple type.
 * The expected behavior of this operation is that both the element types and their
 * corresponding values are correctly acquired from the supertuple instance.
 * @since 1.2
 */
TEST_CASE("cast from supertuple to std tuple", "[cast][ref]")
{
    SECTION("simple tuples are converted") {
        auto tuple = st::tuple_t(1, 2.3, 'c');
        auto result = st::to_std(tuple);

        STATIC_REQUIRE(
            std::tuple_size_v<decltype(result)> ==
            std::tuple_size_v<decltype(tuple)>);

        REQUIRE(std::get<0>(result) == 1);
        REQUIRE(std::get<1>(result) == 2.3);
        REQUIRE(std::get<2>(result) == 'c');
    }

    SECTION("reference types are preserved") {
        int array[3] = {1, 2, 3};

        auto tuple = st::tie(array);
        auto result = st::to_std(tuple);

        STATIC_REQUIRE(
            std::tuple_size_v<decltype(result)> ==
            std::tuple_size_v<decltype(tuple)>);

        array[1] = 7;

        REQUIRE(std::get<0>(result) == 1);
        REQUIRE(std::get<1>(result) == 7);
        REQUIRE(std::get<2>(result) == 3);
    }
}
