# Concat

## Definition

Combine two tuples into a single tuple.

```cpp
template <id_t ...I, id_t ...J, typename ...T, typename ...U>
decltype(auto) concat(
    const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t,
    detail::tuple_t<detail::id_sequence_t<J...>, U...>&& u
);
```

## Category

List Operations

## Description

`concat` creates a new tuple by combining all elements from two input tuples. Elements from the first tuple appear before elements from the second. The result type is `tuple_t<T..., U...>`.

**Haskell equivalent:** `(++) :: [a] -> [a] -> [a]`

## Syntax

```cpp
auto combined = st::concat(first_tuple, second_tuple);
```

## Return Type

A new tuple of type `tuple_t<all_first_elements..., all_second_elements...>`.

## Behavior

- **Creates New:** Returns a new tuple without modifying inputs.
- **Order:** Elements from first tuple precede second tuple elements.
- **Variadic:** Works with tuples of any size and element types.
- **Move Support:** Second tuple can be moved to enable efficient element forwarding.
- **Compile-Time:** Fully `constexpr` evaluated.

## Use Cases

- Joining tuple sequences in pipelines
- Combining results from multiple computations
- Building larger tuples from smaller components
- Flattening nested tuple structures

## Example

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

auto first = st::tuple_t(1, 2);
auto second = st::tuple_t(3.0, "hello");

// Concatenate tuples
auto combined = st::concat(first, std::move(second));
// Result: (1, 2, 3.0, "hello")
static_assert(decltype(combined)::count == 4);

// Chain concats to join multiple tuples
auto t1 = st::tuple_t(1);
auto t2 = st::tuple_t(2);
auto t3 = st::tuple_t(3);
auto all = st::concat(t1, st::concat(t2, std::move(t3)));
```

## Related Operations

- [append](append.md) — Add single element to end
- [prepend](prepend.md) — Add single element to beginning
- [head](head.md), [tail](tail.md) — Decompose tuples

