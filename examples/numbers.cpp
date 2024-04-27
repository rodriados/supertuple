/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file An example usage with tuples of numbers.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#include <cassert>
#include <cmath>

#include <supertuple.h>

namespace st = supertuple;

/**
 * A generic addition function to fold numeric tuples with.
 * @param x The first addition operand.
 * @param y The second addition operand.
 * @return The addition result.
 */
inline static constexpr auto add =
    [](auto x, auto y) { return x + y; };

/**
 * This example uses tuples containing numeric types and demonstrates their use
 * by showing the implementation of simple algorithms using folding operations.
 * @since 1.0
 */
int main()
{
    SUPERTUPLE_EXAMPLE (1) {
        /// Example #1: Tuple of integers.
        /// Perform a left-fold reduction to sum integers.
        auto t = st::tuple_t(1, 2, 3, 4, 5);
        auto r = st::foldl(t, add);
        assert(r == 15);
    }

    SUPERTUPLE_EXAMPLE (2) {
        /// Example #2: Tuple of floats.
        /// Perform a left-fold reduction to sum floats.
        auto t = st::tuple_t(2.f, 4.f, 6.f, 8.f, 10.f);
        auto r = st::foldl(t, add);
        assert(r == 30.);
    }

    SUPERTUPLE_EXAMPLE (3) {
        /// Example #3: Tuple of doubles.
        /// Perform a left-fold reduction with pow-operator on doubles.
        auto t = st::tuple_t(4., 3., 2.);
        auto r = st::foldl(t, pow);
        assert(r == 4096.);
    }

    SUPERTUPLE_EXAMPLE (4) {
        /// Example #4: Tuple of doubles.
        /// Perform a right-fold reduction with pow-operator on doubles.
        auto t = st::tuple_t(4., 3., 2.);
        auto r = st::foldr(t, pow);
        assert(r == 262144.);
    }

    return 0;
}
