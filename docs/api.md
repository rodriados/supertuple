# API Reference

This document provides a detailed API reference for SuperTuple types and functions.

## Core Types

### `tuple_t<T...>`

The main tuple type that stores elements of types `T...`.

```cpp
template <typename ...T>
class tuple_t;
```

**Template Parameters:**
- `T...`: The types of elements stored in the tuple

**Members:**
- `static constexpr size_t count`: The number of elements in the tuple
- `tuple_t() = default`: Default constructor
- `tuple_t(U&&... value)`: Constructor from values
- `tuple_t(const tuple_t<U...>& other)`: Copy constructor
- `tuple_t(tuple_t<U...>&& other)`: Move constructor

**Example:**
```cpp
auto empty_tuple = st::tuple_t<>();
auto int_tuple = st::tuple_t(1, 2, 3);
auto mixed_tuple = st::tuple_t(1, 2.5, "hello");
```

### `ntuple_t<T, N>`

A tuple with N elements of the same type T.

```cpp
template <typename T, size_t N>
using ntuple_t = /* implementation */;
```

**Template Parameters:**
- `T`: The element type
- `N`: The number of elements

**Example:**
```cpp
auto points = st::ntuple_t<double, 3>(1.0, 2.0, 3.0);
```

## File Organization

SuperTuple documentation is organized into several sections for easy navigation:

### Core Concepts

- **This file (api.md)** — Type definitions and core interfaces
- **[Tuple Types](tuples.md)** — In-depth guide to choosing and using tuple_t, ntuple_t, pair_t
- **[Interoperability Guide](interop.md)** — Converting between SuperTuple and std::tuple
- **[Usage Guide](usage.md)** — Getting started with practical examples

### Operations Reference

All 21 SuperTuple operations are documented individually with complete signatures, behavior descriptions, and examples:

- **[Operations Index](operations.md)** — Quick reference to all operations by category
- **[Detailed Operations](operations/README.md)** — Full documentation for each operation in its own file

Operations are organized into 5 functional categories:
1. **Access** — `get`, `set`, `tie`
2. **List** — `head`, `tail`, `last`, `init`, `append`, `prepend`, `concat`, `reverse`, `select`
3. **Folding** — `fold`, `scan`
4. **Transformation** — `apply`, `zip`, `zipwith`, `convert`
5. **Iteration** — `foreach`, `forward`

### Advanced Topics & Performance

- **[Advanced Topics](advanced.md)** — Compile-time computing, CUDA support, template metaprogramming, composition patterns
- **[Performance Guide](performance.md)** — Complexity analysis, optimization strategies, benchmarking
- **[FAQ](faq.md)** — Common questions and answers

---

## Access Operations

### `get<I>(tuple)`

Retrieves the element at compile-time index I.

```cpp
template <size_t I, typename ...T>
constexpr auto get(const tuple_t<T...>& tuple);
```

**Template Parameters:**
- `I`: The index of the element to retrieve (0-based)

**Parameters:**
- `tuple`: The tuple to access

**Return Value:**
- The element at index I

**Example:**
```cpp
auto tuple = st::tuple_t(10, 20, 30);
auto first = st::get<0>(tuple);  // 10
```

### `set<I>(tuple, value)`

Creates a new tuple with the element at index I replaced.

```cpp
template <size_t I, typename T, typename U, typename ...V>
constexpr auto set(const tuple_t<T, U, V...>& tuple, const T& value);
```

**Template Parameters:**
- `I`: The index of the element to replace

**Parameters:**
- `tuple`: The original tuple
- `value`: The new value for the element

**Return Value:**
- A new tuple with the element replaced

**Example:**
```cpp
auto tuple = st::tuple_t(1, 2, 3);
auto modified = st::set<1>(tuple, 42);  // tuple_t(1, 42, 3)
```

### `tie(array)`

Creates a tuple that references elements of a C-style array.

```cpp
template <typename T, size_t N>
constexpr auto tie(T (&array)[N]);
```

**Template Parameters:**
- `T`: The array element type
- `N`: The array size

**Parameters:**
- `array`: The C-style array to reference

**Return Value:**
- A tuple containing references to the array elements

**Example:**
```cpp
double arr[] = {1.0, 2.0, 3.0};
auto tuple = st::tie(arr);
```

## List Operations

### `head(tuple)`

Returns the first element of the tuple.

```cpp
template <typename T, typename ...U>
constexpr auto head(const tuple_t<T, U...>& tuple);
```

**Parameters:**
- `tuple`: The tuple (must have at least one element)

**Return Value:**
- The first element

### `last(tuple)`

Returns the last element of the tuple.

```cpp
template <typename ...T>
constexpr auto last(const tuple_t<T...>& tuple);
```

**Parameters:**
- `tuple`: The tuple (must have at least one element)

**Return Value:**
- The last element

### `tail(tuple)`

Returns a tuple containing all elements except the first.

```cpp
template <typename T, typename ...U>
constexpr auto tail(const tuple_t<T, U...>& tuple);
```

**Parameters:**
- `tuple`: The tuple (must have at least one element)

**Return Value:**
- A tuple with all elements except the first

### `init(tuple)`

Returns a tuple containing all elements except the last.

```cpp
template <typename ...T>
constexpr auto init(const tuple_t<T...>& tuple);
```

**Parameters:**
- `tuple`: The tuple (must have at least one element)

**Return Value:**
- A tuple with all elements except the last

### `select(tuple, index_sequence)`

Selects elements by indexes and returns a new tuple containing only selected items.

```cpp
template <id_t ...K, id_t ...I, typename ...T>
constexpr auto select(const tuple_t<T...>& tuple, std::index_sequence<K...> indices);
```

**Parameters:**
- `tuple`: The tuple to select values from
- `indices`: The index sequence of element positions to retain

**Return Value:**
- A tuple containing the selected elements

## Construction Operations

### `append(tuple, element)`

Appends an element to the end of the tuple.

```cpp
template <typename ...T, typename U>
constexpr auto append(const tuple_t<T...>& tuple, U&& element);
```

**Parameters:**
- `tuple`: The original tuple
- `element`: The element to append

**Return Value:**
- A new tuple with the element appended

### `prepend(tuple, element)`

Prepends an element to the beginning of the tuple.

```cpp
template <typename ...T, typename U>
constexpr auto prepend(const tuple_t<T...>& tuple, U&& element);
```

**Parameters:**
- `tuple`: The original tuple
- `element`: The element to prepend

**Return Value:**
- A new tuple with the element prepended

### `concat(tuple1, tuple2)`

Concatenates two tuples.

```cpp
template <typename ...T, typename ...U>
constexpr auto concat(const tuple_t<T...>& a, const tuple_t<U...>& b);
```

**Parameters:**
- `a`: The first tuple
- `b`: The second tuple

**Return Value:**
- A tuple containing elements from both input tuples

### `reverse(tuple)`

Reverses the order of elements in the tuple.

```cpp
template <typename ...T>
constexpr auto reverse(const tuple_t<T...>& tuple);
```

**Parameters:**
- `tuple`: The tuple to reverse

**Return Value:**
- A tuple with elements in reverse order

## Folding Operations

### `foldl(tuple, function, initial)`

Performs a left fold with an initial value.

```cpp
template <typename F, typename B, size_t ...I, typename ...T>
constexpr auto foldl(const tuple_t<...>& tuple, F&& lambda, B&& base);
```

**Parameters:**
- `tuple`: The tuple to fold
- `lambda`: Binary function (accumulator, element) -> new_accumulator
- `base`: Initial accumulator value

**Return Value:**
- The final accumulator value

### `foldl(tuple, function)`

Performs a left fold without initial value.

```cpp
template <typename F, size_t ...I, typename ...T>
constexpr auto foldl(const tuple_t<...>& tuple, F&& lambda);
```

**Parameters:**
- `tuple`: The tuple to fold (must have at least one element)
- `lambda`: Binary function (accumulator, element) -> new_accumulator

**Return Value:**
- The final accumulator value

### `foldr(tuple, function, initial)`

Performs a right fold with an initial value.

```cpp
template <typename F, typename B, size_t ...I, typename ...T>
constexpr auto foldr(const tuple_t<...>& tuple, F&& lambda, B&& base);
```

**Parameters:**
- `tuple`: The tuple to fold
- `lambda`: Binary function (element, accumulator) -> new_accumulator
- `base`: Initial accumulator value

**Return Value:**
- The final accumulator value

### `foldr(tuple, function)`

Performs a right fold without initial value.

```cpp
template <typename F, size_t ...I, typename ...T>
constexpr auto foldr(const tuple_t<...>& tuple, F&& lambda);
```

**Parameters:**
- `tuple`: The tuple to fold (must have at least one element)
- `lambda`: Binary function (element, accumulator) -> new_accumulator

**Return Value:**
- The final accumulator value

## Scanning Operations

### `scanl(tuple, function, initial)`

Performs a left scan with initial value.

```cpp
template <typename F, typename B, size_t ...I, typename ...T>
constexpr auto scanl(const tuple_t<...>& tuple, F&& lambda, B&& base);
```

**Parameters:**
- `tuple`: The tuple to scan
- `lambda`: Binary function (accumulator, element) -> new_accumulator
- `base`: Initial accumulator value

**Return Value:**
- A tuple containing all intermediate accumulator values

### `scanr(tuple, function, initial)`

Performs a right scan with initial value.

```cpp
template <typename F, typename B, size_t ...I, typename ...T>
constexpr auto scanr(const tuple_t<...>& tuple, F&& lambda, B&& base);
```

**Parameters:**
- `tuple`: The tuple to scan
- `lambda`: Binary function (element, accumulator) -> new_accumulator
- `base`: Initial accumulator value

**Return Value:**
- A tuple containing all intermediate accumulator values

## Mapping Operations

### `apply(tuple, function)`

Applies a unary function to each element.

```cpp
template <typename F, size_t ...I, typename ...T>
constexpr auto apply(const tuple_t<...>& tuple, F&& function);
```

**Parameters:**
- `tuple`: The input tuple
- `function`: Unary function to apply to each element

**Return Value:**
- A tuple with the function applied to each element

### `apply(tuple, function, arg)`

Applies a binary function to each element with a constant argument.

```cpp
template <typename F, typename U, size_t ...I, typename ...T>
constexpr auto apply(const tuple_t<...>& tuple, F&& function, U&& arg);
```

**Parameters:**
- `tuple`: The input tuple
- `function`: Binary function to apply
- `arg`: Constant argument for the function

**Return Value:**
- A tuple with the function applied to each element

## Zipping Operations

### `zip(tuple1, tuple2)`

Combines two tuples element-wise into pairs.

```cpp
template <size_t ...I, size_t ...J, typename ...T, typename ...U>
constexpr auto zip(const tuple_t<...>& a, const tuple_t<...>& b);
```

**Parameters:**
- `a`: First tuple
- `b`: Second tuple (must have same size as a)

**Return Value:**
- A tuple of tuples, where each inner tuple contains corresponding elements

### `zipwith(tuple1, tuple2, function)`

Combines two tuples element-wise using a function.

```cpp
template <typename F, size_t ...I, typename ...T, typename ...U>
constexpr auto zipwith(const tuple_t<...>& a, const tuple_t<...>& b, F&& function);
```

**Parameters:**
- `a`: First tuple
- `b`: Second tuple (must have same size as a)
- `function`: Binary function to combine corresponding elements

**Return Value:**
- A tuple with the function applied to corresponding elements

## Iteration Operations

### `foreach(tuple, function)`

Applies a function to each element for side effects.

```cpp
template <typename F, size_t ...I, typename ...T>
constexpr void foreach(const tuple_t<...>& tuple, F&& function);
```

**Parameters:**
- `tuple`: The tuple to iterate over
- `function`: Unary function to apply to each element

**Return Value:**
- void

### `rforeach(tuple, function)`

Applies a function to each element in reverse order for side effects.

```cpp
template <typename F, size_t ...I, typename ...T>
constexpr void rforeach(const tuple_t<...>& tuple, F&& function);
```

**Parameters:**
- `tuple`: The tuple to iterate over in reverse
- `function`: Unary function to apply to each element

**Return Value:**
- void

## Conversion Operations

### `convert<NewType>(tuple)`

Converts all elements to a new type.

```cpp
template <typename U, typename ...T>
constexpr auto convert(const tuple_t<T...>& tuple);
```

**Template Parameters:**
- `U`: The target type for conversion

**Parameters:**
- `tuple`: The tuple to convert

**Return Value:**
- A tuple with all elements converted to type U

### `forward(tuple, function)`

Forwards tuple elements as arguments to a function.

```cpp
template <typename F, typename ...T>
constexpr auto forward(const tuple_t<T...>& tuple, F&& function);
```

**Parameters:**
- `tuple`: The tuple whose elements will be forwarded
- `function`: A callable that accepts the tuple elements as arguments

**Return Value:**
- The result of calling function with the tuple elements

### `from_std(tuple)`

Converts a std::tuple to a supertuple::tuple_t.

```cpp
template <typename ...T>
constexpr auto from_std(const std::tuple<T...>& tuple);

template <typename ...T>
constexpr auto from_std(std::tuple<T...>&& tuple);
```

**Parameters:**
- `tuple`: The std::tuple to convert (lvalue or rvalue reference)

**Return Value:**
- A supertuple::tuple_t with the same element types and values

**Example:**
```cpp
std::tuple<int, double> std_tuple(42, 3.14);
auto super_tuple = st::from_std(std_tuple);  // tuple_t<int, double>
```

### `to_std(tuple)`

Converts a supertuple::tuple_t to a std::tuple.

```cpp
template <typename ...T>
constexpr auto to_std(const tuple_t<T...>& tuple);

template <typename ...T>
constexpr auto to_std(tuple_t<T...>&& tuple);
```

**Parameters:**
- `tuple`: The supertuple::tuple_t to convert (lvalue or rvalue reference)

**Return Value:**
- A std::tuple with the same element types and values

**Example:**
```cpp
auto super_tuple = st::tuple_t(42, 3.14);
std::tuple<int, double> std_tuple = st::to_std(super_tuple);
```

## Constants and Types

- `tuple_t<T...>::count`: Number of elements in the tuple
- `tuple_t<T...>::element_t<I>`: Type of element at index I
- `tuple_t<T...>::accessor_t<I>`: Reference type for element at index I

## Requirements

- C++17 or later
- All operations are `constexpr` when possible
- Functions may have additional constraints (e.g., non-empty tuples for head/last)
