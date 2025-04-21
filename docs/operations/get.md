# Get

## Definition

Retrieve a tuple element by index or by unique type.

```cpp
template <id_t I, typename T>
decltype(auto) get(detail::node_t<I, T>& node) noexcept;

template <typename T, id_t I>
decltype(auto) get(detail::node_t<I, T>& node) noexcept;
```

## Category

Access Operations

## Description

`get` retrieves an element from a tuple by either its 0-based index or its type. If a tuple element has a unique type in that tuple, you can retrieve it by type; otherwise, you must use the index. The operation supports const-qualified and move references, enabling proper value forwarding.

**Haskell equivalent:** Element access / pattern matching on tuples

## Syntax

```cpp
// Get by index (0-based)
auto value = st::get<0>(my_tuple);

// Get by type (only works if type T is unique in tuple)
auto value = st::get<int>(my_tuple);
```

## Return Type

A reference to the element (const-qualified or move, depending on tuple reference type).

## Behavior

- **By Index:** Returns the element at position `I` (0-indexed).
- **By Type:** Returns the element of type `T` if exactly one element of that type exists in the tuple.
- **Const/Move Safety:** When called on a const tuple, returns const reference. When called on an rvalue tuple (`&&`), returns an rvalue reference, enabling move semantics.
- **Compile-Time:** All operations are `constexpr`, evaluated at compile time.

## Use Cases

- Extracting individual elements from a tuple for further processing
- Decomposing tuples into separate variables
- Type-safe access to tuple elements at compile time
- Building access patterns for functional operations

## Example

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

// Create a tuple with heterogeneous types
auto my_tuple = st::tuple_t(42, 3.14, std::string("hello"));

// Access by index
int first = st::get<0>(my_tuple);        // 42
double second = st::get<1>(my_tuple);    // 3.14

// Access by type (type must be unique)
int num = st::get<int>(my_tuple);        // 42
std::string str = st::get<std::string>(my_tuple);  // "hello"

// With move semantics
auto moved_tuple = st::tuple_t(1, 2, 3);
int value = st::get<0>(std::move(moved_tuple));  // Moves element
```

## Related Operations

- [set](set.md) — Modify an element in a tuple
- [head](head.md) — Get first element (equivalent to `get<0>`)
- [last](last.md) — Get last element

