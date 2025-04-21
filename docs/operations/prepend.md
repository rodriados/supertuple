# Prepend

## Definition

Create a new tuple with an element added to the beginning.

```cpp
template <typename E, id_t ...I, typename ...T>
decltype(auto) prepend(const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t, E&& element);

template <typename E, id_t ...I, typename ...T>
decltype(auto) prepend(detail::tuple_t<detail::id_sequence_t<I...>, T...>&& t, E&& element);
```

## Category

List Operations

## Description

`prepend` creates a new tuple by adding an element to the beginning of an existing tuple, shifting all existing elements' indices up by one. The return type becomes `tuple_t<E, T...>`.

**Haskell equivalent:** `(:) :: a -> [a] -> [a]` or cons

## Syntax

```cpp
auto extended = st::prepend(my_tuple, new_element);
```

## Return Type

A new tuple of type `tuple_t<E, original_elements...>`.

## Behavior

- **Creates New:** Returns a new tuple without modifying the input.
- **Type Extension:** New element type becomes first; original elements follow.
- **Index Shift:** Original elements' indices increase by 1.
- **Perfect Forwarding:** Element is moved if rvalue, copied if lvalue.
- **Compile-Time:** Fully `constexpr` evaluated.

## Use Cases

- Building tuples from a head element and tail tuple
- Prepending to sequences in functional compositions
- Stack-like LIFO construction patterns
- Type-safe sequential tuple construction

## Example

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

// Start with a tuple
auto tuple = st::tuple_t(2.0, "hello");  // (double, const char*)

// Prepend an element
auto extended = st::prepend(tuple, 1);  // (int, double, const char*)
static_assert(decltype(extended)::count == 3);

// Build from scratch with chained prepends (builds right-to-left)
auto result = st::prepend(
    st::prepend(st::tuple_t("three"), 2),
    1
);  // (int, int, const char*)

// With move semantics
auto moved = st::prepend(st::tuple_t(std::string("tail")), std::string("head"));
```

## Related Operations

- [append](append.md) — Add element to end
- [concat](concat.md) — Combine two tuples
- [tail](tail.md) — Remove first element

