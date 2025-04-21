# Init

## Definition

Return a tuple with the last element removed.

```cpp
template <id_t ...I, typename ...T>
decltype(auto) init(const detail::tuple_t<detail::id_sequence_t<0, I...>, T...>& t);

template <id_t ...I, typename ...T>
decltype(auto) init(detail::tuple_t<detail::id_sequence_t<0, I...>, T...>&& t);
```

## Category

List Operations

## Description

`init` returns a new tuple containing all elements except the last one. This operation is the complement to `tail` for end-relative processing.

**Haskell equivalent:** `init :: [a] -> [a]`

## Syntax

```cpp
auto all_but_last = st::init(my_tuple);
```

## Return Type

A new tuple containing elements 0 through N-2 of the original tuple.

## Behavior

- **Creates New Tuple:** Returns a new tuple without modifying the original.
- **Elements:** Contains all elements from index 0 to N-2.
- **Type Change:** Return tuple has one fewer element than input.
- **Move Support:** If called on an rvalue, elements are moved.
- **Compile-Time:** Fully `constexpr` evaluated.

## Use Cases

- Removing the last element to process a shortened collection
- Symmetric patterns with `tail` (remove from front vs back)
- Truncating sequences for specific calculations
- Preparation for fold or scan operations

## Example

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

auto tuple = st::tuple_t(1, 2, 3, 4);

// Remove last element
auto shortened = st::init(tuple);  // (1, 2, 3)
static_assert(decltype(shortened)::count == 3);

// Nested init operations
auto further = st::init(shortened);  // (1, 2)

// Last + init pattern
auto last_elem = st::last(tuple);      // 4
auto prefix = st::init(tuple);         // (1, 2, 3)
```

## Related Operations

- [tail](tail.md) — Remove first element
- [last](last.md) — Get last element
- [append](append.md) — Add element to end

