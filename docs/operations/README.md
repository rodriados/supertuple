# Tuple Operations Reference

This folder contains detailed documentation for all 21 SuperTuple operations, organized by functional category. Each operation has its own comprehensive guide with signatures, usage examples, and related operations.

**Note:** For interoperability functions (`to_std`, `from_std`), see the [Interoperability Guide](../interop.md).

## Quick Navigation

- **[Access Operations](#access-operations)** — Retrieve and modify individual elements
- **[List Operations](#list-operations)** — Manipulate tuple structure and composition
- **[Folding/Reduction Operations](#foldingreduction-operations)** — Reduce tuples to single values
- **[Transformation Operations](#transformation-operations)** — Create new tuples by transforming elements
- **[Iteration Operations](#iteration-operations)** — Process tuple elements sequentially

---

## Access Operations

Operations for accessing and modifying individual tuple elements.

| Operation | File | Description |
|-----------|------|-------------|
| **get** | [get.md](get.md) | Retrieve element by index or unique type |
| **set** | [set.md](set.md) | Modify element in-place by index or type |
| **tie** | [tie.md](tie.md) | Create tuple of references from variables or arrays |

### Common Pattern

```cpp
// Access an element
auto value = st::get<0>(tuple);  // By index
auto value = st::get<int>(tuple);  // By type

// Modify an element
st::set<0>(tuple, new_value);

// Create reference tuple
int a, b, c;
auto refs = st::tie(a, b, c);
```

---

## List Operations

Operations for structural manipulation: combining, decomposing, and reordering tuples.

| Operation | File | Description |
|-----------|------|-------------|
| **head** | [head.md](head.md) | Get first element |
| **tail** | [tail.md](tail.md) | Get all elements except first |
| **last** | [last.md](last.md) | Get last element |
| **init** | [init.md](init.md) | Get all elements except last |
| **append** | [append.md](append.md) | Add element to end |
| **prepend** | [prepend.md](prepend.md) | Add element to beginning |
| **concat** | [concat.md](concat.md) | Combine two tuples |
| **reverse** | [reverse.md](reverse.md) | Reverse element order |
| **select** | [select.md](select.md) | Extract specific indices (filtering/reordering) |

### Common Patterns

```cpp
// Decomposition (head and tail)
auto first = st::head(tuple);
auto rest = st::tail(tuple);

// Building incrementally
auto extended = st::append(tuple, element);
auto prepended = st::prepend(tuple, element);
auto combined = st::concat(first_tuple, second_tuple);

// Reordering/filtering
auto reversed = st::reverse(tuple);
auto selected = st::select(tuple, std::index_sequence<2, 0, 1>{});
```

---

## Folding/Reduction Operations

Operations that combine all tuple elements into a single value using an accumulation function.

| Operation | File | Description |
|-----------|------|-------------|
| **fold** | [fold.md](fold.md) | Left-fold or right-fold reduction (foldl, foldr) |
| **scan** | [scan.md](scan.md) | Left-scan or right-scan (fold with intermediate steps) |

### Common Patterns

```cpp
// Sum elements with base value
auto sum = st::foldl(tuple, [](auto acc, auto x) { return acc + x; }, 0);

// Product without base (uses first element)
auto product = st::foldl(tuple, [](auto a, auto b) { return a * b; });

// Intermediate steps / running totals
auto running_sum = st::scanl(
    tuple,
    [](auto acc, auto x) { return acc + x; },
    0
);  // Returns tuple of intermediate values

// Right-fold (different order of operations)
auto right_result = st::foldr(tuple, [](auto a, auto b) { return a - b; });
```

---

## Transformation Operations

Operations that create new tuples by applying functions to elements.

| Operation | File | Description |
|-----------|------|-------------|
| **apply** | [apply.md](apply.md) | Apply function to all elements (mapping) |
| **zip** | [zip.md](zip.md) | Pair-wise combine two tuples into pairs |
| **zipwith** | [zipwith.md](zipwith.md) | Pair-wise combine two tuples with custom function |
| **convert** | [convert.md](convert.md) | Type conversion and casting operations |

### Common Patterns

```cpp
// Element-wise transformation
auto doubled = st::apply(tuple, [](auto x) { return x * 2; });
auto squared = st::apply(point, [](auto x) { return x * x; });

// Combining two tuples element-wise
auto zipped = st::zip(first, second);  // Creates pairs

// Custom combination function
auto sum = st::zipwith(
    a, b,
    [](auto x, auto y) { return x + y; }
);

// Chaining transformations (common pattern)
auto composed = st::foldl(
    st::zipwith(a, b, [](auto x, auto y) { return (y - x) * (y - x); }),
    [](auto acc, auto sq) { return acc + sq; },
    0.0
);  // Squared differences fold
```

---

## Iteration Operations

Operations for sequential element processing.

| Operation | File | Description |
|-----------|------|-------------|
| **foreach** | [foreach.md](foreach.md) | Iterate with side effects (includes rforeach for reverse) |
| **forward** | [forward.md](forward.md) | Unpack tuple elements as function parameters |

### Common Patterns

```cpp
// Forward iteration with side effects
st::foreach(tuple, [](auto elem) {
    std::cout << elem << " ";
});

// Reverse iteration
st::rforeach(tuple, [](auto elem) {
    process(elem);
});

// Unpack parameters for function call
auto result = st::forward(
    tuple,
    [](int a, double b, std::string c) { return process(a, b, c); }
);
```

---

## Composition Examples

Tuple operations compose naturally to build complex algorithms:

### Example 1: Vector Length (Euclidean Norm)

```cpp
auto point = st::ntuple_t<double, 3>(1, 2, 3);
auto length = std::sqrt(
    st::foldl(
        st::apply(point, [](auto x) { return x * x; }),
        [](auto acc, auto sq) { return acc + sq; },
        0.0
    )
);
```

**Steps:**
1. `apply` — Square each coordinate
2. `foldl` — Sum all squared values
3. `std::sqrt` — Take square root

### Example 2: Euclidean Distance

```cpp
auto p1 = st::ntuple_t<double, 3>(1, 2, 3);
auto p2 = st::ntuple_t<double, 3>(4, 5, 6);

auto distance = std::sqrt(
    st::foldl(
        st::zipwith(p1, p2, [](auto x, auto y) { return (y - x) * (y - x); }),
        [](auto acc, auto sq) { return acc + sq; },
        0.0
    )
);
```

**Steps:**
1. `zipwith` — Pair coordinates and compute squared differences
2. `foldl` — Sum all squared differences
3. `std::sqrt` — Take square root

### Example 3: Custom Aggregation

```cpp
auto values = st::tuple_t(1, 2, 3, 4, 5);

// Compute multiple statistics
auto sum = st::foldl(values, [](auto a, auto b) { return a + b; });
auto product = st::foldl(values, [](auto a, auto b) { return a * b; }, 1);
auto steps = st::scanl(values, [](auto a, auto b) { return a + b; }, 0);
```

---

## Organization & Design Principles

- **Immutability:** Most operations create new tuples rather than modifying originals (functional style)
- **Type Safety:** All operations are compile-time evaluated with full type checking
- **Constexpr:** All operations work in constant expressions for compile-time computation
- **Perfect Forwarding:** Elements are efficiently moved or copied based on context
- **Zero Overhead:** Implementations optimize away to minimal machine code
- **Composability:** Operations naturally chain to build complex algorithms

---

## Choosing the Right Operation

| Task | Operations |
|------|-----------|
| Get/set individual elements | `get`, `set` |
| Remove first/last | `tail`, `init` |
| Add element(s) | `append`, `prepend`, `concat` |
| Rearrange/filter | `select`, `reverse` |
| Transform elements | `apply`, `zipwith` |
| Aggregate to single value | `fold`, `foldl`, `foldr` |
| See intermediate steps | `scan`, `scanl`, `scanr` |
| Side effects on each element | `foreach`, `rforeach` |
| Call function with unpacked tuple | `forward` |

---

## See Also

- [Main API Reference](../api.md)
- [Usage Guide](../usage.md)
- [Examples](../examples.md)
- [Tuple Types Guide](../tuples.md)
- [Advanced Topics](../advanced.md)
