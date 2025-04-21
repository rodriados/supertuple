# Examples

This document provides practical examples demonstrating SuperTuple usage in various scenarios.

## Basic Usage

### Creating and Accessing Tuples

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

int main() {
    // Create tuples
    auto numbers = st::tuple_t(1, 2, 3, 4, 5);
    auto mixed = st::tuple_t(42, 3.14, "hello", true);

    // Access elements
    auto first = st::get<0>(numbers);     // 1
    auto third = st::get<2>(numbers);     // 3

    // Structured bindings
    auto [a, b, c, d, e] = numbers;

    // Modify elements (creates new tuple)
    auto modified = st::set<2>(numbers, 99);  // tuple_t(1, 2, 99, 4, 5)

    return 0;
}
```

### List Operations

```cpp
auto data = st::tuple_t(10, 20, 30, 40, 50);

// Extract parts
auto first = st::head(data);        // 10
auto rest = st::tail(data);         // tuple_t(20, 30, 40, 50)
auto last_elem = st::last(data);    // 50
auto init_part = st::init(data);    // tuple_t(10, 20, 30, 40)

// Build new tuples
auto appended = st::append(data, 60);     // tuple_t(10, 20, 30, 40, 50, 60)
auto prepended = st::prepend(data, 0);    // tuple_t(0, 10, 20, 30, 40, 50)

// Combine tuples
auto a = st::tuple_t(1, 2, 3);
auto b = st::tuple_t(4, 5, 6);
auto combined = st::concat(a, b);         // tuple_t(1, 2, 3, 4, 5, 6)

// Reverse
auto reversed = st::reverse(data);         // tuple_t(50, 40, 30, 20, 10)
```

## Functional Programming Patterns

### Folding for Aggregation

```cpp
auto numbers = st::tuple_t(1, 2, 3, 4, 5);

// Sum all elements
auto sum = st::foldl(numbers, [](auto acc, auto x) { return acc + x; }, 0);  // 15

// Product of all elements
auto product = st::foldl(numbers, [](auto acc, auto x) { return acc * x; }); // 120

// Find maximum
auto max_val = st::foldl(numbers, [](auto acc, auto x) { return std::max(acc, x); }, INT_MIN);

// Check if all elements are even
auto all_even = st::foldl(numbers, [](auto acc, auto x) { return acc && (x % 2 == 0); }, true);

// Concatenate strings
auto words = st::tuple_t("Hello", " ", "World", "!");
auto sentence = st::foldl(words, [](auto acc, auto x) { return acc + x; }, std::string(""));
```

### Mapping Transformations

```cpp
auto numbers = st::tuple_t(1, 2, 3, 4, 5);

// Square each element
auto squared = st::apply(numbers, [](auto x) { return x * x; });  // tuple_t(1, 4, 9, 16, 25)

// Convert to strings
auto strings = st::apply(numbers, [](auto x) { return std::to_string(x); });

// Add 10 to each element
auto added = st::apply(numbers, [](auto x, auto y) { return x + y; }, 10);  // tuple_t(11, 12, 13, 14, 15)

// Convert types
auto doubles = st::convert<double>(numbers);  // tuple_t(1.0, 2.0, 3.0, 4.0, 5.0)
```

### Zipping for Element-wise Operations

```cpp
auto a = st::tuple_t(1, 2, 3, 4);
auto b = st::tuple_t(5, 6, 7, 8);

// Element-wise addition
auto sums = st::zipwith(a, b, [](auto x, auto y) { return x + y; });      // tuple_t(6, 8, 10, 12)

// Element-wise multiplication
auto products = st::zipwith(a, b, [](auto x, auto y) { return x * y; });  // tuple_t(5, 12, 21, 32)

// Create pairs
auto pairs = st::zip(a, b);  // tuple_t(tuple_t(1,5), tuple_t(2,6), tuple_t(3,7), tuple_t(4,8))

// Distance calculation
auto x_coords = st::tuple_t(1.0, 2.0, 3.0);
auto y_coords = st::tuple_t(4.0, 5.0, 6.0);
auto distances = st::zipwith(x_coords, y_coords,
    [](auto x, auto y) { return std::sqrt(x*x + y*y); });
```

### Scanning for Running Totals

```cpp
auto values = st::tuple_t(1, 2, 3, 4);

// Running sum (left to right)
auto running_sum = st::scanl(values, [](auto acc, auto x) { return acc + x; }, 0);
// Result: tuple_t(0, 1, 3, 6, 10)

// Running product
auto running_product = st::scanl(values, [](auto acc, auto x) { return acc * x; }, 1);
// Result: tuple_t(1, 1, 2, 6, 24)

// Running maximum
auto running_max = st::scanl(values, [](auto acc, auto x) { return std::max(acc, x); }, INT_MIN);
// Result: tuple_t(INT_MIN, 1, 2, 3, 4)
```

## Advanced Examples

### Geometry Library

```cpp
#include <cmath>
#include <supertuple/api.h>

namespace st = supertuple;
namespace geometry {

// Point in N-dimensional space
template <size_t N>
using point_t = st::ntuple_t<double, N>;

// Vector length (Euclidean norm)
template <size_t N>
constexpr double length(const point_t<N>& p) {
    return std::sqrt(st::foldl(
        st::apply(p, [](auto x) { return x * x; }),
        [](auto acc, auto x) { return acc + x; }
    ));
}

// Euclidean distance between points
template <size_t N>
constexpr double distance(const point_t<N>& a, const point_t<N>& b) {
    return std::sqrt(st::foldl(
        st::zipwith(a, b, [](auto x, auto y) { return (y - x) * (y - x); }),
        [](auto acc, auto x) { return acc + x; }
    ));
}

// Dot product
template <size_t N>
constexpr double dot(const point_t<N>& a, const point_t<N>& b) {
    return st::foldl(
        st::zipwith(a, b, [](auto x, auto y) { return x * y; }),
        [](auto acc, auto x) { return acc + x; },
        0.0
    );
}

// Vector addition
template <size_t N>
constexpr point_t<N> add(const point_t<N>& a, const point_t<N>& b) {
    return st::zipwith(a, b, [](auto x, auto y) { return x + y; });
}

// Scalar multiplication
template <size_t N>
constexpr point_t<N> scale(const point_t<N>& p, double s) {
    return st::apply(p, [](auto x, auto s) { return x * s; }, s);
}

} // namespace geometry

// Usage
int main() {
    auto p1 = geometry::point_t<3>(1, 2, 3);
    auto p2 = geometry::point_t<3>(4, 5, 6);

    auto len = geometry::length(p1);           // sqrt(14)
    auto dist = geometry::distance(p1, p2);   // sqrt(27)
    auto dot_prod = geometry::dot(p1, p2);    // 32
    auto sum = geometry::add(p1, p2);         // (5, 7, 9)
    auto scaled = geometry::scale(p1, 2.0);  // (2, 4, 6)

    return 0;
}
```

### Data Processing Pipeline

```cpp
#include <vector>
#include <supertuple/api.h>

namespace st = supertuple;

// Example: Process a collection of data points
struct DataPoint {
    double x, y;
    std::string label;
};

std::vector<DataPoint> process_data(const std::vector<DataPoint>& data) {
    // Convert to tuple representation for functional processing
    // (This is a simplified example - in practice you'd work with tuples directly)

    // Example pipeline: filter, transform, aggregate
    auto values = st::tuple_t(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    // Filter even numbers
    auto evens = st::tuple_t(2, 4, 6, 8, 10);  // In real code, you'd filter programmatically

    // Transform: square each value
    auto squared = st::apply(evens, [](auto x) { return x * x; });

    // Aggregate: sum of squares
    auto sum_squares = st::foldl(squared, [](auto acc, auto x) { return acc + x; }, 0);

    // Running statistics
    auto running_sums = st::scanl(evens, [](auto acc, auto x) { return acc + x; }, 0);

    return data;  // Placeholder
}
```

### Compile-time Computations

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

// Fibonacci sequence at compile time
template <size_t N>
constexpr auto fibonacci() {
    if constexpr (N == 0) return st::tuple_t(0);
    else if constexpr (N == 1) return st::tuple_t(0, 1);
    else {
        constexpr auto prev = fibonacci<N-1>();
        constexpr auto last_two = st::tail(st::init(prev));
        constexpr auto next_val = st::foldl(last_two, [](auto acc, auto x) { return acc + x; }, 0);
        return st::append(prev, next_val);
    }
}

// Factorial computation
constexpr auto factorial_tuple = st::tuple_t(1, 2, 3, 4, 5);
constexpr auto factorials = st::scanl(factorial_tuple,
    [](auto acc, auto x) { return acc * x; }, 1);
// Result: tuple_t(1, 1, 2, 6, 24, 120)

// Prime checking (simplified)
constexpr bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    constexpr auto divisors = st::tuple_t(5, 7, 11, 13, 17, 19, 23);
    return st::foldl(
        st::apply(divisors, [n](auto d) { return n % d != 0; }),
        [](auto acc, auto x) { return acc && x; },
        true
    );
}

int main() {
    constexpr auto fib10 = fibonacci<10>();  // Computed at compile time
    static_assert(st::get<10>(fib10) == 55);

    static_assert(is_prime(17) == true);
    static_assert(is_prime(18) == false);

    return 0;
}
```

### Working with Arrays

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

void array_example() {
    double arr[5] = {1.0, 2.0, 3.0, 4.0, 5.0};

    // Create tuple referencing array
    auto tuple = st::tie(arr);

    // Modify through tuple (affects original array)
    auto modified = st::set<2>(tuple, 99.0);
    // arr[2] is now 99.0

    // Apply operations
    auto squared = st::apply(tuple, [](auto x) { return x * x; });

    // Process array elements functionally
    st::foreach(tuple, [](auto& x) {
        x *= 2;  // Double each element in place
    });
}
```

These examples demonstrate the versatility of SuperTuple for various programming tasks, from simple data manipulation to complex mathematical computations and compile-time programming.
