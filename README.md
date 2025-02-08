# SuperTuple
![license MIT](https://img.shields.io/badge/license-MIT-lightgrey.svg)
![version dev](https://img.shields.io/badge/version-1.1-green.svg)

A powerful yet lightweight C++17 tuple implementation for functional-programming.

## Motivation
As a functional-programming enthusiast, specially for [Haskell](https://www.haskell.org/),
I've always found it fascinating how some algorithms can be programmed in such a
descripitive way and yet be extremely performant. Not only so, it has always bothered
me how some solutions may look very clean when developed in a functional paradigm,
whereas quite clumsy otherwise.

**SuperTuple** provides memory-efficient tuple implementation, equivalent to a struct
containing the same types, designed for functional programming. The library emphasizes
clean, descriptive code with zero runtime overhead for many operations due to `constexpr`
evaluation. While `std::tuple` is versatile, it lacks the functional operations
and memory efficiency that **SuperTuple** provides.

## Features
- **Header-only**: Include a single header and you are ready to go.
- **Haskell-inspired API**: Familiar naming and behavior for functional programmers.
- **Template Metaprogramming**: Leverages compile-time evaluation for efficiency.
- **Composable**: Functions can be chained for expressive and readable code.
- **Zero Runtime Overhead**: Operations are evaluated at compile-time using `constexpr`.

## Install
**SuperTuple** is a single-header library. To use it:
- Either **copy the header** by downloading `supertuple.h` from the
[latest release](https://github.com/rodriados/supertuple/releases/latest) and including
it directly in your project.
- Or use **CMake integration** to install via CMake for project or system-wide use.

## Usage
**SuperTuple** provides a functional tuple type, `supertuple::tuple_t`, and a variety
of operations inspired by Haskell’s list functions. Below is an example of a key
operation.

## Example
The `foldl` function performs a reduce operation over a tuple with an optional initial
value and a binary operation.
```cpp
#include <supertuple/api.h>

constexpr auto result = supertuple::foldl(
    supertuple::tuple_t(1, 2, 3)
  , [](auto acc, auto x) { return acc + x; }
); // result == 6 (1 + 2 + 3)
```

## License

**SuperTuple** is licensed under the MIT License. See
[LICENSE](https://github.com/rodriados/supertuple/blob/main/LICENSE) for details.

## Contributing

Contributions are welcome! Please submit issues or pull requests via the
[GitHub repository](https://github.com/rodriados/supertuple). Ensure code follows
C++17 standards and includes appropriate tests.
