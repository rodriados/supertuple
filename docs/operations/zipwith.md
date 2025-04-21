# Zipwith

## Definition

Combine two tuples element-wise using a custom function.

```cpp
template <typename F, id_t ...I, id_t ...J, typename ...T, typename ...U>
decltype(auto) zipwith(
    const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t,
    const detail::tuple_t<detail::id_sequence_t<J...>, U...>& u,
    F&& lambda
);

template <typename F, id_t ...I, id_t ...J, typename ...T, typename ...U>
decltype(auto) zipwith(
    detail::tuple_t<detail::id_sequence_t<I...>, T...>&& t,
    detail::tuple_t<detail::id_sequence_t<J...>, U...>&& u,
    F&& lambda
);
```

## Category

Transformation Operations

## Description

`zipwith` combines two tuples by applying a function to paired elements at the same indices. Unlike `zip` which creates pairs, `zipwith` lets you specify how to combine elements. This is the generalized form of zip.

**Haskell equivalent:** `zipWith :: (a -> b -> c) -> [a] -> [b] -> [c]`

## Syntax

```cpp
auto combined = st::zipwith(first, second, [](auto a, auto b) { return a + b; });
```

## Return Type

A new tuple where each element is the result of the function applied to paired elements from the input tuples.

## Behavior

- **Creates New:** Returns a new tuple without modifying inputs.
- **Element-Wise Function:** Function receives paired elements from same index.
- **Length:** Result size is `min(size_first, size_second)`.
- **Move Support:** Elements are moved if inputs are rvalues.
- **Type Inference:** Result element type inferred from function return type.
- **Compile-Time:** Fully `constexpr` evaluated.

## Use Cases

- Element-wise arithmetic (addition, subtraction, multiplication)
- Coordinate-wise operations (dot products, cross products)
- Combining results with custom logic
- Distance/similarity calculations
- Building reduction-ready combinations

## Example

```cpp
#include <supertuple/api.h>
#include <cmath>

namespace st = supertuple;

auto first = st::tuple_t(1, 2, 3);
auto second = st::tuple_t(10, 20, 30);

// Element-wise addition
auto sum = st::zipwith(first, second, [](auto a, auto b) { return a + b; });
// Result: (11, 22, 33)

// Element-wise multiplication
auto product = st::zipwith(
    first, second,
    [](auto a, auto b) { return a * b; }
);  // Result: (10, 40, 90)

// Geometry: difference calculation
auto p1 = st::tuple_t(1.0, 2.0, 3.0);
auto p2 = st::tuple_t(4.0, 5.0, 6.0);
auto diff = st::zipwith(p1, p2, [](auto x, auto y) { return y - x; });
// Result: (3.0, 3.0, 3.0)

// Distance calculation pattern: squared differences
auto squared_diffs = st::zipwith(
    p1, p2,
    [](auto x, auto y) { return (y - x) * (y - x); }
);  // Result: (9.0, 9.0, 9.0)

// Sum of squared differences (combine with fold)
auto sum_of_sq_diffs = st::foldl(
    squared_diffs,
    [](auto acc, auto sq) { return acc + sq; },
    0.0
);  // Result: 27.0
```

## Related Operations

- [zip](zip.md) — Create pairs without custom function
- [apply](apply.md) — Transform single tuple
- [fold](fold.md) — Reduce results
- Composition: `foldl(zipwith(...), ...)` for reductions

