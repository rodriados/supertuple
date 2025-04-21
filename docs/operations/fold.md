# Fold

## Definition

Perform left-fold or right-fold reduction over a tuple.

```cpp
template <typename F, typename B, id_t ...I, typename ...T>
decltype(auto) foldl(
    const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t,
    F&& lambda, B&& base
);

template <typename F, id_t ...I, typename ...T>
decltype(auto) foldl(
    const detail::tuple_t<detail::id_sequence_t<0, I...>, T...>& t,
    F&& lambda
);

// Similar signatures for foldr (right-fold)
```

## Category

Folding/Reduction Operations

## Description

`foldl` and `foldr` reduce a tuple to a single value by repeatedly applying a function. **foldl** processes elements left-to-right (first to last), while **foldr** processes right-to-left (last to first). Both versions support optional base values.

**Haskell equivalent:** `foldl :: (b -> a -> b) -> b -> [a] -> b` and `foldr`

## Syntax

```cpp
// Left-fold with base value
auto result = st::foldl(my_tuple, [](auto acc, auto x) { return acc + x; }, 0);

// Left-fold without base (uses first element)
auto result = st::foldl(my_tuple, [](auto a, auto b) { return a + b; });

// Right-fold
auto result = st::foldr(my_tuple, [](auto a, auto b) { return std::pow(a, b); });
```

## Return Type

The type depends on the function return type and base value (if provided).

## Behavior

- **With Base:** Accumulator starts with base, applies function to each element sequentially.
- **Without Base:** Accumulator starts with first element, applies function from second element onward.
- **Left-Fold:** Processes `((...((base, x₀), x₁), ...), xₙ)`.
- **Right-Fold:** Processes `(x₀, (x₁, (..., (xₙ, base))))`.
- **Associativity:** Results differ between foldl and foldr for non-associative operations.
- **Compile-Time:** Fully `constexpr` evaluated.

## Use Cases

- Computing aggregate values (sums, products, min/max)
- String concatenation across elements
- Complex reductions requiring accumulation
- Building reduction-based algorithms
- Computing fixed-point calculations

## Example

```cpp
#include <supertuple/api.h>
#include <cmath>

namespace st = supertuple;

auto tuple = st::tuple_t(2, 3, 2);

// Left-fold: sum values
auto sum = st::foldl(
    st::tuple_t(1, 2, 3, 4),
    [](auto acc, auto x) { return acc + x; },
    0
);  // Result: 10

// Left-fold without base: multiply elements
auto product = st::foldl(
    st::tuple_t(2, 3, 4),
    [](auto a, auto b) { return a * b; }
);  // Result: 24

// Right-fold: compute powers
auto power = st::foldr(
    tuple,
    [](auto base, auto exp) { return std::pow(base, exp); }
);  // Result: 2^(3^2) = 512

// Geometry example: sum of squared elements
auto point = st::tuple_t(1.0, 2.0, 3.0);
auto sum_sq = st::foldl(
    st::apply(point, [](auto x) { return x * x; }),
    [](auto acc, auto sq) { return acc + sq; },
    0.0
);  // Result: 14.0
```

## Related Operations

- [scan](scan.md) — Like fold but returns intermediate results
- [apply](apply.md) — Transform elements before folding
- [accumulate pattern with apply/foldl](apply.md) — Common composition

