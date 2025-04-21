# Reverse

## Definition

Create a new tuple with elements in reverse order.

```cpp
template <id_t ...I, typename ...T>
decltype(auto) reverse(const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t);

template <id_t ...I, typename ...T>
decltype(auto) reverse(detail::tuple_t<detail::id_sequence_t<I...>, T...>&& t);
```

## Category

List Operations

## Description

`reverse` creates a new tuple with all elements in reverse order. The first element becomes last, and the last becomes first. This operation is useful for flipping tuple sequences without modifying the original.

**Haskell equivalent:** `reverse :: [a] -> [a]`

## Syntax

```cpp
auto flipped = st::reverse(my_tuple);
```

## Return Type

A new tuple with elements in reverse order. Types remain identical (no change to element types).

## Behavior

- **Creates New:** Returns a new tuple without modifying the input.
- **Order Reversal:** Element at index `i` moves to index `N-1-i`.
- **Type Preservation:** Element types remain the same, just reordered.
- **Index Inversion:** Uses `select` operation internally with reversed index sequence.
- **Compile-Time:** Fully `constexpr` evaluated.

## Use Cases

- Reversing sequences for rightward processing
- Symmetric operations requiring order reversal
- Mirroring tuple arrangements
- Building algorithms that work on both orderings

## Example

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

auto tuple = st::tuple_t(1, 2.0, "hello");

// Reverse the tuple
auto flipped = st::reverse(tuple);
// Result: ("hello", 2.0, 1)

// Access reversed elements
auto first = st::head(flipped);  // "hello"

// Double reverse returns to original order (type-wise, not value-wise for non-copyable)
auto restored = st::reverse(st::reverse(tuple));
```

## Related Operations

- [select](select.md) — Extract specific elements (using reversed indices)
- [head](head.md), [tail](tail.md) — Access ends of sequences
- [apply](apply.md) — Transform element values

