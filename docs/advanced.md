# Advanced Topics

Deep dives into specialized techniques and advanced usage patterns for SuperTuple.

## Table of Contents

1. [Compile-Time Computing](#compile-time-computing)
2. [Type-Safe Guarantees](#type-safe-guarantees)
3. [CUDA Support](#cuda-support)
4. [Custom Functors](#custom-functors)
5. [Composition Patterns](#composition-patterns)
6. [Template Metaprogramming](#template-metaprogramming)

---

## Compile-Time Computing

All SuperTuple operations are marked `constexpr`, enabling computation at compile time.

### Static Computation Example

```cpp
#include <supertuple/api.h>

constexpr auto compute() {
    namespace st = supertuple;

    // All operations happen at compile time
    auto numbers = st::tuple_t(1, 2, 3, 4, 5);

    auto sum = st::foldl(
        numbers,
        [](auto acc, auto x) { return acc + x; },
        0
    );

    return sum;  // Computed at compile time
}

static_assert(compute() == 15);  // Verified at compile time
```

### Advantages

- **Zero Runtime Cost:** Computations evaluated during compilation
- **Verification:** Compile-time assertions verify algorithm correctness
- **Optimization:** Compiler sees full computation, applies aggressive optimizations
- **Reproducibility:** Results are deterministic, independent of runtime environment

### Constexpr Limitations

Not all C++ features are constexpr-compatible:

```cpp
// These work in constexpr context:
std::min, std::max, std::abs, arithmetic operations

// These DON'T work in constexpr context:
std::sqrt, std::pow, std::sin (most <cmath> functions)
std::cout, I/O operations, platform-specific code

// Workaround: Use if constexpr or conditional compilation
constexpr auto safe_sqrt(double x) {
    if constexpr (is_constant_evaluated()) {
        // Constexpr version
        return x;  // Or Newton's method implementation
    } else {
        // Runtime version
        return std::sqrt(x);
    }
}
```

---

## Type-Safe Guarantees

### Compile-Time Index Checking

```cpp
auto tuple = st::tuple_t(1, 2, 3);

// Valid indices
auto elem0 = st::get<0>(tuple);  // ✓ Compiles

// Invalid indices cause compile-time error
// auto elem5 = st::get<5>(tuple);  // ✗ Compile error

// More readable with index_sequence
auto selected = st::select(tuple, std::index_sequence<0, 2>{});  // ✓ OK
```

### Type Uniqueness

SuperTuple enforces unique type access:

```cpp
auto tuple = st::tuple_t(1, 2.5, "hello");

auto num = st::get<int>(tuple);        // ✓ Unique type
auto flt = st::get<double>(tuple);     // ✓ Unique type
auto str = st::get<const char*>(tuple); // ✓ Unique type

// Non-unique types require index access:
auto multi = st::tuple_t(1, 2, 3.0);

// auto x = st::get<int>(multi);  // ✗ Ambiguous!
auto x = st::get<0>(multi);        // ✓ Use index instead
auto y = st::get<1>(multi);
```

### Move Semantics & Perfect Forwarding

All operations use perfect forwarding for optimal efficiency:

```cpp
auto expensive = st::tuple_t(std::string("large"), std::vector<int>{1,2,3});

// Moves are efficient
auto moved = st::append(std::move(expensive), 42);

// Copies only when necessary
auto original = st::tuple_t(std::string("data"));
auto copied = st::append(original, 42);  // Copies into new tuple
```

---

## CUDA Support

SuperTuple works in CUDA device code through `CUDA_CONSTEXPR` macros.

### Basic CUDA Usage

```cpp
#include <supertuple/api.h>

namespace st = supertuple;

// Device-side computation
__global__ void kernel(double* result) {
    if (threadIdx.x == 0) {
        // Tuple operations work in device code
        auto point = st::ntuple_t<double, 3>(1.0, 2.0, 3.0);

        auto squared = st::apply(point, [](auto x) { return x * x; });

        auto sum_sq = st::foldl(
            squared,
            [](auto acc, auto x) { return acc + x; },
            0.0
        );

        result[0] = sum_sq;  // 14.0
    }
}
```

### Considerations

- **Memory:** Tuples are value types; stack allocation in kernel functions
- **Shared Memory:** Can be used in shared memory for inter-thread communication
- **Global Memory:** Can store tuples in global memory with appropriate indirection
- **Vectorization:** NVIDIA compilers optimize tuple access similar to arrays

### Example: Parallel Dot Product

```cpp
__global__ void dot_product(
    const double* x, const double* y,
    int size, double* result
) {
    namespace st = supertuple;

    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < size) {
        // Each thread loads its pair of values
        auto pair = st::pair_t(x[tid], y[tid]);

        // Compute product
        double product = st::forward(
            pair,
            [](double a, double b) { return a * b; }
        );

        result[tid] = product;
    }
}
```

---

## Custom Functors

Guidelines for writing functors to use with tuple operations.

### Functor Signature for apply

```cpp
// For apply: takes one element, returns transformed element
struct DoubleIt {
    constexpr int operator()(int x) const {
        return x * 2;
    }
};

auto doubled = st::apply(tuple, DoubleIt{});

// With lambda (simpler)
auto doubled = st::apply(tuple, [](auto x) { return x * 2; });

// With extra arguments
auto scaled = st::apply(
    tuple,
    [](auto x, double factor) { return x * factor; },
    2.5
);
```

### Functor Signature for fold/foldr

```cpp
// For fold: takes accumulator and element, returns new accumulator
struct Sum {
    constexpr auto operator()(auto acc, auto x) const {
        return acc + x;
    }
};

auto total = st::foldl(tuple, Sum{}, 0);

// With lambda
auto product = st::foldl(
    tuple,
    [](auto acc, auto x) { return acc * x; },
    1
);
```

### Functor Signature for zipwith

```cpp
// For zipwith: takes two paired elements, returns combined
struct Add {
    constexpr auto operator()(auto a, auto b) const {
        return a + b;
    }
};

auto sums = st::zipwith(a, b, Add{});

// With lambda
auto combined = st::zipwith(
    a, b,
    [](auto x, auto y) { return x + y; }
);
```

### Generic Functors (Template Operator)

```cpp
// Works with any types that support the operation
struct GenericOperation {
    template <typename A, typename B>
    constexpr auto operator()(A a, B b) const {
        return a + b;  // Works for int, double, string, etc.
    }
};

auto result = st::foldl(tuple, GenericOperation{}, 0);
```

### Const Correctness

Functors should be const for use in constexpr contexts:

```cpp
// ✓ Const operator - works with constexpr
struct ConstFunctor {
    constexpr int operator()(int x) const { return x * 2; }
};

constexpr auto doubled = st::apply(tuple, ConstFunctor{});

// ✗ Non-const operator - won't work with constexpr
struct NonConstFunctor {
    int operator()(int x) { return x * 2; }  // Not const!
};

// constexpr auto doubled = st::apply(tuple, NonConstFunctor{});  // Error
```

---

## Composition Patterns

### Sequential Composition

Combine multiple operations to build complex algorithms:

```cpp
auto data = st::tuple_t(1, 2, 3, 4, 5);

// Pattern: transform → reduce
auto sum_of_squares = st::foldl(
    st::apply(data, [](auto x) { return x * x; }),
    [](auto acc, auto x) { return acc + x; },
    0
);  // (1 + 4 + 9 + 16 + 25) = 55

// Pattern: zip → transform → fold
auto a = st::tuple_t(1, 2, 3);
auto b = st::tuple_t(4, 5, 6);

auto dot_product = st::foldl(
    st::zipwith(
        a, b,
        [](auto x, auto y) { return x * y; }
    ),
    [](auto acc, auto prod) { return acc + prod; },
    0
);  // (1*4 + 2*5 + 3*6) = 32

// Pattern: scan → select → fold
auto cumsum = st::scanl(data, [](auto acc, auto x) { return acc + x; }, 0);
auto last_three = st::select(cumsum, std::index_sequence<2, 3, 4>{});
```

### Geometry Example

```cpp
// Compute vector magnitude
template <size_t D>
constexpr double magnitude(const st::ntuple_t<double, D>& v) {
    return std::sqrt(
        st::foldl(
            st::apply(v, [](auto x) { return x * x; }),
            [](auto acc, auto x) { return acc + x; },
            0.0
        )
    );
}

// Compute distance between points
template <size_t D>
constexpr double distance(
    const st::ntuple_t<double, D>& a,
    const st::ntuple_t<double, D>& b
) {
    return std::sqrt(
        st::foldl(
            st::zipwith(
                a, b,
                [](auto x, auto y) { return (y - x) * (y - x); }
            ),
            [](auto acc, auto x) { return acc + x; },
            0.0
        )
    );
}
```

---

## Template Metaprogramming

### Compile-Time Tuple Introspection

```cpp
#include <supertuple/api.h>

// Get tuple size
template <typename T>
void process(const T& tuple) {
    constexpr size_t n = std::tuple_size_v<T>;
    process_impl(tuple, std::make_index_sequence<n>{});
}

// Helper to process with indices
template <typename T, size_t ...I>
void process_impl(const T& tuple, std::index_sequence<I...>) {
    // Process each element
    (process_element(st::get<I>(tuple)), ...);  // C++17 fold expression
}
```

### Conditional Type Operations

```cpp
// Apply different operations based on type
template <typename T>
auto transform_element(const T& elem) {
    if constexpr (std::is_integral_v<T>) {
        return elem * 2;
    } else if constexpr (std::is_floating_point_v<T>) {
        return elem / 2.0;
    } else {
        return elem;  // Other types unchanged
    }
}

auto mixed = st::tuple_t(1, 2.5, "text");
auto transformed = st::apply(mixed, transform_element<decltype(?)>);  // Won't work directly
```

### Type Transformation Metafunctions

```cpp
// Metafunction to get tuple element types
template <typename Tuple>
struct tuple_element_types;

template <typename ...T>
struct tuple_element_types<st::tuple_t<T...>> {
    using types = std::tuple<T...>;
};

// Usage in templates
template <typename Tuple>
void generic_processor(const Tuple& t) {
    using element_types = typename tuple_element_types<Tuple>::types;
    // Can now use element_types for generic processing
}
```

---

## Performance Best Practices

### Move Semantics

```cpp
// Good: Pass by rvalue when you won't reuse
auto result = st::append(std::move(tuple), element);

// Less efficient: Copies by default
auto another = st::append(tuple, element);

// Very good: Chain operations with moves
auto final = st::foldl(
    st::apply(std::move(data), transform),
    reduce_fn,
    initial
);
```

### Avoid Unnecessary Copies

```cpp
// Inefficient: Multiple intermediate tuples
auto t1 = st::apply(data, fn1);
auto t2 = st::apply(t1, fn2);
auto result = st::foldl(t2, fn3, init);

// Better: Direct composition where possible
auto result = st::foldl(
    st::apply(
        st::apply(data, fn1),
        fn2
    ),
    fn3,
    init
);
```

### Compile-Time Optimization

```cpp
// Compiler can optimize full computation
constexpr auto static_result = compute_everything();

// Instead of runtime computation
auto runtime_result = compute_at_runtime();
```

---

## See Also

- [Tuple Types](tuples.md) — Understanding tuple types
- [Performance Guide](performance.md) — Optimization strategies
- [Operations Reference](operations/README.md) — Detailed operation docs
