# Installation

SuperTuple is a header-only C++17 library, making it easy to integrate into your projects. There are two main ways to install and use SuperTuple:

## Option 1: Single Header File (Recommended for Quick Start)

1. Download the `supertuple.h` file from the [latest release](https://github.com/rodriados/supertuple/releases/latest).
2. Copy the header file into your project's include directory.
3. Include it in your source files:

```cpp
#include "supertuple.h"
// or
#include <supertuple.h>
```

## Option 2: CMake Integration (Recommended for Larger Projects)

SuperTuple provides CMake integration for more robust dependency management.

### Using CMake FetchContent (Modern CMake)

Add the following to your `CMakeLists.txt`:

```cmake
include(FetchContent)

FetchContent_Declare(
  supertuple
  GIT_REPOSITORY https://github.com/rodriados/supertuple.git
  GIT_TAG v1.1.2  # Use the latest version
)

FetchContent_MakeAvailable(supertuple)
```

Then link it to your target:

```cmake
target_link_libraries(your_target PRIVATE SuperTuple::SuperTuple)
```

### Manual CMake Installation

1. Clone or download the SuperTuple repository.
2. Configure and build:

```bash
cd supertuple
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/path/to/install
make install
```

3. In your project's `CMakeLists.txt`, find the installed package:

```cmake
find_package(SuperTuple REQUIRED)
target_link_libraries(your_target PRIVATE SuperTuple::SuperTuple)
```

## Requirements

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.24+ (for CMake integration)

## Testing the Installation

After installation, create a simple test file:

```cpp
#include <supertuple/api.h>

int main() {
    auto tuple = supertuple::tuple_t(1, 2, 3);
    return 0;
}
```

Compile with:

```bash
g++ -std=c++17 -I/path/to/supertuple test.cpp -o test
```

If using CMake integration, ensure your `CMakeLists.txt` sets the C++ standard:

```cmake
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```
