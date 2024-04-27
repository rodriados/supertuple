/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Environment configuration and macro values
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <supertuple/version.h>

#include <supertuple/environment/compiler.h>
#include <supertuple/environment/language.h>
#include <supertuple/environment/annotations.h>
#include <supertuple/environment/namespace.hpp>

/*
 * Enumerates all possible target environment modes to which the code might be compiled
 * to. The environment mode may affect some features' availability and performace.
 */
#define SUPERTUPLE_BUILD_DEV        0
#define SUPERTUPLE_BUILD_DEBUG      1
#define SUPERTUPLE_BUILD_TESTING    2
#define SUPERTUPLE_BUILD_PRODUCTION 3

/*
 * Discovers and explicits the target environment mode to which the code must be
 * currently compiled to. The mode may affect some features' availability and performance.
 */
#if defined(DEBUG) || defined(_DEBUG)
  #define SUPERTUPLE_BUILD SUPERTUPLE_BUILD_DEBUG
  #define SUPERTUPLE_ENVIRONMENT "Debug"
#elif defined(TESTING)
  #define SUPERTUPLE_BUILD SUPERTUPLE_BUILD_TESTING
  #define SUPERTUPLE_ENVIRONMENT "Testing"
#elif defined(DEV) || defined(DEVELOPMENT)
  #define SUPERTUPLE_BUILD SUPERTUPLE_BUILD_DEV
  #define SUPERTUPLE_ENVIRONMENT "Development"
#else
  #define SUPERTUPLE_BUILD SUPERTUPLE_BUILD_PRODUCTION
  #define SUPERTUPLE_ENVIRONMENT "Production"
#endif

/*
 * Checks the current compiler's C++ language level. As the majority of this software's
 * codebase is written in C++, we must check whether its available or not.
 */
#if !defined(SUPERTUPLE_IGNORE_CPP_DIALECT)
  #if !defined(SUPERTUPLE_CPP_DIALECT) || SUPERTUPLE_CPP_DIALECT < 2017
    #error This software requires at least a C++17 enabled compiler.
  #endif
#endif

/*
 * Checks whether the current compiler is compatible with the software's prerequisites.
 * Should it not be compatible, then we emit a warning but try compiling anyway.
 */
#if !defined(SUPERTUPLE_IGNORE_COMPILER_CHECK) && SUPERTUPLE_BUILD == SUPERTUPLE_BUILD_PRODUCTION
  #if SUPERTUPLE_HOST_COMPILER == SUPERTUPLE_HOST_COMPILER_UNKNOWN
    #warning This software has not been tested with the current compiler.
  #endif
#endif
