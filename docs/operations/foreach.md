# Foreach

## Definition

Iterate over tuple elements, applying a function for side effects.

```cpp
template <typename F, typename ...A, id_t ...I, typename ...T>
void foreach(
    detail::tuple_t<detail::id_sequence_t<I...>, T...>& t,
    F&& lambda, A&&... args
);

template <typename F, typename ...A, id_t ...I, typename ...T>
void foreach(
    const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t,
    F&& lambda, A&&... args
);

template <typename F, typename ...A, id_t ...I, typename ...T>
void rforeach(
    detail::tuple_t<detail::id_sequence_t<I...>, T...>& t,
    F&& lambda, A&&... args
);
```

## Category

Iteration Operations

## Description

`foreach` iterates over each element of a tuple, calling a function with side effects. Unlike `apply` which returns a new tuple, `foreach` is for functions called purely for their side effects (printing, logging, updates). The function returns void.

**Haskell equivalent:** `traverse_ :: (a -> IO ()) -> [a] -> IO ()`

## Syntax

```cpp
// Iterate with side effects
st::foreach(my_tuple, [](auto& elem) {
    elem.process();
});

// Reverse iteration
st::rforeach(my_tuple, [](auto elem) {
    std::cout << elem << ", ";
});

// With extra arguments
st::foreach(my_tuple, [](auto elem, int multiplier) {
    return elem * multiplier;
}, 2);
```

## Return Type

Void. Function is called for side effects only.

## Behavior

- **Forward Iteration:** `foreach` processes elements from first to last.
- **Reverse Iteration:** `rforeach` processes elements from last to first.
- **mutable Elements:** Non-const tuple references allow modifying elements in-place.
- **Extra Args:** Additional arguments passed to every function call.
- **Perfect Forwarding:** Elements forwarded according to input tuple const/move qualification.
- **Compile-Time:** Fully `constexpr` evaluated (for constexpr-compatible functions).

## Use Cases

- Applying side effects to each element (logging, printing, I/O)
- Modifying elements in place
- Triggering computations for each element
- Pattern: post-processing after folds or transformations
- Debugging/inspection of tuple contents

## Example

```cpp
#include <supertuple/api.h>
#include <iostream>

namespace st = supertuple;

// Simple iteration with side effects
auto data = st::tuple_t("hello", 42, 3.14);

// Print each element
st::foreach(data, [](auto elem) {
    std::cout << elem << " ";
});
// Output: hello 42 3.14

// Modify elements in place
auto mutable_data = st::tuple_t(1, 2, 3);
st::foreach(mutable_data, [](auto& elem) {
    elem *= 2;
});
// mutable_data is now (2, 4, 6)

// Reverse iteration
auto values = st::tuple_t(1, 2, 3);
st::rforeach(values, [](auto val) {
    std::cout << val << " ";
});
// Output: 3 2 1

// With extra arguments
st::foreach(
    st::tuple_t(1, 2, 3),
    [](auto val, int scale) {
        std::cout << (val * scale) << " ";
    },
    10
);
// Output: 10 20 30
```

## Related Operations

- [apply](apply.md) — Like foreach but for transformations (returns new tuple)
- [forward](forward.md) — Forward tuple elements as function parameters
- [fold](fold.md) — Complex aggregation with iteration

