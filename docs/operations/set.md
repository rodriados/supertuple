# Set

## Definition

Assign a new value to a tuple element by index or by unique type.

```cpp
template <id_t I, typename T, typename V>
void set(detail::node_t<I, T>& node, V&& value);

template <typename T, id_t I, typename V>
void set(detail::node_t<I, T>& node, V&& value);
```

## Category

Access Operations

## Description

`set` modifies a tuple element in-place by assigning a new value. Like `get`, elements can be located by index or by type (if unique). The operation uses perfect forwarding to efficiently move or copy values depending on the situation.

**Haskell equivalent:** Immutable updates (conceptually, SuperTuple provides mutable reference semantics)

## Syntax

```cpp
// Set by index
st::set<0>(my_tuple, new_value);

// Set by type (only works if type T is unique)
st::set<int>(my_tuple, 42);
```

## Return Type

Void. Modifies the tuple element in-place.

## Behavior

- **By Index:** Modifies element at position `I` with the new value.
- **By Type:** Modifies the element of type `T` if exactly one exists.
- **Move/Copy:** Uses perfect forwarding; if `new_value` is an rvalue, it's moved; if lvalue, it's copied.
- **Mutates:** Directly modifies the tuple element (mutation, not functional).

## Use Cases

- Updating specific fields in a tuple structure
- Building mutable data structures with tuple foundations
- Replacing computational results in a tuple
- Modifying loop variables stored in tuples

## Example

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

// Create a mutable tuple
auto data = st::tuple_t(10, 20, 30);

// Modify by index
st::set<0>(data, 100);  // data is now (100, 20, 30)

// Modify by type (if type is unique)
st::set<int>(data, 42);  // Sets one of the ints to 42

// With move semantics
auto str_tuple = st::tuple_t(std::string("old"));
st::set<0>(str_tuple, std::string("new"));  // Moves new string in
```

## Related Operations

- [get](get.md) — Retrieve an element from a tuple
- [append](append.md) — Create new tuple with element added
- [prepend](prepend.md) — Create new tuple with element added at start

