# Contributing

We welcome contributions to SuperTuple! This document provides guidelines for contributing to the project.

## Development Setup

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.24+
- Python 3.6+ (for the header packing script)
- Git

### Building from Source

```bash
# Clone the repository
git clone https://github.com/rodriados/supertuple.git
cd supertuple

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build
make

# Run tests
ctest
```

### Development Build

For development with additional checks:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug -DSUPERTUPLE_DEVELOPMENT_BUILD=ON
```

This enables:
- Test building
- Warning-as-errors
- Additional compiler warnings

## Code Style

### C++ Standards

- Use C++17 features
- Follow the existing code style in the project
- Use `constexpr` wherever possible
- Prefer template metaprogramming over runtime computation
- Use descriptive variable and function names

### Naming Conventions

- Types: `PascalCase` (e.g., `tuple_t`, `leaf_t`)
- Functions: `snake_case` (e.g., `foldl`, `zipwith`)
- Template parameters: Single uppercase letters (e.g., `T`, `U`, `F`)
- Constants: `SCREAMING_SNAKE_CASE` with `SUPERTUPLE_` prefix

### Code Organization

- Keep implementation in `.hpp` files in appropriate subdirectories
- Use the `supertuple` namespace
- Group related functionality in operation subdirectories
- Include necessary headers with full paths

## Testing

### Running Tests

```bash
# From build directory
ctest

# Or run specific test
ctest -R "test_name"

# Run with verbose output
ctest -V
```

### Writing Tests

Tests use [Catch2](https://github.com/catchorg/Catch2) framework. Add tests in the `test/` directory:

```cpp
#include <supertuple/api.h>
#include <catch2/catch_test_macros.hpp>

namespace st = supertuple;

TEST_CASE("my new operation", "[operation]") {
    auto tuple = st::tuple_t(1, 2, 3);

    SECTION("basic functionality") {
        auto result = st::my_operation(tuple);
        REQUIRE(result == expected_value);
    }

    SECTION("edge cases") {
        auto empty_tuple = st::tuple_t<>();
        // Test edge cases
    }
}
```

### Test Coverage

- Test all public APIs
- Include edge cases (empty tuples, single elements, etc.)
- Test `constexpr` evaluation where applicable
- Verify compile-time and runtime behavior

## Documentation

### Code Documentation

- Use Doxygen-style comments for public APIs
- Document template parameters
- Explain complex algorithms
- Provide usage examples in comments

### Example

```cpp
/**
 * Performs a left-fold reduction over a tuple.
 * @tparam F The functor type to fold the tuple with.
 * @tparam B The fold operation base type.
 * @tparam I The tuple sequence indeces.
 * @tparam T The tuple's element members types.
 * @param t The tuple to fold.
 * @param lambda The functor used to fold the tuple with.
 * @param base The folding base value.
 * @return The fold resulting value.
 */
template <typename F, typename B, size_t ...I, typename ...T>
SUPERTUPLE_CONSTEXPR decltype(auto) foldl(
    const tuple_t<detail::identity_t<std::index_sequence<I...>>, T...>& t
  , F&& lambda
  , B&& base
);
```

## Pull Request Process

1. **Fork** the repository
2. **Create a feature branch** from `master`
3. **Make your changes** following the guidelines above
4. **Add tests** for new functionality
5. **Update documentation** if needed
6. **Ensure all tests pass**
7. **Submit a pull request** with a clear description

### Pull Request Guidelines

- Use a descriptive title
- Reference any related issues
- Provide a clear description of changes
- Include tests and documentation updates
- Keep changes focused and atomic

### Commit Messages

- Use clear, descriptive commit messages
- Start with a verb (Add, Fix, Update, etc.)
- Keep the first line under 50 characters
- Provide additional context in the body if needed

Examples:
```
Add zipwith operation for element-wise tuple combination
Fix compile error in fold operations with empty tuples
Update documentation for new API functions
```

## Issue Reporting

### Bug Reports

When reporting bugs, please include:

- SuperTuple version
- Compiler and version
- Operating system
- Minimal code example that reproduces the issue
- Expected vs. actual behavior
- Any error messages

### Feature Requests

For feature requests:

- Clearly describe the proposed feature
- Explain the use case and motivation
- Provide examples of how it would be used
- Consider backward compatibility

## Project Structure

```
supertuple/
├── src/supertuple/          # Source code
│   ├── api.h                # Main API header
│   ├── tuple.hpp            # Core tuple implementation
│   ├── operation/           # Operation implementations
│   └── detail/              # Internal utilities
├── test/                    # Test files
├── examples/                # Example usage
├── cmake/                   # CMake configuration
├── support/                 # Build utilities
└── docs/                    # Documentation
```

## Performance Considerations

- Maintain zero runtime overhead for `constexpr` operations
- Avoid unnecessary copies
- Use perfect forwarding where appropriate
- Consider compile-time evaluation opportunities

## License

By contributing to SuperTuple, you agree that your contributions will be licensed under the MIT License.

## Getting Help

- Check existing issues and documentation
- Ask questions in GitHub discussions
- Review the examples and tests for usage patterns

Thank you for contributing to SuperTuple!
