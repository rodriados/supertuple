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
auto tuple = st::tuple_t(1, 2.5, "hello", true);
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

**See also:** [get](operations/get.md)

### Modifying Elements

```cpp
auto tuple = st::tuple_t(1, 2, 3);

// Create new tuple
auto extended = st::append(tuple, 4);  // Results in (1, 2, 3, 4)

// Modify in-place
st::set<1>(tuple, 42);  // tuple is now (1, 42, 3)
```

**See also:** [set](operations/set.md), [append](operations/append.md), [prepend](operations/prepend.md)

## Functional Operations

SuperTuple provides Haskell-inspired operations for working with tuples.

### Folding Operations

Folding reduces a tuple to a single value:

```cpp
auto numbers = st::tuple_t(2, 3, 2);

auto add = [](auto x, auto y) { return x + y; };

// Left fold with initial value
auto foldl = st::foldl(numbers, add, 1);    // 1 + 2 + 3 + 2 = 8
auto scanl = st::scanl(numbers, add, 1);    // tuple_t(1, 3, 6, 8)

// Right fold without initial value
auto foldr = st::foldr(numbers, std::pow);  // (2 ^ (3 ^ 2)) = 512
auto scanr = st::scanr(numbers, std::pow);  // tuple_t(512, 9, 2)
```

**See also:** [fold](operations/fold.md), [scan](operations/scan.md)

### Mapping Operations

Apply functions to elements:

```cpp
auto numbers = st::tuple_t(1, 2, 3);

auto add = [](auto x, auto y) { return x + y; };
auto sqr = [](auto x) { return x * x; };

// Apply a function to each element
auto squared = st::apply(numbers, sqr);     // (1, 4, 9)

// Apply a binary function with a constant
auto added = st::apply(numbers, add, 10);   // (11, 12, 13)
```

**See also:** [apply](operations/apply.md)

### Zipping Operations

Combine tuples element-wise:

```cpp
auto a = st::tuple_t(1, 2, 3);
auto b = st::tuple_t(4, 5, 6);

auto add = [](auto x, auto y) { return x + y; };

// Zip two tuples into a tuple of pairs
auto zipped = st::zip(a, b);            // ((1,4), (2,5), (3,6))

// Zip with a function
auto summed = st::zipwith(a, b, add);   // (5, 7, 9)
```

**See also:** [zip](operations/zip.md), [zipwith](operations/zipwith.md)

### List-like Operations
Modify tuples like lists:

```cpp
auto tuple = st::tuple_t(1, 2, 3, 4, 5);

// Head and tail
auto head = st::head(tuple);            // 1
auto tail = st::tail(tuple);            // (2, 3, 4, 5)

// Last and init
auto init = st::init(tuple);            // (1, 2, 3, 4)
auto last = st::last(tuple);            // 5

// Concatenation
auto a = st::tuple_t(1, 2);
auto b = st::tuple_t(3, 4);
auto concat = st::concat(a, b);         // (1, 2, 3, 4)

// Append/prepend single elements
auto append = st::append(tuple, 6);     // (1, 2, 3, 4, 5, 6)
auto prepend = st::prepend(tuple, 0);   // (0, 1, 2, 3, 4, 5)

// Reverse
auto reverse = st::reverse(tuple);      // (5, 4, 3, 2, 1)

// Select by indexes
auto select = st::select(tuple, std::index_sequence<0, 2>());   // (1, 3)
```

**See also:** [head](operations/head.md), [last](operations/last.md), [tail](operations/tail.md),
[init](operations/init.md), [concat](operations/concat.md), [reverse](operations/reverse.md),
[select](operations/select.md)

### Iterating Operations
Iterate over elements:

```cpp
auto tuple = st::tuple_t(1, 2, 3, 4);

auto print = [](auto x) { std::cout << x << " "; };

// Iterate elements with side-effects
st::foreach(tuple, print);  // Prints: 1 2 3 4
st::rforeach(tuple, print); // Prints: 4 3 2 1
```

**See also:** [foreach](operations/foreach.md)

## Advanced Examples

For advanced examples, please check [examples](examples.md).

## Performance Notes

- Most operations are `constexpr` and can be evaluated at compile-time
- Tuples have zero runtime overhead compared to structs with equivalent members
- Operations create new tuples rather than modifying existing ones
- The library leverages template metaprogramming for efficiency
