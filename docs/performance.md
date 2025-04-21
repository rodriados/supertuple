# Performance Guide

Optimization strategies and performance characteristics of SuperTuple operations.

## Zero-Abstraction Semantics

SuperTuple implements **zero-abstraction semantics**: the performance of tuple operations should be equivalent to hand-written code.

### Principle

```cpp
// SuperTuple version
auto data = st::tuple_t(1, 2, 3, 4, 5);
auto sum = st::foldl(data, [](auto acc, auto x) { return acc + x; }, 0);

// Equivalent hand-written version
int sum_manual = 0;
sum_manual += 1; sum_manual += 2; sum_manual += 3; sum_manual += 4; sum_manual += 5;

// Assembly: IDENTICAL
// Both compile to the exact same machine code with optimizations enabled
```

### Verification

Compile with optimizations (`-O2` or `-O3`) and inspect generated assembly:

```bash
# Check assembly output
g++ -O3 -S code.cpp
# Compare SuperTuple operations with manual implementations
# You'll find they produce identical assembly

# Or use Compiler Explorer: https://godbolt.org/
```

---

## Compilation & Runtime Complexity

### Compile-Time Complexity

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| `get<I>` | O(1) | Direct field access |
| `set<I>` | O(N) | Creates new tuple (all elements) |
| `apply` | O(N) | Applies function to each element |
| `foldl` | O(N) | Processes each element once |
| `zip` | O(min(N,M)) | Pairs elements |
| `append` | O(N) | Creates new tuple with all elements |
| `concat` | O(N+M) | Combines sequences |
| `reverse` | O(N) | Reorders all elements |
| `select` | O(K) | K = number of selected indices |

**Implications:**
- More operations → longer compilation time
- Deep nesting of operations → potentially slower builds
- Large tuples (100+ elements) → noticeable compilation delay
- Constexpr evaluation might require more build time than runtime equivalents

### Runtime Complexity

With optimizations enabled (`-O2`, `-O3`), all compile-time-determined operations have **zero runtime cost**:

```cpp
// These compile to no-ops or direct calculations
constexpr auto result = st::foldl(st::tuple_t(1,2,3), [](auto a, auto b) { return a + b; }, 0);
// result == 6, computed entirely at compile time
```

---

## Memory Layout & Alignment

### Tuple Size

SuperTuple tuples have minimal overhead:

```cpp
auto t1 = st::tuple_t(1, 2, 3);
// Size approximately: sizeof(int) + sizeof(int) + sizeof(int) + possible padding

auto t2 = st::tuple_t(1, 2.5, true);
// Size approximately: sizeof(int) + sizeof(double) + sizeof(bool) + potential padding

// Verify actual size
static_assert(sizeof(t1) <= 3 * sizeof(int));
```

### Alignment

Elements are aligned according to their types for efficient memory access:

```cpp
// Likely layout:
// | padding | double (8 bytes) | int (4 bytes) | bool (1 byte) | padding |
auto mixed = st::tuple_t<double, int, bool>(3.14, 42, true);

// Alignment ensures:
// - Each element accessed efficiently
// - No performance penalty for misalignment
// - Can safely cast to array pointer (for contiguous types)
```

### Cache Efficiency

For homogeneous tuples (`ntuple_t<T, N>`), memory layout is contiguous and cache-friendly:

```cpp
// Optimized for cache locality
auto point = st::ntuple_t<double, 1000>(...);

// Iteration benefits from cache prefetching
st::foreach(point, [](double x) {
    process(x);  // Sequential access, excellent cache behavior
});
```

---

## Optimization Strategies

### 1. Use Constexpr When Possible

```cpp
// ✓ GOOD: Computation at compile time
constexpr auto result = st::foldl(
    st::tuple_t(1, 2, 3),
    [](auto a, auto b) { return a + b; },
    0
);

// ✓ BETTER: If you must compute at runtime, help the compiler
inline auto compute_inline() {
    return st::foldl(data, fn, 0);
}

// ✗ AVOID: Unnecessary runtime computation
auto suboptimal = st::foldl(setup_tuple(), expensive_fn, 0);
```

### 2. Perfect Forwarding & Move Semantics

```cpp
// ✓ GOOD: Use move for temporary tuples
auto extended = st::append(std::move(temporary), element);

// ✓ GOOD: Pass by const& for reuse
void process(const MyTuples& data) {
    auto sum = st::foldl(data, add, 0);
    auto product = st::foldl(data, multiply, 1);  // Reuses data
}

// ✓ GOOD: Use move for final result
return st::append(std::move(result), final_element);

// ✗ AVOID: Unnecessary copies
auto copied = st::append(tuple, element);  // Copies when move available
```

### 3. Const Correctness

```cpp
// ✓ GOOD: Const enables compiler optimizations
auto sum = st::foldl(const_data, add, 0);

// ✓ GOOD: Mark functions const
const MyData compute_const() const {
    return st::apply(data, transform);
}

// ✗ AVOID: Non-const references prevent optimizations
auto sum = st::foldl(mutable_data, add, 0);  // Compiler assumes mutable_data changes
```

### 4. Operate on References When Appropriate

```cpp
// For large tuples, use references
const auto& large_data = get_large_tuple();
auto sum = st::foldl(large_data, add, 0);  // No copy

// For small POD tuples, pass by value (often faster due to register allocation)
auto small = st::tuple_t(1, 2, 3);
auto result = operate(small);  // May be faster as value
```

### 5. Avoid Unnecessary Intermediate Tuples

```cpp
// ✗ INEFFICIENT: Multiple temporary tuples
auto r1 = st::apply(data, f1);
auto r2 = st::apply(r1, f2);
auto r3 = st::foldl(r2, f3, 0);

// ✓ EFFICIENT: Direct composition
auto result = st::foldl(
    st::apply(
        st::apply(data, f1),
        f2
    ),
    f3,
    0
);

// ✓ ALSO EFFICIENT: Declare as inline/constexpr
constexpr auto result = compute_everything();
```

### 6. Use Homogeneous Tuples for Vectors

```cpp
// ✓ BETTER: ntuple_t for numeric vectors
auto point = st::ntuple_t<double, 3>(1.0, 2.0, 3.0);
auto magnitude = std::sqrt(
    st::foldl(
        st::apply(point, [](auto x) { return x * x; }),
        [](auto a, auto b) { return a + b; },
        0.0
    )
);

// ✗ LESS IDEAL: tuple_t for numeric vectors
auto mixed = st::tuple_t(1.0, 2.0, 3.0);  // Works but less optimized
```

---

## Operation-Specific Performance Notes

### `get<I>` — O(1), Zero Cost

Direct field access with no runtime overhead.

```cpp
auto first = st::get<0>(tuple);  // Single memory access
```

### `apply` — O(N), Minimal Cost

Applies function N times. Optimization depends on function complexity.

```cpp
// Compiler likely unrolls or vectorizes
auto squared = st::apply(numbers, [](auto x) { return x * x; });

// With expensive function, cost scales linearly
auto computed = st::apply(data, expensive_computation);  // O(N * cost(fn))
```

### `foldl`/`foldr` — O(N), Minimal Cost

Accumulation with linear complexity. Difficult to vectorize (sequentially dependent).

```cpp
// Fast: Simple accumulation
auto sum = st::foldl(data, [](auto a, auto b) { return a + b; }, 0);

// Slower: Complex fold function
auto custom = st::foldl(data, complex_calculation, init);
```

### `zip`/`zipwith` — O(min(N,M)), Minimal Cost

Pairing or combining two sequences.

```cpp
// Linear in shorter sequence length
auto combined = st::zipwith(a, b, [](auto x, auto y) { return x + y; });
```

### `reverse` — O(N), Minor Cost

Reorders elements. Compiler typically generates efficient code.

```cpp
// Similar performance to manually reversing
auto rev = st::reverse(tuple);
```

### `select` — O(K), Minimal Cost

K = number of selected indices.

```cpp
// K=3: Selects 3 elements
auto selected = st::select(tuple, std::index_sequence<0, 2, 5>{});

// Very fast for small K
auto pair = st::select(tuple, std::index_sequence<1, 3>{});  // Just 2 elements
```

---

## Benchmarking Tips

### Simple Benchmark Template

```cpp
#include <chrono>
#include <supertuple/api.h>

namespace st = supertuple;

int main() {
    auto data = st::ntuple_t<double, 1000>(...init data...);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000000; ++i) {
        auto result = st::foldl(data, add, 0.0);
        [[maybe_unused]] volatile auto _ = result;  // Prevent optimization
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Time: " << duration.count() << "ms\n";
}
```

### Compiler Optimization Flags

Always benchmark with optimizations:

```bash
# GCC/Clang
g++ -O2 benchmark.cpp -o benchmark_O2
g++ -O3 benchmark.cpp -o benchmark_O3
g++ -Ofast benchmark.cpp -o benchmark_ofast

# MSVC
cl /O2 benchmark.cpp
cl /Ox benchmark.cpp
```

### Compare with Alternatives

```cpp
// Benchmark SuperTuple
auto result_st = st::foldl(data, add, 0);

// Benchmark std::tuple (if applicable)
auto result_std = std::get<0>(std::tuple(...));

// Benchmark hand-written equivalent
int result_manual = /* ... */;

// Compare generated assembly
```

---

## Known Limitations & Workarounds

### Deep Template Nesting → Slow Compilation

**Problem:** Complex compositions compile slowly.

```cpp
// Slow to compile
auto result = st::foldl(st::apply(st::zipwith(...), ...), ...);
```

**Workaround:** Break into intermediate steps.

```cpp
auto step1 = st::zipwith(...);
auto step2 = st::apply(step1, ...);
auto result = st::foldl(step2, ...);
```

### Large Tuples (100+ Elements)

**Problem:** Type explosion, long compilation, large binaries.

```cpp
// Expensive to compile
auto huge = st::tuple_t(v1, v2, ..., v100);
```

**Workaround:** Use `ntuple_t` for homogeneous collections, or reduce tuple size.

```cpp
auto optimized = st::ntuple_t<int, 100>(...);  // Better than heterogeneous
auto split = st::tuple_t(part1, part2, part3);  // Split into logical groups
```

### Runtime Tuples (Dynamic Sizes)

**Problem:** SuperTuple works only at compile time with fixed sizes.

**Workaround:** For dynamic sizes, use `std::vector` or `std::tuple`.

```cpp
// SuperTuple: fixed-size, compile-time guaranteed
auto known_size = st::ntuple_t<int, 5>(...);

// For unknown size: use std::vector
std::vector<int> dynamic(n);
```

---

## Compiler-Specific Notes

### GCC

- Excellent constexpr optimization
- Good vectorization of homogeneous operations
- May require `-std=c++17` or higher

### Clang

- Aggressive inlining and optimization
- Better constexpr time tracking
- Good diagnostics for template issues

### MSVC

- Strong constexpr support
- Good loop unrolling
- May require `/std:c++latest` for full C++20 support

---

## Summary: Performance Checklist

- [ ] Use constexpr when computation is compile-time determinable
- [ ] Enable compiler optimizations (`-O2` or `-O3`)
- [ ] Use move semantics for temporary tuples
- [ ] Avoid unnecessary intermediate tuples
- [ ] Use `ntuple_t` for numeric vectors
- [ ] Mark functions const when appropriate
- [ ] Benchmark with `-O2` or `-O3` optimizations
- [ ] Compare assembly with manual equivalents
- [ ] Break complex compositions if compilation is slow
- [ ] Use `std::vector` for dynamic-sized collections

---

## See Also

- [Advanced Topics](advanced.md) — Compile-time computing details
- [Operations Reference](operations/README.md) — Detailed operation costs
- [Tuple Types](tuples.md) — Choosing between tuple types
