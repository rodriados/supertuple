# Append

## Definition

Create a new tuple with an element added to the end.

```cpp
template <typename E, id_t ...I, typename ...T>
decltype(auto) append(const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t, E&& element);

template <typename E, id_t ...I, typename ...T>
decltype(auto) append(detail::tuple_t<detail::id_sequence_t<I...>, T...>&& t, E&& element);
```

## Category

List Operations

## Description

`append` creates a new tuple by adding an element to the end of an existing tuple. The original tuple is unchanged, following functional programming immutability principles. The return type becomes `tuple_t<T..., E>`.

**Haskell equivalent:** `(++) :: [a] -> [a] -> [a]` or `snoc`

## Syntax

```cpp
auto extended = st::append(my_tuple, new_element);
```

## Return Type

A new tuple of type `tuple_t<original_elements..., E>`.

## Behavior

- **Creates New:** Returns a new tuple without modifying the input.
- **Type Extension:** Type contains all original elements plus the new element type.
- **Element Addition:** New element becomes the last element (index N).
- **Perfect Forwarding:** Element is moved if rvalue, copied if lvalue.
- **Compile-Time:** Fully `constexpr` evaluated.

## Use Cases

- Building tuples incrementally by adding elements
- Extending homogeneous or heterogeneous collections
- Accumulating results in functional pipelines
- Type-safe dynamic tuple construction at compile time

## Example

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

// Start with a tuple
auto tuple = st::tuple_t(1, 2.0);  // (int, double)

// Append an element
auto extended = st::append(tuple, "hello");  // (int, double, const char*)
static_assert(decltype(extended)::count == 3);

// Chain appends
auto result = st::append(
    st::append(st::tuple_t(1), 2),
    std::string("three")
);  // (int, int, std::string)

// With move semantics
auto moved = st::append(st::tuple_t(std::string("old")), std::string("new"));
```

## Related Operations

- [prepend](prepend.md) — Add element to beginning
- [concat](concat.md) — Combine two tuples
- [init](init.md) — Remove last element

