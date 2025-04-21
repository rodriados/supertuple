# Tie

## Definition

Create a tuple of references from variables or array references.

```cpp
template <typename ...T>
decltype(auto) tie(T&... ref) noexcept;

template <typename T, size_t N>
decltype(auto) tie(T (&ref)[N]) noexcept;

template <typename T, size_t N>
decltype(auto) tie(T (&&ref)[N]) noexcept;
```

## Category

Access Operations

## Description

`tie` creates a tuple containing references to existing variables or array elements, without copying them. This operation is useful for creating lightweight tuple wrappers around existing data, or for structured binding scenarios where you want to gather multiple references.

**Haskell equivalent:** Conceptually similar to bundling multiple values without ownership

## Syntax

```cpp
// Tie individual variables
int a, b, c;
auto refs = st::tie(a, b, c);

// Tie array elements
int arr[3] = {1, 2, 3};
auto arr_refs = st::tie(arr);
```

## Return Type

A tuple of references (`tuple_t<T&...>` or `ntuple_t<T&, N>` for arrays).

## Behavior

- **Variable References:** Each argument becomes a reference in the tuple.
- **Array References:** Creates a homogeneous tuple of references to array elements.
- **Move Support:** For arrays passed as rvalue references, creates a tuple of rvalue references.
- **Zero-Copy:** No data is copied; only references are maintained.
- **Lifetime Dependency:** The created tuple's validity depends on the lifetime of the referenced objects.

## Use Cases

- Creating lightweight views into existing data structures
- Preparing data for structured bindings
- Gathering multiple variables for functional operations
- Building temporary reference tuples for algorithm composition

## Example

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

// Example 1: Tie individual variables
int x = 10, y = 20, z = 30;
auto refs = st::tie(x, y, z);

// Access references
ST::get<0>(refs) = 100;  // Modifies x
x = 100;  // Confirmed

// Example 2: Tie array
int arr[3] = {1, 2, 3};
auto arr_refs = st::tie(arr);

// Example 3: Use with structured bindings (C++17)
int a = 5, b = 15;
auto [ref_a, ref_b] = st::tie(a, b);
ref_a = 50;  // Modifies a
```

## Related Operations

- [get](get.md) — Retrieve elements from a tuple
- [foreach](foreach.md) — Iterate over tuple elements

