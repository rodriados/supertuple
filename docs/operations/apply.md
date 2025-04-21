# Apply

## Definition

Apply a function to all elements of a tuple, creating a new tuple with transformed values.

```cpp
template <typename F, typename ...A, id_t ...I, typename ...T>
decltype(auto) apply(
    const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t,
    F&& lambda, A&&... args
);

template <typename F, typename ...A, id_t ...I, typename ...T>
decltype(auto) apply(
    detail::tuple_t<detail::id_sequence_t<I...>, T...>&& t,
    F&& lambda, A&&... args
);
```

## Category

Transformation Operations

## Description

`apply` transforms each element of a tuple by applying a function to it, creating a new tuple with the transformed values. This is the fundamental mapping operation for tuples (equivalent to `map` in functional programming).

**Haskell equivalent:** `map :: (a -> b) -> [a] -> [b]`

## Syntax

```cpp
// Simple transformation
auto doubled = st::apply(my_tuple, [](auto x) { return x * 2; });

// With extra arguments
auto shifted = st::apply(my_tuple, [](auto x, int off) { return x + off; }, 5);
```

## Return Type

A new tuple where each element is the result of applying the function to the corresponding input element.

## Behavior

- **Creates New:** Returns a new tuple without modifying the input.
- **Element-Wise:** Function is applied independently to each element.
- **Type Change:** Element types change to function return type (if homogeneous result).
- **Extra Args:** Additional arguments are passed to every function call.
- **Perfect Forwarding:** Uses perfect forwarding for elements and arguments.
- **Compile-Time:** Fully `constexpr` evaluated.

## Use Cases

- Transforming tuple elements (scaling, casting, formatting)
- Preparing elements for folding or other operations
- Type conversions across all elements
- Building processing pipelines (common pattern: apply → fold)
- Vector/point transformations in geometry

## Example

```cpp
#include <supertuple/api.h>
#include <cmath>

namespace st = supertuple;

// Simple transformation: multiply by 2
auto numbers = st::tuple_t(1, 2, 3);
auto doubled = st::apply(numbers, [](auto x) { return x * 2; });
// Result: (2, 4, 6)

// Transform with type change: convert to double
auto int_tuple = st::tuple_t(1, 2, 3);
auto as_double = st::apply(int_tuple, [](auto x) { return (double)x; });
// Result: (1.0, 2.0, 3.0)

// Extra arguments: add offset
auto offset_by_10 = st::apply(
    st::tuple_t(1, 2, 3),
    [](auto x, int off) { return x + off; },
    10
);  // Result: (11, 12, 13)

// Geometry example: square elements
auto point = st::tuple_t(1.0, 2.0, 3.0);
auto squared = st::apply(point, [](auto x) { return x * x; });
// Result: (1.0, 4.0, 9.0)

// Chaining with fold: sum of squares
auto sum_of_squares = st::foldl(
    st::apply(point, [](auto x) { return x * x; }),
    [](auto acc, auto sq) { return acc + sq; },
    0.0
);  // Result: 14.0
```

## Related Operations

- [fold/scan](fold.md) — Reduce transformed values
- [zipwith](zipwith.md) — Apply function to paired elements from two tuples
- [foreach](foreach.md) — Apply function for side effects only

