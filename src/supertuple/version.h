/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Compiler-time macros encoding SuperTuple release version.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

/**
 * The preprocessor macros encoding the current SuperTuple library release version.
 * This is guaranteed to change with every SuperTuple release.
 */
#define SUPERTUPLE_VERSION 10102

/**
 * The preprocessor macros encoding the release policy's values to the current SuperTuple
 * library release version.
 */
#define SUPERTUPLE_VERSION_MAJOR (SUPERTUPLE_VERSION / 10000)
#define SUPERTUPLE_VERSION_MINOR (SUPERTUPLE_VERSION / 100 % 100)
#define SUPERTUPLE_VERSION_PATCH (SUPERTUPLE_VERSION % 100)
/**#@-*/
