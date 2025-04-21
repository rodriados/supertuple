# Convert

## Definition

Convert tuple elements to different types or formats.

```cpp
template <typename To>
class converter_t {
    // Creates conversion utility for deferred conversion operations
};

// Usage typically through converter_t API for type transformations
```

## Category

Transformation Operations

## Description

`convert` provides mechanisms for casting and converting tuple element types. It enables creating new tuples with elements converted to target types, with compile-time type checking and safety.

**Haskell equivalent:** Conceptually similar to functor/applicative mappings with type changes

## Syntax

```cpp
// Typical usage (implementation details vary per use case)
// Apply conversions using composition with apply or explicit conversions
```

## Return Type

A new tuple with elements of converted types.

## Behavior

- **Type Safety:** Conversions checked at compile time.
- **Immutable:** Creates new tuples, doesn't modify originals.
- **Flexible:** Supports various conversion mechanisms.
- **Efficient:** Zero-overhead abstractions; conversions compile away.

## Use Cases

- Converting integer tuples to floating-point
- Type promotion or demotion
- String/numeric conversions
- Interfacing between different type systems
- Casting for algorithmic requirements

## Example

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

// Conversions are typically done via apply with lambda conversions
auto ints = st::tuple_t(1, 2, 3);

// Convert to double using apply
auto as_doubles = st::apply(ints, [](auto x) { return (double)x; });
// Result: (1.0, 2.0, 3.0)

// Convert to string
auto as_strings = st::apply(ints, [](auto x) {
    return std::to_string(x);
});
// Result: ("1", "2", "3")

// Mixed type tuple conversions
auto mixed = st::tuple_t(1, 2.5, 3);
auto uniform = st::apply(mixed, [](auto x) {
    return (double)x;
});
// Result: (1.0, 2.5, 3.0)
```

## Related Operations

- [apply](apply.md) — General element transformation (includes conversions)
- [zipwith](zipwith.md) — Combine with type conversion
- Type system integration with `cast.hpp`

