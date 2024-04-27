/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Common header file for all examples.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#include <cstdio>

/*
 * We should include macros used on examples to notate which example is curring
 * in execution, if any. These will indicate which example was running if one of
 * them fail to pass fail their assertions.
 */
#define SUPERTUPLE_EXAMPLE(i) printf(__FILE__ ": running example #%d\n", i);
#define SUPERTUPLE_PRINT(fmt, ...) printf("  " fmt "\n", __VA_ARGS__);
