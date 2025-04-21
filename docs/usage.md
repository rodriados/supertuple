# Usage Guide

SuperTuple provides a functional programming approach to working with tuples in C++. This guide covers basic usage patterns and concepts.

**For more information:**
- [Tuple Types Guide](tuples.md) — Deep dive on `tuple_t`, `ntuple_t`, `pair_t`
- [Operations Reference](operations/README.md) — Detailed documentation for all 21 operations
- [Examples](examples.md) — Real-world usage scenarios

## Basic Concepts

### Tuple Creation

Create tuples using the `tuple_t` type:

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

// Create a tuple with different types
auto mixed_tuple = st::tuple_t(1, 2.5, "hello", true);

// Create a tuple with repeated types
auto int_tuple = st::ntuple_t<int, 3>(1, 2, 3);  // equivalent to tuple_t(1, 2, 3)
```

### Accessing Elements

Get tuple elements by index (0-based) or unique type:

```cpp
auto tuple = st::tuple_t(10, 20, 30);

// Get elements by index (0-based)
auto first = st::get<0>(tuple);   // 10
auto second = st::get<1>(tuple);  // 20

// Get by type (only works if type T is unique in the tuple)
auto value = st::get<int>(tuple);  // Ambiguous if multiple ints!

// Structured bindings (C++17) — recommended way
auto [a, b, c] = tuple;
```

**See also:** [get operation](operations/get.md)

### Modifying Elements

```cpp
auto tuple = st::tuple_t(1, 2, 3);

// Create new tuple (functional approach)
auto extended = st::append(tuple, 4);  // Results in (1, 2, 3, 4)

// Modify in-place (mutable approach)
st::set<1>(tuple, 42);  // tuple is now (1, 42, 3)

// Original tuple is unchanged (unless using set)
assert(tuple == st::tuple_t(1, 2, 3));
```

**See also:** [set](operations/set.md), [append](operations/append.md), [prepend](operations/prepend.md)

## Functional Operations

SuperTuple provides Haskell-inspired operations for working with tuples.

### Folding Operations

Folding reduces a tuple to a single value:

```cpp
auto numbers = st::tuple_t(1, 2, 3, 4);

// Left fold with initial value
auto sum = st::foldl(numbers, [](auto acc, auto x) { return acc + x; }, 0);  // 10

// Left fold without initial value (uses first element as base)
auto product = st::foldl(numbers, [](auto acc, auto x) { return acc * x; });  // 24

// Right fold
auto right_sum = st::foldr(numbers, [](auto x, auto acc) { return x + acc; }, 0);  // 10
```

### Mapping Operations

Apply functions to elements:

```cpp
auto numbers = st::tuple_t(1, 2, 3);

// Apply a function to each element
auto squared = st::apply(numbers, [](auto x) { return x * x; });  // tuple_t(1, 4, 9)

// Apply a binary function with a constant
auto added = st::apply(numbers, [](auto x, auto y) { return x + y; }, 10);  // tuple_t(11, 12, 13)
```

### Zipping Operations

Combine tuples element-wise:

```cpp
auto a = st::tuple_t(1, 2, 3);
auto b = st::tuple_t(4, 5, 6);

// Zip two tuples into a tuple of pairs
auto zipped = st::zip(a, b);  // tuple_t(tuple_t(1,4), tuple_t(2,5), tuple_t(3,6))

// Zip with a function
auto summed = st::zipwith(a, b, [](auto x, auto y) { return x + y; });  // tuple_t(5, 7, 9)
```

### List-like Operations

```cpp
auto tuple = st::tuple_t(1, 2, 3, 4, 5);

// Head and tail
auto first = st::head(tuple);      // 1
auto rest = st::tail(tuple);       // tuple_t(2, 3, 4, 5)

// Last and init
auto last_elem = st::last(tuple);  // 5
auto all_but_last = st::init(tuple);  // tuple_t(1, 2, 3, 4)

// Concatenation
auto a = st::tuple_t(1, 2);
auto b = st::tuple_t(3, 4);
auto combined = st::concat(a, b);  // tuple_t(1, 2, 3, 4)

// Appending/prepending single elements
auto appended = st::append(tuple, 6);    // tuple_t(1, 2, 3, 4, 5, 6)
auto prepended = st::prepend(tuple, 0);  // tuple_t(0, 1, 2, 3, 4, 5)

// Reverse
auto reversed = st::reverse(tuple);  // tuple_t(5, 4, 3, 2, 1)

// Select by indexes
auto selected = st::select(tuple, std::index_sequence<0, 2>{});  // tuple_t(1, 3)
```

Prefix scans (running totals):

```cpp
auto numbers = st::tuple_t(1, 2, 3, 4);

// Left scan
auto left_scan = st::scanl(numbers, [](auto acc, auto x) { return acc + x; }, 0);
// Results in tuple_t(0, 1, 3, 6, 10)

// Right scan
auto right_scan = st::scanr(numbers, [](auto x, auto acc) { return x + acc; }, 0);
// Results in tuple_t(10, 9, 7, 4, 0)
```

### Iteration

```cpp
auto tuple = st::tuple_t(1, 2, 3, 4);

// For-each (side effects)
st::foreach(tuple, [](auto x) {
    std::cout << x << " ";
});  // Prints: 1 2 3 4

// Reverse for-each (side effects)
int sum = 0;
st::rforeach(tuple, [&](auto x) {
    sum += x;
});  // sum == 10 (4 + 3 + 2 + 1)
```

## Advanced Examples

### Geometry Calculations

```cpp
#include <cmath>
#include <supertuple/api.h>

namespace st = supertuple;

template <size_t D>
using point_t = st::ntuple_t<double, D>;

template <size_t D>
double length(const point_t<D>& p) {
    return std::sqrt(st::foldl(
        st::apply(p, [](auto x) { return x * x; }),
        [](auto acc, auto x) { return acc + x; }
    ));
}

template <size_t D>
double distance(const point_t<D>& a, const point_t<D>& b) {
    return std::sqrt(st::foldl(
        st::zipwith(a, b, [](auto x, auto y) { return std::pow(y - x, 2); }),
        [](auto acc, auto x) { return acc + x; }
    ));
}

// Usage
auto p1 = point_t<3>(1, 2, 3);
auto p2 = point_t<3>(4, 5, 6);
auto len = length(p1);
auto dist = distance(p1, p2);
```

### Data Processing Pipeline

```cpp
auto data = st::tuple_t(1, 2, 3, 4, 5);

// Pipeline: filter even numbers, square them, sum
auto result = st::foldl(
    st::apply(
        st::tuple_t(2, 4),  // Filtered even numbers
        [](auto x) { return x * x; }  // Square each
    ),
    [](auto acc, auto x) { return acc + x; },  // Sum
    0
);  // Result: 4 + 16 = 20
```

## Performance Notes

- Most operations are `constexpr` and can be evaluated at compile-time
- Tuples have zero runtime overhead compared to structs with equivalent members
- Operations create new tuples rather than modifying existing ones
- The library leverages template metaprogramming for efficiency
