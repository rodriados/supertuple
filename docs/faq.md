# Frequently Asked Questions (FAQ)

Common questions about SuperTuple and their answers.

## General Questions

### What is SuperTuple and why should I use it?

**Q:** What is SuperTuple?

**A:** SuperTuple is a C++17 header-only library providing lightweight, type-safe tuples with Haskell-inspired functional operations. Unlike `std::tuple`, SuperTuple emphasizes:
- Zero runtime overhead through constexpr evaluation
- Composable functional operations (fold, map, zip, etc.)
- Clean, expressive syntax
- C++17+ features for better performance

### How does SuperTuple differ from std::tuple?

**Q:** What's the difference between SuperTuple and `std::tuple`?

**A:**

| Feature | SuperTuple | std::tuple |
|---------|-----------|----------|
| **Functional Ops** | Built-in (fold, zip, apply) | Must implement manually |
| **Constexpr** | Fully constexpr evaluated | Limited constexpr support |
| **Syntax** | Clean, Haskell-like | verbose std::get<> |
| **Size** | Single header | Part of standard library |
| **Performance** | Zero overhead | Similar with optimizations |
| **Learning Curve** | Functional concepts needed | Familiar C++ patterns |

**Use SuperTuple if:** You want functional programming or compile-time computation.
**Use std::tuple if:** You prefer standard library familiarity.

### Is SuperTuple production-ready?

**Q:** Can I use SuperTuple in production code?

**A:** Yes, SuperTuple is stable and suitable for production. Features:
- Comprehensive test suite
- Header-only, no dependency maintenance
- Mature API design based on functional programming principles
- Used in research, academic, and commercial projects

## Installation & Setup

### How do I install SuperTuple?

**Q:** How do I install SuperTuple?

**A:** SuperTuple is header-only. Three options:

1. **Manual:** Copy `supertuple/` folder into your project
2. **CMake:** Use `FetchContent` or `find_package`
3. **Package:** Install via package manager (if available)

See [Installation Guide](installation.md) for details.

### What C++ version does SuperTuple require?

**Q:** What C++ standard is required?

**A:** SuperTuple requires **C++17 or later** due to:
- Fold expressions (`(op, ...)`)
- Structured bindings (`auto [x, y] = tuple`)
- `constexpr` features
- Template improvements

Compile with `-std=c++17` or higher.

## Usage & API

### How do I create tuples?

**Q:** How do I create a SuperTuple?

**A:**

```cpp
namespace st = supertuple;

// Heterogeneous tuple
auto mixed = st::tuple_t(1, 2.5, "hello");  // Different types

// Homogeneous tuple
auto point = st::ntuple_t<double, 3>(1.0, 2.0, 3.0);  // Same type

// Pair
auto pair = st::pair_t(42, "value");  // Exactly 2 elements

// Empty
auto empty = st::tuple_t<>();
```

### How do I access tuple elements?

**Q:** How do I get elements from a tuple?

**A:**

```cpp
auto tuple = st::tuple_t(1, 2.5, "hello");

// By index (0-based)
auto first = st::get<0>(tuple);   // 1

// By type (if unique)
auto str = st::get<std::string>(tuple);  // Won't work - const char*

// Structured bindings (C++17)
auto [a, b, c] = tuple;

// With iterators/foreach
st::foreach(tuple, [](auto elem) {
    std::cout << elem << " ";
});
```

### How do I modify tuple elements?

**Q:** Can I modify tuple elements?

**A:** Two approaches:

```cpp
auto tuple = st::tuple_t(1, 2, 3);

// 1. Create new tuple (functional)
auto modified = st::append(tuple, 4);  // (1, 2, 3, 4)

// 2. In-place modification (mutable)
st::set<0>(tuple, 100);  // tuple is now (100, 2, 3)
```

**Note:** Most operations create new tuples (immutable style), except `set`.

### What are the main operations?

**Q:** What operations are available?

**A:** 21 operations organized into categories:

- **Access:** get, set, tie
- **List:** head, tail, last, init, append, prepend, concat, reverse, select
- **Folding:** fold, scan
- **Transform:** apply, zip, zipwith, convert
- **Iteration:** foreach, forward

See [Operations Reference](operations/README.md) for details.

## Functional Programming

### What's the difference between fold and scan?

**Q:** When should I use `fold` vs `scan`?

**A:**

```cpp
auto data = st::tuple_t(1, 2, 3, 4);

// fold: returns only final result
auto sum = st::foldl(data, [](auto a, auto b) { return a + b; }, 0);
// Result: 10 (single value)

// scan: returns intermediate steps
auto running = st::scanl(data, [](auto a, auto b) { return a + b; }, 0);
// Result: (0, 1, 3, 6, 10) (tuple)
```

**Use `fold`:** Need final aggregate value.
**Use `scan`:** Need intermediate values or running totals.

### How do I compose operations?

**Q:** Can I chain tuple operations together?

**A:** Yes, operations compose naturally:

```cpp
auto data = st::tuple_t(1, 2, 3, 4, 5);

// Composition: apply → fold
auto sum_of_squares = st::foldl(
    st::apply(data, [](auto x) { return x * x; }),
    [](auto acc, auto x) { return acc + x; },
    0
);

// Composition: zipwith → fold (dot product)
auto a = st::tuple_t(1, 2, 3);
auto b = st::tuple_t(4, 5, 6);
auto dot = st::foldl(
    st::zipwith(a, b, [](auto x, auto y) { return x * y; }),
    [](auto acc, auto p) { return acc + p; },
    0
);
```

### What's constexpr and why is it important?

**Q:** What's constexpr and how does it relate to SuperTuple?

**A:** `constexpr` means code executes at **compile time** when possible:

```cpp
// Computed at compile time
constexpr auto result = st::foldl(
    st::tuple_t(1, 2, 3),
    [](auto a, auto b) { return a + b; },
    0
);

static_assert(result == 6);  // Verified at compile time!

// Benefits:
// - Zero runtime overhead
// - Results verified before execution
// - Constants available for template metaprogramming
```

All SuperTuple operations are `constexpr`.

## Operators & Operations

### How do I use apply?

**Q:** What does `apply` do and how do I use it?

**A:** `apply` transforms each element:

```cpp
auto data = st::tuple_t(1, 2, 3);

// Double each element
auto doubled = st::apply(data, [](auto x) { return x * 2; });
// Result: (2, 4, 6)

// With extra arguments
auto scaled = st::apply(data, [](auto x, int s) { return x * s; }, 10);
// Result: (10, 20, 30)

// Type conversion
auto as_double = st::apply(data, [](auto x) { return (double)x; });
// Result: (1.0, 2.0, 3.0)
```

### How do I use zip/zipwith?

**Q:** What's the difference between `zip` and `zipwith`?

**A:**

```cpp
auto a = st::tuple_t(1, 2, 3);
auto b = st::tuple_t(10, 20, 30);

// zip: creates pairs
auto pairs = st::zip(a, b);
// Result: ((1,10), (2,20), (3,30))

// zipwith: applies custom function
auto sums = st::zipwith(a, b, [](auto x, auto y) { return x + y; });
// Result: (11, 22, 33)
```

**Use `zip`:** Need pairs, will process later.
**Use `zipwith`:** Compute combined values immediately.

### How do I iterate over a tuple?

**Q:** How do I loop over tuple elements?

**A:**

```cpp
auto data = st::tuple_t("hello", 42, 3.14);

// Forward iteration
st::foreach(data, [](auto elem) {
    std::cout << elem << " ";  // hello 42 3.14
});

// Reverse iteration
st::rforeach(data, [](auto elem) {
    std::cout << elem << " ";  // 3.14 42 hello
});

// Modify in place
auto mutable_data = st::tuple_t(1, 2, 3);
st::foreach(mutable_data, [](auto& elem) {
    elem *= 2;  // mutable_data is now (2, 4, 6)
});
```

## Type System

### Can I have duplicate types in a tuple?

**Q:** What happens if a tuple has duplicate types?

**A:** You can have duplicates, but **type-based access breaks**:

```cpp
auto tuple = st::tuple_t(1, 2.5, 3);  // Two ints

// Type-based access fails - which int?
// auto x = st::get<int>(tuple);  // Error: ambiguous!

// Use index-based access instead
auto first = st::get<0>(tuple);   // 1
auto third = st::get<2>(tuple);   // 3

// This works - doubles is unique
auto d = st::get<double>(tuple);  // 2.5
```

**Best Practice:** Use homogeneous tuples (`ntuple_t`) if all elements are same type.

### When should I use ntuple_t vs tuple_t?

**Q:** Should I use `ntuple_t<T, N>` or `tuple_t<T, T, T>`?

**A:**

```cpp
// For vectors/points: use ntuple_t
auto point = st::ntuple_t<double, 3>(1.0, 2.0, 3.0);  // Clearer intent
auto packed = st::tuple_t(1.0, 2.0, 3.0);              // Also works

// Benefits of ntuple_t:
// - Cleaner code
// - Better compiler understanding
// - More efficient handling
// - Semantic clarity ("I have a 3-element vector")
```

**Use `ntuple_t`:** Homogeneous collections (vectors, points, arrays).
**Use `tuple_t`:** Mixed types or small fixed tuples.

## Performance & Optimization

### Is SuperTuple fast?

**Q:** What's the performance of SuperTuple?

**A:** SuperTuple achieves **zero runtime overhead** through constexpr and inlining:

```cpp
// SuperTuple
auto sum = st::foldl(data, [](auto a, auto b) { return a + b; }, 0);

// Hand-written
int sum_manual = 0;
for (auto x : data) sum_manual += x;

// Result: Identical machine code with -O2/-O3 optimization
```

See [Performance Guide](performance.md) for details.

### How can I optimize my code?

**Q:** How do I make my SuperTuple code faster?

**A:** Best practices:

1. **Enable optimizations:** `-O2` or `-O3`
2. **Use constexpr:** Compute at compile time when possible
3. **Use move semantics:** `st::append(std::move(tuple), elem)`
4. **Compose operations:** Avoid intermediate tuples
5. **Use ntuple_t:** For numeric vectors
6. **Inline functions:** Mark as `inline` or `constexpr`

```cpp
// Good
constexpr auto result = st::foldl(st::apply(data, f1), f2, 0);

// Avoid
auto r1 = st::apply(data, f1);
auto r2 = st::foldl(r1, f2, 0);
```

## CUDA & GPU Programming

### Does SuperTuple work on CUDA?

**Q:** Can I use SuperTuple in CUDA kernels?

**A:** Yes! SuperTuple tuples work in device code:

```cpp
__global__ void kernel() {
    namespace st = supertuple;

    // Create and use tuples in device code
    auto point = st::ntuple_t<double, 3>(1.0, 2.0, 3.0);

    auto squared = st::apply(point, [](auto x) { return x * x; });

    auto sum = st::foldl(squared, [](auto a, auto b) { return a + b; }, 0.0);
}
```

See [CUDA Support](advanced.md#cuda-support) section for details.

## Troubleshooting

### I'm getting template compilation errors

**Q:** What does "template instantiation failed" mean?

**A:** Common causes:

1. **Wrong function signature**
   ```cpp
   // Wrong: lambda returns void
   auto result = st::foldl(data, [](auto a, auto b) { a + b; }, 0);

   // Right: lambda returns value
   auto result = st::foldl(data, [](auto a, auto b) { return a + b; }, 0);
   ```

2. **Index out of bounds**
   ```cpp
   auto t = st::tuple_t(1, 2);
   // auto x = st::get<5>(t);  // Error: index 5 doesn't exist!
   ```

3. **Ambiguous type access**
   ```cpp
   auto t = st::tuple_t(1, 2, 3.0);
   // auto x = st::get<int>(t);  // Error: which int?
   // Use index instead
   auto x = st::get<0>(t);
   ```

### Compilation is very slow

**Q:** Why does my code compile slowly?

**A:** Large/complex tuple operations increase compile time:

- Break compositions into intermediate steps
- Use `ntuple_t` instead of repeated `tuple_t`
- Reduce tuple sizes
- Use forward declarations

See [Performance Guide](performance.md#deep-template-nesting--slow-compilation) for solutions.

## Contributing & Support

### How do I report bugs?

**Q:** How do I report issues?

**A:** Visit the project repository and file an issue with:
- What you tried
- What you expected
- What happened instead
- Minimal reproducible example
- Compiler and version info

### Can I contribute?

**Q:** How can I contribute to SuperTuple?

**A:** See [Contributing Guide](Contributing.md) for details on:
- Development setup
- Code style
- Testing requirements
- Submission process

---

## See Also

- [Getting Started](usage.md)
- [Operations Reference](operations/README.md)
- [Tuple Types](tuples.md)
- [API Reference](api.md)
- [Performance Guide](performance.md)
- [Advanced Topics](advanced.md)
