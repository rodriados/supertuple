# Interoperability Guide

SuperTuple integrates seamlessly with standard C++ utilities and third-party libraries. This guide covers converting between SuperTuple and standard C++ tuples, and integration patterns.

## Table of Contents

1. [Converting to std::tuple](#converting-to-stdtuple)
2. [Converting from std::tuple](#converting-from-stdtuple)
3. [Integration Patterns](#integration-patterns)
4. [Common Scenarios](#common-scenarios)
5. [Performance Considerations](#performance-considerations)

---

## Converting to std::tuple

### `to_std` Function

Convert a SuperTuple `tuple_t` to a standard C++ `std::tuple`:

```cpp
template <typename ...T>
constexpr decltype(auto) to_std(const tuple_t<T...>& t);

template <typename ...T>
constexpr decltype(auto) to_std(tuple_t<T...>&& t);
```

**When to use:**
- Passing SuperTuples to standard library functions
- Interfacing with APIs expecting `std::tuple`
- Using `std::apply`, `std::get`, etc.
- Interoperating with third-party libraries

### Basic Example

```cpp
#include <supertuple/api.h>
#include <iostream>

namespace st = supertuple;

int main() {
    // Create a SuperTuple
    auto super = st::tuple_t(42, 3.14, std::string("hello"));

    // Convert to std::tuple
    auto standard = st::to_std(super);

    // Use standard library functions
    std::cout << std::get<0>(standard) << "\n";  // 42
    std::cout << std::get<1>(standard) << "\n";  // 3.14
    std::cout << std::get<2>(standard) << "\n";  // hello
}
```

### Using with std::apply

```cpp
auto super = st::tuple_t(1, 2, 3, 4);
auto standard = st::to_std(super);

// Unpack tuple elements as function arguments
auto sum = std::apply([](auto... args) {
    return (args + ... + 0);
}, standard);  // 10
```

### Move Semantics

```cpp
// Efficient transfer of ownership
auto temp_std = st::to_std(st::tuple_t(1, 2, 3));
// Elements are moved if applicable, not copied
```

---

## Converting from std::tuple

### `from_std` Function

Convert a standard C++ `std::tuple` to a SuperTuple:

```cpp
template <typename ...T>
constexpr decltype(auto) from_std(const std::tuple<T...>& t);

template <typename ...T>
constexpr decltype(auto) from_std(std::tuple<T...>&& t);
```

**When to use:**
- Converting results from standard library functions
- Importing tuples from third-party libraries
- Applying SuperTuple operations to existing `std::tuple` data
- Gradual migration from `std::tuple` to SuperTuple

### Basic Example

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

// Function returning standard tuple (e.g., from external library)
std::tuple<int, double, std::string> fetch_data() {
    return {42, 3.14, "data"};
}

int main() {
    // Get std::tuple from external source
    auto std_tuple_instance = fetch_data();

    // Convert to SuperTuple
    auto super = st::from_std(std_tuple_instance);

    // Now apply SuperTuple operations
    auto transformed = st::apply(super, [](auto x) {
        // Process elements
        return x;
    });
}
```

### Applying Operations

```cpp
// Convert and use functional operations
auto std_values = std::tuple(1.0, 2.0, 3.0);
auto super = st::from_std(std_values);

auto add = [](auto x, auto y) { return x + y; };

// Sum using fold
auto sum = st::foldl(super, add, 0.0);  // 6.0

// Transform
auto doubled = st::apply(super, [](auto x) { return x * 2; });
// (2.0, 4.0, 6.0)
```

### Move Semantics

```cpp
// Convert temporary elegantly
auto super = st::from_std(std::tuple(1, 2, 3, 4));
// Elements are moved if applicable
```

---

## Integration Patterns

### Pattern 1: Round-Trip Conversion

Convert between formats for different APIs:

```cpp
// Start with SuperTuple operations
auto result = st::apply(input, [](auto x) { return x * 2; });

// Convert to std::tuple for external library
auto std_result = st::to_std(result);
external_api_function(std_result);

// Convert result back if needed
auto final = st::from_std(std_result);
```

### Pattern 2: Mixed Operations

Combine SuperTuple and standard library operations:

```cpp
auto super = st::tuple_t(1, 2, 3, 4, 5);
auto add = [](auto x, auto y) { return x + y; };

// SuperTuple fold
auto sum = st::foldl(super, add, 0);

// Standard library on converted tuple
auto std_tuple = st::to_std(st::apply(super, [](auto x) { return x * 2; }));
auto product = std::apply([](auto... args) {
    return (args * ... * 1);
}, std_tuple);
```

### Pattern 3: Gradual Migration

Migrate code incrementally from `std::tuple` to SuperTuple:

```cpp
// Legacy code using std::tuple
std::tuple<int, double> legacy_data = get_legacy_data();

// Convert for new SuperTuple-based functionality
auto modern = st::from_std(legacy_data);

// Apply new operations
auto processed = st::apply(modern, transform_function);

// Convert back for legacy code if needed
auto legacy_result = st::to_std(processed);
```

### Pattern 4: Composition

Combine multiple tuples with type preservation:

```cpp
auto a = st::tuple_t(1, 2);
auto b = std::tuple(3.0, 4.0);

// Convert and combine
auto combined = st::concat(a, st::from_std(b));
// type: tuple_t<int, int, double, double>

// Process combined result
auto result = st::apply(combined, [](auto x) { return (double) x; });
```

---

## Performance Considerations

### Zero-Cost Conversions

Both `to_std` and `from_std` are marked `constexpr` and compile to equivalent code:

```cpp
// These two are equivalent at runtime (after optimization)
auto a = st::to_std(st::tuple_t(1, 2, 3));
auto b = std::tuple(1, 2, 3);  // Compiles to identical machine code
```

### When Conversion is Free

- **Conversions compile away** when optimizations are enabled
- **No dynamic allocations** — both tuple types are fixed-size, stack-allocated
- **Perfect forwarding** ensures move semantics work efficiently
- **No temporary copies** with modern compiler optimizations

### Best Practices

1. **Use `const` references** when passing to functions that don't modify:
   ```cpp
   auto std_tuple = st::to_std(super);  // Converted tuple
   func(std_tuple);  // Passed by value (small, optimized)
   ```

2. **Use rvalue references** for temporary conversions:
   ```cpp
   process(st::to_std(st::apply(data, transform)));  // Efficient
   ```

3. **Avoid unnecessary conversions** in tight loops:
   ```cpp
   // Do this once
   auto std_data = st::to_std(data);

   // Use many times
   for (int i = 0; i < 1000; ++i) {
       use(std_data);
   }
   ```

---

## Type Preservation

Conversions preserve element types exactly:

```cpp
auto super = st::tuple_t(44LL, 3.14f, std::string("text"));
auto std_tuple = st::to_std(super);

// Types are preserved:
// std_tuple type: std::tuple<long long, float, std::string>
std::cout << typeid(std::get<0>(std_tuple)).name() << "\n";  // long long
std::cout << typeid(std::get<1>(std_tuple)).name() << "\n";  // float
std::cout << typeid(std::get<2>(std_tuple)).name() << "\n";  // std::string
```

---

## See Also

- **[Tuple Types Guide](tuples.md)** — Understanding tuple type selection
- **[API Reference](api.md)** — Complete API documentation
- **[Usage Guide](usage.md)** — Getting started with SuperTuple
