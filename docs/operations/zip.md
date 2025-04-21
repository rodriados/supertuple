# Zip

## Definition

Combine two tuples element-wise into a tuple of pairs.

```cpp
template <id_t ...I, id_t ...J, typename ...T, typename ...U>
decltype(auto) zip(
    const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t,
    const detail::tuple_t<detail::id_sequence_t<J...>, U...>& u
);

template <id_t ...I, id_t ...J, typename ...T, typename ...U>
decltype(auto) zip(
    detail::tuple_t<detail::id_sequence_t<I...>, T...>&& t,
    detail::tuple_t<detail::id_sequence_t<J...>, U...>&& u
);
```

## Category

Transformation Operations

## Description

`zip` combines two tuples by pairing elements at the same index, creating a new tuple of `pair_t` objects. If tuples have different lengths, the result contains pairs only for indices present in both (length of shorter tuple).

**Haskell equivalent:** `zip :: [a] -> [b] -> [(a, b)]`

## Syntax

```cpp
auto zipped = st::zip(first_tuple, second_tuple);
```

## Return Type

A new tuple of `pair_t<T₀,U₀>, pair_t<T₁,U₁>, ...` with length equal to the shorter input tuple.

## Behavior

- **Creates New:** Returns a new tuple without modifying inputs.
- **Pairing:** Element at index i from first tuple pairs with element at index i from second.
- **Length:** Result size is `min(size_first, size_second)`.
- **Move Support:** Elements are moved if inputs are rvalues.
- **Pair Type:** Each element is `pair_t<T, U>` (specialized 2-element tuple).
- **Compile-Time:** Fully `constexpr` evaluated.

## Use Cases

- Aligning two sequences for parallel processing
- Creating coordinate pairs from separate dimensions
- Combining results from two computations
- Preparing data for zipwith operations
- Implementing coordinate/vector operations

## Example

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

auto first = st::tuple_t(1, 2, 3);
auto second = st::tuple_t(10, 20, 30);

// Zip two tuples
auto zipped = st::zip(first, second);
// Result: ((1,10), (2,20), (3,30))
static_assert(decltype(zipped)::count == 3);

// Access paired elements
auto first_pair = st::get<0>(zipped);  // pair_t(1, 10)
auto pair_first = st::get<0>(first_pair);   // 1
auto pair_second = st::get<1>(first_pair);  // 10

// Mismatched lengths: result uses shorter
auto longer = st::tuple_t(1, 2, 3, 4, 5);
auto shorter = st::tuple_t(10, 20);
auto trimmed = st::zip(longer, shorter);
// Result: ((1,10), (2,20)) - length 2

// Geometry use case: zip x,y,z coordinates
auto xs = st::tuple_t(1.0, 2.0, 3.0);
auto ys = st::tuple_t(4.0, 5.0, 6.0);
auto points = st::zip(xs, ys);  // ((1.0,4.0), (2.0,5.0), (3.0,6.0))
```

## Related Operations

- [zipwith](zipwith.md) — Zip with custom combination function
- [concat](concat.md) — Combine tuples sequentially
- [apply](apply.md) — Transform before/after zipping

