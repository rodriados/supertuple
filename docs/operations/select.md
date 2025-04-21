# Select

## Definition

Extract specific elements from a tuple by their indices.

```cpp
template <id_t ...K, id_t ...I, typename ...T>
decltype(auto) select(
    const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t,
    std::index_sequence<K...>
);

template <id_t ...K, id_t ...I, typename ...T>
decltype(auto) select(
    detail::tuple_t<detail::id_sequence_t<I...>, T...>&& t,
    std::index_sequence<K...>
);
```

## Category

List Operations

## Description

`select` creates a new tuple containing only the elements at specified indices from the input tuple. This operation supports arbitrary index permutations, filtering, and reordering.

**Haskell equivalent:** Applicative/list comprehension indexing

## Syntax

```cpp
// Select elements at indices 0, 2, 1 from input tuple
auto selected = st::select(my_tuple, std::index_sequence<0, 2, 1>{});
```

## Return Type

A new tuple containing only the selected elements in the specified index order.

## Behavior

- **Creates New:** Returns a new tuple without modifying the input.
- **Index Sequence:** Indices specify which elements to extract and in what order.
- **Reordering:** Indices don't need to be in order; duplicates are allowed.
- **Type Construction:** Result type matches the types at selected indices.
- **Move Support:** Elements are moved if input is rvalue.
- **Compile-Time:** Fully `constexpr` evaluated.

## Use Cases

- Extracting specific tuple elements
- Reordering tuple elements without the full tuple
- Filtering out unwanted elements by index
- Building new tuples from subsets in arbitrary order
- Implementing permutations and combinations

## Example

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

auto tuple = st::tuple_t(10, 20, 30, 40);  // indices 0,1,2,3

// Select specific elements
auto selected = st::select(tuple, std::index_sequence<0, 2>{});
// Result: (10, 30) - elements at indices 0 and 2

// Reorder elements
auto reordered = st::select(tuple, std::index_sequence<3, 1, 0>{});
// Result: (40, 20, 10)

// Select with duplicates
auto dups = st::select(tuple, std::index_sequence<1, 1, 1>{});
// Result: (20, 20, 20)
```

## Related Operations

- [reverse](reverse.md) — Reverse all elements (uses select with reversed indices)
- [head](head.md), [tail](tail.md) — Select front/back subsets
- [get](get.md) — Get single element by index

