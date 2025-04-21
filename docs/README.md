# SuperTuple Documentation

Welcome to the SuperTuple documentation! This directory contains comprehensive documentation for the SuperTuple library.

## Documents

### Getting Started

- **[Installation](installation.md)** — Step-by-step setup instructions for your project
- **[Usage Guide](usage.md)** — Practical tutorial with basic concepts and common patterns
- **[Quick Examples](examples.md)** — Practical examples from basic to advanced usage

### References

- **[Tuple Types Guide](tuples.md)** — In-depth guide to `tuple_t`, `ntuple_t`, and `pair_t`
- **[API Reference](api.md)** — Detailed type signatures and interfaces
- **[Operations Reference](operations.md)** — Index of all 21 operations organized by category
- **[Detailed Operations](operations/)** — Individual pages for each operation with signatures, examples, and use cases
- **[Interoperability Guide](interop.md)** — Converting between SuperTuple and std::tuple, integration patterns

### Advanced & Performance

- **[Advanced Topics](advanced.md)** — Compile-time computing, CUDA support, template metaprogramming
- **[Performance Guide](performance.md)** — Optimization strategies, complexity analysis, benchmarking

### Development

- **[Contributing](../CONTRIBUTING.md)** — Guidelines for contributors, development setup, code standards

## Quick Start

New to SuperTuple? Follow this learning path:

1. **[Installation](installation.md)** — Get set up in 5 minutes
2. **[Usage Guide](usage.md)** — Learn core concepts and patterns
3. **[Tuple Types Guide](tuples.md)** — Understand the three tuple types
4. **[Quick Examples](examples.md)** — See real-world usage scenarios

**Ready for details?** — [API Reference](api.md)\
**Want to optimize?** — [Performance Guide](performance.md)\

## About SuperTuple

SuperTuple is a powerful yet lightweight C++17 tuple implementation designed for functional programming. It provides:

- **Memory-efficient tuples** equivalent to structs
- **Haskell-inspired API** with familiar functional operations
- **Zero runtime overhead** through `constexpr` evaluation
- **21 Built-in Operations**

**Access (3):** `get`, `set`, `tie`\
**List (9):** `head`, `tail`, `last`, `init`, `append`, `prepend`, `concat`, `reverse`, `select`\
**Folding (2):** `foldl`, `foldr`, `scanl`, `scanr`\
**Transform (4):** `apply`, `zip`, `zipwith`, `convert`\
**Iteration (3):** `foreach`, `rforeach`, `forward`

**Want to know more?** — [Operations Reference](operations/README.md).

## Example

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

int main() {
    // Create a tuple
    auto numbers = st::tuple_t(1, 2, 3, 4, 5);

    // Define operations
    auto add = [](auto x, auto y) { return x + y; };
    auto square = [](auto x) { return x * x; };

    // Functional operations
    auto sums = st::foldl(numbers, add, 0);             // 15
    auto squares = st::apply(numbers, square);          // (1, 4, 9, 16, 25)

    // Combine tuples
    auto total = st::zipwith(numbers, squared, add);    // (2, 6, 12, 20, 30)

    return 0;
}
```

## License

SuperTuple is licensed under the MIT License. See the main [LICENSE](../LICENSE) file for details.

## Support

- **Issues**: [GitHub Issues](https://github.com/rodriados/supertuple/issues)
- **Contributing**: See [Contributing](../CONTRIBUTING.md) for guidelines

---

For the latest information, visit the [SuperTuple GitHub repository](https://github.com/rodriados/supertuple).
