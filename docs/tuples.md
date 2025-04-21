# Tuple Types Guide

This guide provides in-depth coverage of SuperTuple's tuple types and how to choose between them.

## Core Tuple Types

SuperTuple provides three main tuple type abstractions:

### 1. `tuple_t<T...>` — Heterogeneous Tuples

A general-purpose tuple that can hold elements of different types.

```cpp
auto mixed = st::tuple_t(1, 3.14, "hello", true);
// tuple_t<int, double, const char*, bool>
```

**Characteristics:**
- Store elements of any types in a fixed-size collection
- Each element type is part of the type signature
- Access by index or by unique type
- Most flexible tuple type
- Zero runtime overhead

**When to use:**
- Grouping heterogeneous data (e.g., configuration, return values)
- When elements have distinct types
- Building type-safe data structures
- Compile-time polymorphism

**Key Members:**
```cpp
static constexpr size_t count;  // Number of elements

T& get<int>();                  // Access by index
T& get<T>();                    // Access by unique type
void set<int>(value);           // Modify by index
void set<T>(value);             // Modify by unique type
```

**Example:**
```cpp
auto config = st::tuple_t("app_name", 8080, true);

auto app_name = st::get<0>(config);  // By index
auto port = st::get<int>(config);    // By type (unique)
```

---

### 2. `ntuple_t<T, N>` — Homogeneous Tuples

A tuple containing exactly `N` elements of the same type `T`. Useful for fixed-size numeric collections.

```cpp
auto point_3d = st::ntuple_t(1.0, 2.0, 3.0);
// ntuple_t<double, 3>
```

**Characteristics:**
- All elements have the same type
- Fixed size known at compile time
- Optimized for uniform-type collections
- Similar to `std::array<T, N>` but with functional operations
- Zero runtime overhead

**When to use:**
- Fixed-size numeric vectors/points
- Coordinates in N-dimensional space
- Homogeneous collections where type uniformity is desired
- Geometry, signal processing, physics calculations

**Key Members:**
```cpp
static constexpr size_t count;  // Always equals N

T& get<int>();                  // Access by index (same as array)
void set<int>(value);           // Modify by index
```

**Example:**
```cpp
namespace st = supertuple;

auto point_2d = st::ntuple_t(3.0, 4.0);
auto point_3d = st::ntuple_t(1.0, 2.0, 3.0);
auto point_9d = st::ntuple_t(...9 values...);

auto scaled = st::apply(point_2d, [](auto x) { return x * 2.0; });
```

---

### 3. `pair_t<T, U>` — Binary Tuples

A specialized tuple containing exactly two elements of types `T` and `U`. Often used as the pairing result from `zip` operations.

```cpp
auto coord = st::pair_t(42, 3.14);
// pair_t<int, double>
```

**Characteristics:**
- Exactly 2 elements
- Lightweight container for dual values
- Inherits from `tuple_t<T, U>`
- All tuple operations apply
- Zero runtime overhead

**When to use:**
- Pairing two values (result of `zip` operations)
- Key-value associations
- Coordinates or dual measurements
- Result of binary operations

**Key Members:**
```cpp
static constexpr size_t count = 2;

T& get<int>();
T& get<T>();            // First element type
U& get<U>();            // Second element type
void set<int>(value);
void set<T>(value);     // First element type
void set<U>(value);     // Second element type
```

**Example:**
```cpp
auto coord = st::pair_t(42, 3.14);
auto [x, y] = coord;
```

---

## Structured Bindings (C++17)

All tuple types support C++17 structured bindings for convenient decomposition:

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

// Heterogeneous tuple
auto config = st::tuple_t(42, "app", 3.14);
auto [code, name, version] = config;

// Homogeneous tuple
auto point = st::ntuple_t(1.0, 2.0, 3.0);
auto [x, y, z] = point;

// Pair
auto coord = st::pair_t(10, 20);
auto [a, b] = coord;
```

This enables natural variable extraction while maintaining type safety.

---

## Tuple Construction Patterns

### Default Construction

```cpp
// Empty tuple
auto empty = st::tuple_t<>();

// With default-constructible elements (default initialized)
auto defaults = st::ntuple_t<int, 3>();  // (0, 0, 0)
```

### Value Initialization

```cpp
// Heterogeneous
auto mixed = st::tuple_t(1, 2.5, "hello");

// Homogeneous
auto point = st::ntuple_t(1.0, 2.0, 3.0);

// Pair
auto pair = st::pair_t(42, "value");
```

### From References (tie)

```cpp
int x = 10, y = 20;
auto refs = st::tie(x, y);  // References to x and y

// Modifications through refs affect original variables
st::set<0>(refs, 100);
assert(x == 100);
```

### From C-Style Arrays

```cpp
double arr[3] = {1.0, 2.0, 3.0};
auto tuple = st::tie(arr);  // References to array elements
```

---

## Type Conversion & Casting

Converting between tuple types:

```cpp
// Via apply: ntuple_t to tuple_t with type change
auto ints = st::ntuple_t(1, 2, 3);
auto doubles = st::apply(ints, [](auto x) { return (double) x; });
// tuple_t<double, double, double>
```

---

## Element Access Patterns

### By Index

```cpp
auto tuple = st::tuple_t(1, 2.5, "hello");

auto first = st::get<0>(tuple);   // 1 (int)
auto second = st::get<1>(tuple);  // 2.5 (double)
auto third = st::get<2>(tuple);   // "hello" (const char*)
```

**Best for:** Position-based access, loops over indices, structured operations.

### By Type (Unique Types Only)

```cpp
auto config = st::tuple_t(42, "app", 3.14);

auto port = st::get<int>(config);        // 42 (if int is unique)
auto name = st::get<const char*>(config);  // "app"
auto version = st::get<double>(config);   // 3.14
```

**Best for:** Type-safe semantic access, self-documenting code.

**⚠ Important:** Type-based access only works if each type appears exactly once. Use index-based access if types repeat:

```cpp
// This won't compile - two ints!
auto tuple = st::tuple_t(1, 2.5, 3);
// auto x = st::get<int>(tuple);  // Ambiguous!

// Use indices instead
auto first_int = st::get<0>(tuple);   // 1
auto second_int = st::get<2>(tuple);  // 3
```

### Structured Bindings

```cpp
auto [x, y, z] = point;  // C++17 decomposition
```

---

## Memory Layout

### Tuple Memory Representation

SuperTuple tuples are typically zero-cost abstractions that compile to efficient structures:

```cpp
auto tuple = st::tuple_t(1, 2.5, "hello");
// Conceptually similar to:
// struct { int _0; double _1; const char* _2; };
```

**Characteristics:**
- No runtime overhead
- Layout depends on compiler/architecture alignment
- Similar memory footprint to hand-written structs
- Elements may have padding for alignment

### Homogeneous Tuple Layout

```cpp
auto point = st::ntuple_t(1.0, 2.0, 3.0);
// Conceptually: double[3] with functional operations
// Contiguous memory block
```

---

## Immutability & Mutability Semantics

### Creating New vs. Modifying

By default, SuperTuple operations create new tuples (functional style):

```cpp
auto original = st::tuple_t(1, 2, 3);

// Creates new tuple (non-mutating)
auto extended = st::append(original, 4);

// Original unchanged
assert(original == st::tuple_t(1, 2, 3));
assert(extended == st::tuple_t(1, 2, 3, 4));
```

### In-Place Modification

Use `set` for in-place mutations:

```cpp
auto mutable_data = st::tuple_t(1, 2, 3);
st::set<0>(mutable_data, 100);  // Modifies mutable_data directly
```

### Constness

Const tuples support const access:

```cpp
const auto immutable = st::tuple_t(1, 2, 3);
auto value = st::get<0>(immutable);  // Returns const reference
```

---

## Advanced: Template Metaprogramming

Access tuple properties at compile time:

```cpp
template <typename T>
void process_tuple(const T& tuple) {
    // Get count of elements
    constexpr size_t n = std::tuple_size_v<T>;  // Works with SuperTuple

    // Iterate with index_sequence
    process_elements(tuple, std::make_index_sequence<n>{});
}
```

SuperTuple tuples are compatible with standard library concepts for compile-time introspection.

---

## See Also

- [Operations Reference](operations/README.md) — Functional operations on tuples
- [API Reference](api.md) — Detailed type signatures
- [Usage Guide](usage.md) — Practical patterns
- [Examples](examples.md) — Real-world usage
