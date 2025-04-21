# Head

## Definition

Retrieve the first element of a tuple.

```cpp
template <id_t ...I, typename ...T>
decltype(auto) head(const detail::tuple_t<detail::id_sequence_t<0, I...>, T...>& t) noexcept;

template <id_t ...I, typename ...T>
decltype(auto) head(detail::tuple_t<detail::id_sequence_t<0, I...>, T...>&& t) noexcept;
```

## Category

List Operations

## Description

`head` returns the first element of a tuple. It's equivalent to `get<0>(t)`. This operation is commonly used in functional programming patterns where you process tuples element by element.

**Haskell equivalent:** `head :: [a] -> a`

## Syntax

```cpp
auto first = st::head(my_tuple);
```

## Return Type

A reference to the first element (const-qualified or move, depending on input).

## Behavior

- **Returns:** First element of the tuple (index 0).
- **Move Support:** If called on an rvalue tuple, returns an rvalue reference.
- **Compile-Time:** Fully `constexpr` evaluated.
- **Requires:** Non-empty tuple.

## Use Cases

- Processing tuple elements sequentially in functional compositions
- Extracting the first element in patterns like `(head, tail)` decomposition
- First-element access patterns in recursive algorithms
- Convenient alias for `get<0>`

## Example

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

auto tuple = st::tuple_t(42, 3.14, "hello");

// Get first element
auto first = st::head(tuple);  // 42
static_assert(std::is_same_v<decltype(first), int>);

// Using with tail for decomposition
auto tail = st::tail(tuple);  // (3.14, "hello")
```

## Related Operations

- [tail](tail.md) — Get all elements except first
- [last](last.md) — Get last element
- [get](get.md) — Get element by index or type

