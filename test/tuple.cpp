/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Test cases for the tuple types.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#include <string>

#include <catch.hpp>
#include <supertuple.hpp>

namespace st = supertuple;

/**
 * Tests for the getters and setters of a simple tuple instance.
 * @since 1.0
 */
TEST_CASE("generic tuple methods", "[tuple]")
{
    auto t = st::tuple_t(4, 5., std::string("tuple"));

    REQUIRE(t.get<0>() == 4);
    REQUIRE(t.get<1>() == 5.);
    REQUIRE(t.get<2>() == "tuple");

    t.set<0>(7);
    t.set<1>(2.5);
    t.set<2>("newtuple");

    REQUIRE(t.get<0>() == 7);
    REQUIRE(t.get<1>() == 2.5);
    REQUIRE(t.get<2>() == "newtuple");
}

/**
 * Tests for the getters and setters of an n-tuple instance.
 * @since 1.0
 */
TEST_CASE("generic ntuple methods", "[ntuple]")
{
    auto t = st::ntuple_t(1, 2, 3, 4);

    REQUIRE(t.get<0>() == 1);
    REQUIRE(t.get<1>() == 2);
    REQUIRE(t.get<2>() == 3);
    REQUIRE(t.get<3>() == 4);

    t.set<0>(5);
    t.set<1>(6);
    t.set<2>(7);
    t.set<3>(8);

    REQUIRE(t.get<0>() == 5);
    REQUIRE(t.get<1>() == 6);
    REQUIRE(t.get<2>() == 7);
    REQUIRE(t.get<3>() == 8);
}

/**
 * Tests for the getters and setters of a pair instance.
 * @since 1.0
 */
TEST_CASE("generic pair methods", "[pair]")
{
    auto t = st::pair_t(4, std::string("pair"));

    REQUIRE(t.first() == 4);
    REQUIRE(t.second() == "pair");

    t.set<0>(5);
    t.set<1>("tuple");

    REQUIRE(t.first() == 5);
    REQUIRE(t.second() == "tuple");
}
