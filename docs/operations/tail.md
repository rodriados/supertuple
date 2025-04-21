# Tail

## Definition

Return a tuple with the first element removed.

```cpp
template <id_t ...I, typename ...T>
decltype(auto) tail(const detail::tuple_t<detail::id_sequence_t<0, I...>, T...>& t);

template <id_t ...I, typename ...T>
decltype(auto) tail(detail::tuple_t<detail::id_sequence_t<0, I...>, T...>&& t);
```

## Category

List Operations

## Description

`tail` returns a new tuple containing all elements of the input tuple except the first one. This operation is fundamental in functional programming for processing tuples recursively.

**Haskell equivalent:** `tail :: [a] -> [a]`

## Syntax

```cpp
auto rest = st::tail(my_tuple);
```

## Return Type

A new tuple containing elements 1 through N of the original tuple.

## Behavior

- **Creates New Tuple:** Returns a new tuple without modifying the original.
- **Elements:** Contains all elements from index 1 to the end.
- **Type Change:** Return tuple has one fewer element than input.
- **Move Support:** If called on an rvalue, elements are moved.
- **Compile-Time:** Fully `constexpr` evaluated.

## Use Cases

- Recursive tuple processing patterns (consume head, process tail)
- Removing the first element from a collection
- Building functional pipelines with sequential element removal
- Interleaving with `head` for tuple decomposition

## Example

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

auto tuple = st::tuple_t(1, 2.0, "hello");

// Remove first element
auto rest = st::tail(tuple);  // (2.0, "hello")
static_assert(decltype(rest)::count == 2);

// Nested tail operations
auto further = st::tail(rest);  // ("hello")

// Typical head + tail pattern
auto head_elem = st::head(tuple);  // 1
auto tail_elems = st::tail(tuple);  // (2.0, "hello")
```

## Related Operations

- [head](head.md) — Get first element
- [init](init.md) — Remove last element
- [select](select.md) — Extract specific elements

