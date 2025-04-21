# Last

## Definition

Retrieve the last element of a tuple.

```cpp
template <id_t ...I, typename ...T>
decltype(auto) last(const detail::tuple_t<detail::id_sequence_t<0, I...>, T...>& t) noexcept;

template <id_t ...I, typename ...T>
decltype(auto) last(detail::tuple_t<detail::id_sequence_t<0, I...>, T...>&& t) noexcept;
```

## Category

List Operations

## Description

`last` returns the last element of a tuple. This is a convenience operation complementary to `head`, useful in patterns where you need the final element of a tuple.

**Haskell equivalent:** `last :: [a] -> a`

## Syntax

```cpp
auto final = st::last(my_tuple);
```

## Return Type

A reference to the last element (const-qualified or move, depending on input).

## Behavior

- **Returns:** Final element of the tuple (index N-1).
- **Move Support:** If called on an rvalue tuple, returns an rvalue reference.
- **Compile-Time:** Fully `constexpr` evaluated.
- **Requires:** Non-empty tuple.

## Use Cases

- Accessing the last element in functional fold operations
- Final element retrieval in tuple processing
- Complement to `last` for symmetric first/last patterns
- Used internally by `scan` operations

## Example

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

auto tuple = st::tuple_t(10, 20, 30, 40);

// Get last element
auto final = st::last(tuple);  // 40
static_assert(std::is_same_v<decltype(final), int>);

// With init operation
auto all_but_last = st::init(tuple);  // (10, 20, 30)
auto last_elem = st::last(tuple);      // 40
```

## Related Operations

- [init](init.md) — Get all elements except last
- [head](head.md) — Get first element
- [get](get.md) — Get element by index or type

