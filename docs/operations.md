# Operations Reference

All 21 SuperTuple operations are documented individually in the [operations folder](operations/README.md) with detailed signatures, behavior descriptions, practical examples, and use cases.

## Quick Navigation

**→ [Full Operations Index](operations/README.md)** — Organized by category with complete documentation

---

## Access Operations (3)

- **[get](operations/get.md)** — Retrieve element by index or type
- **[set](operations/set.md)** — Modify element by index or type
- **[tie](operations/tie.md)** — Create tuple of references

## List Operations (9)

- **[head](operations/head.md)** — First element
- **[tail](operations/tail.md)** — All but first element
- **[last](operations/last.md)** — Last element
- **[init](operations/init.md)** — All but last element
- **[append](operations/append.md)** — Add element at end
- **[prepend](operations/prepend.md)** — Add element at beginning
- **[concat](operations/concat.md)** — Combine two tuples
- **[reverse](operations/reverse.md)** — Reverse element order
- **[select](operations/select.md)** — Extract specific indices

## Folding Operations (2)

- **[fold](operations/fold.md)** — Reduce to single value (foldl/foldr)
- **[scan](operations/scan.md)** — Fold with intermediate steps (scanl/scanr)

## Transformation Operations (4)

- **[apply](operations/apply.md)** — Transform all elements
- **[zip](operations/zip.md)** — Pair elements from two tuples
- **[zipwith](operations/zipwith.md)** — Combine with custom function
- **[convert](operations/convert.md)** — Type conversions

## Iteration Operations (3)

- **[foreach](operations/foreach.md)** — Forward/reverse iteration
- **[forward](operations/forward.md)** — Unpack as function parameters

---

## Interoperability

For converting between SuperTuple and standard C++ tuples, see:

- **[Interoperability Guide](interop.md)** — `to_std` and `from_std` functions for integration with standard library and third-party code

---

## By Design

- **All operations are `constexpr`:** Compile-time computation when possible
- **Immutable by default:** Operations create new tuples, preserving originals
- **Zero-overhead abstractions:** Generated code matches hand-written equivalents with optimizations enabled
- **Composable:** Operations naturally chain for complex algorithms

---

## See Also

- **[Detailed Operations Index](operations/README.md)** — Each operation documented individually
- **[Tuple Types](tuples.md)** — Understanding tuple types
- **[Usage Guide](usage.md)** — Getting started
- **[Performance Guide](performance.md)** — Complexity and optimization
- **[FAQ](faq.md)** — Common questions
