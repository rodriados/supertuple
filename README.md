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

This project implements new tuple types, in opposition to `std::tuple`, with the
focus of creating tuples that are memory-equivalent to a _struct_ containing the
same types, in addition to functional operations that operate over them.

This library does not intend to implement or enable a full functional-programming
experience in C++, but to allow specific solutions to be abstracted with descriptive
and clean code.

## Features
- **Header-only**: just include a header and you are ready to go.
- **Haskell-inspired API**: familiar naming for functional programmers.
- **Template metaprogramming**: works at compile-time wherever possible.
- **Composable**: functions can be chained in expressive ways.
- **Zero runtime overhead** for many operations due to `constexpr` evaluation.

## Install
SuperTuple is a single-header library that can be included directly in your source
tree and does not have any dependencies other than a C++17-compatible compiler to
be installed in your system.


## Usage
To use the the library, you can simply copy the source file into your own project
or install it on your system via CMake and then reference it in your code:
```cpp
#include <supertuple.h>
```

## Example
The equivalent of a `zipWith` operation in Haskell could be implemented as:
```cpp
#include <supertuple.h>

constexpr auto result = supertuple::zipwith(
    supertuple::tuple_t(1, 2, 3)
  , supertuple::tuple_t(4, 5, 6)
  , [](auto x, auto y) { return x + y; }
); // result == supertuple::tuple_t(5, 7, 9)
```
