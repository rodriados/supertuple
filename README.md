# SuperTuple
![license MIT](https://img.shields.io/badge/license-MIT-lightgrey.svg)
![version dev](https://img.shields.io/badge/version-dev-red.svg)

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

## Install
The library does not have any dependencies other than a C++17-compiler to be installed
on your system. As a header-only library, you may as well directly download or copy
the files into your own project or clone it following the steps below:
```bash
git clone https://github.com/rodriados/supertuple
```

## Usage
To use the project, you can copy source files into your own project or install it
on your system and then reference it in your code:
```cpp
#include <supertuple.h>
```
