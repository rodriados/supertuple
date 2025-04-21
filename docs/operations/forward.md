# Forward

## Definition

Forward all tuple elements as function parameters.

```cpp
template <typename F, id_t ...I, typename ...T>
decltype(auto) forward(
    const detail::tuple_t<detail::id_sequence_t<I...>, T...>& t,
    F&& lambda
);

template <typename F, id_t ...I, typename ...T>
decltype(auto) forward(
    detail::tuple_t<detail::id_sequence_t<I...>, T...>&& t,
    F&& lambda
);
```

## Category

Iteration Operations

## Description

`forward` unpacks all tuple elements and passes them as individual parameters to a function. This is useful for calling functions that expect multiple parameters when you have a tuple containing those parameters. Also called "tuple unpacking" or "variadic unpacking".

**Haskell equivalent:** `uncurry` or `uncurryN`

## Syntax

```cpp
auto result = st::forward(my_tuple, [](int a, double b, std::string c) {
    return process(a, b, c);
});
```

## Return Type

The return value of the function called with unpacked elements.

## Behavior

- **Unpacks All Elements:** All tuple elements become separate function parameters.
- **Type Safety:** Function parameter types must match tuple element types.
- **Move Support:** If tuple is rvalue, elements are forwarded as rvalues.
- **Functionality:** Enables calling fixed-parameter functions with tuple data.
- **Perfect Forwarding:** Preserves const/move semantics during unpacking.
- **Compile-Time:** Fully `constexpr` evaluated.

## Use Cases

- Calling functions with parameters stored in a tuple
- Unpacking results for multi-parameter operations
- Bridging tuple-based and parameter-based APIs
- Functional composition where intermediate results are tuples
- Variadic function wrapping

## Example

```cpp
#include <supertuple/api.h>
#include <iostream>

namespace st = supertuple;

// Function expecting multiple parameters
auto process = [](int a, double b, std::string c) {
    std::cout << "a=" << a << ", b=" << b << ", c=" << c << std::endl;
    return a + (int)b;
};

// Create tuple with parameters
auto params = st::tuple_t(42, 3.14, std::string("hello"));

// Forward elements as separate parameters
auto result = st::forward(params, process);
// Equivalent to: process(42, 3.14, "hello")

// Mathematical function
auto add3 = [](int x, int y, int z) { return x + y + z; };
auto numbers = st::tuple_t(10, 20, 30);
auto sum = st::forward(numbers, add3);  // Result: 60

// Combining with other operations
auto tuple = st::tuple_t(5, 10);
auto multiply = [](int a, int b) { return a * b; };
auto product = st::forward(tuple, multiply);  // Result: 50

// With move semantics
auto data = st::tuple_t(std::string("hello"), std::string("world"));
auto concat = [](std::string a, std::string b) { return a + " " + b; };
auto result = st::forward(std::move(data), concat);
// Result: "hello world"
```

## Related Operations

- [foreach](foreach.md) — Iterate for side effects
- [apply](apply.md) — Transform elements without unpacking
- [fold](fold.md) — Reduce with function application

