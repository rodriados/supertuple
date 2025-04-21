# Scan

## Definition

Perform left-scan or right-scan reduction over a tuple, returning intermediate steps.

```cpp
template <typename F, typename B, id_t ...I, typename ...T>
decltype(auto) scanl(
    const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t,
    F&& lambda, B&& base
);

template <typename F, id_t ...I, typename ...T>
decltype(auto) scanl(
    const detail::tuple_t<detail::id_sequence_t<0, I...>, T...>& t,
    F&& lambda
);

// Similar signatures for scanr (right-scan)
```

## Category

Folding/Reduction Operations

## Description

`scanl` and `scanr` are like `foldl` and `foldr`, but instead of returning only the final result, they return a tuple containing all intermediate accumulator values. This is useful for seeing the progression of a reduction.

**Haskell equivalent:** `scanl :: (b -> a -> b) -> b -> [a] -> [b]` and `scanr`

## Syntax

```cpp
// Left-scan with base
auto result = st::scanl(my_tuple, [](auto acc, auto x) { return acc + x; }, 0);

// Left-scan without base
auto result = st::scanl(my_tuple, [](auto a, auto b) { return a + b; });

// Right-scan
auto result = st::scanr(my_tuple, [](auto a, auto b) { return a + b; });
```

## Return Type

A tuple containing all intermediate accumulator values, one more element than input (includes base).

## Behavior

- **With Base:** Returns tuple: `(base, f(base, x₀), f(f(base, x₀), x₁), ...)`.
- **Without Base:** Returns tuple: `(x₀, f(x₀, x₁), f(f(x₀, x₁), x₂), ...)`.
- **Length:** Result has N+1 elements (with base) or N elements (without base).
- **Intermediate Values:** All accumulator states are preserved in result tuple.
- **Compile-Time:** Fully `constexpr` evaluated.

## Use Cases

- Tracking cumulative sums or running totals
- Computing prefix sums (scanl) or suffix sums (scanr)
- Observing intermediate states of a computation
- Building sequences of partial results
- Cumulative statistics (running average, max, etc.)

## Example

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

// Running sum / prefix sum
auto input = st::tuple_t(1, 2, 3, 4);
auto running_sum = st::scanl(
    input,
    [](auto acc, auto x) { return acc + x; },
    0
);  // Result: (0, 1, 3, 6, 10)

// Without base: starts with first element
auto prefixes = st::scanl(
    st::tuple_t(1, 2, 3),
    [](auto acc, auto x) { return acc + x; }
);  // Result: (1, 3, 6)

// Multiplying elements with intermediate products
auto products = st::scanl(
    st::tuple_t(2, 3, 4),
    [](auto acc, auto x) { return acc * x; },
    1
);  // Result: (1, 2, 6, 24)

// Right-scan: suffix operations
auto suffixes = st::scanr(
    st::tuple_t(1, 2, 3),
    [](auto x, auto acc) { return x + acc; },
    0
);  // Shows sums from right to left
```

## Related Operations

- [fold](fold.md) — Compute only final result, not intermediate steps
- [apply](apply.md) — Transform elements before scanning
- Composition with fold for post-processing results

