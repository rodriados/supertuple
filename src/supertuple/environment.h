/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Environment configuration and macro values
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <supertuple/version.h>

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
 * Enumerating known host compilers. These compilers are not all necessarily officially
 * supported. Nevertheless, some special adaptation or fixes might be implemented
 * to each one of these if so needed.
 */
#define SUPERTUPLE_OPT_COMPILER_UNKNOWN 0
#define SUPERTUPLE_OPT_COMPILER_GCC     1
#define SUPERTUPLE_OPT_COMPILER_CLANG   2
#define SUPERTUPLE_OPT_COMPILER_NVCC    3

/*
 * Finds the version of the host compiler being used. Some features might change
 * or be unavailable depending on the current compiler configuration.
 */
#if defined(__clang__)
  #define SUPERTUPLE_COMPILER SUPERTUPLE_OPT_COMPILER_CLANG
  #define SUPERTUPLE_CLANG_VERSION (__clang_major__ * 100 + __clang_minor__)

#elif defined(__NVCC__) || defined(__NVCOMPILER_CUDA__)
  #define SUPERTUPLE_COMPILER SUPERTUPLE_OPT_COMPILER_NVCC
  #define SUPERTUPLE_NVCC_VERSION (__CUDACC_VER_MAJOR__ * 100 + __CUDACC_VER_MINOR__)

#elif defined(__GNUC__) || defined(__GNUG__)
  #define SUPERTUPLE_COMPILER SUPERTUPLE_OPT_COMPILER_GCC
  #define SUPERTUPLE_GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)

#else
  #define SUPERTUPLE_COMPILER SUPERTUPLE_OPT_COMPILER_UNKNOWN
#endif

/*
 * Macro for programmatically emitting a pragma call, independently on which compiler
 * is currently in use.
 */
#if !defined(SUPERTUPLE_EMIT_PRAGMA_CALL)
  #define SUPERTUPLE_EMIT_PRAGMA_CALL(x) _Pragma(#x)
#endif

/*
 * Macro for programmatically emitting a compiler warning. This will be shown during
 * compile-time and might stop compilation if warnings are treated as errors.
 */
#if !defined(SUPERTUPLE_EMIT_COMPILER_WARNING)
  #if (SUPERTUPLE_COMPILER == SUPERTUPLE_OPT_COMPILER_GCC)
    #define SUPERTUPLE_EMIT_COMPILER_WARNING(msg)           \
      SUPERTUPLE_EMIT_PRAGMA_CALL(GCC warning msg)
  #elif (SUPERTUPLE_COMPILER == SUPERTUPLE_OPT_COMPILER_CLANG)
    #define SUPERTUPLE_EMIT_COMPILER_WARNING(msg)           \
      SUPERTUPLE_EMIT_PRAGMA_CALL(clang warning msg)
  #else
    #define SUPERTUPLE_EMIT_COMPILER_WARNING(msg)
  #endif
#endif

/*
 * Macros for disabling or manually emitting warnings with specific compilers. This
 * is useful to treat the behaviour of a specific compiler, such as hiding buggy
 * compiler warnings or exploits that have intentionally been taken advantage of.
 */
#if (SUPERTUPLE_COMPILER == SUPERTUPLE_OPT_COMPILER_GCC) && !defined(__CUDA_ARCH__)
  #define SUPERTUPLE_EMIT_GCC_WARNING(x) SUPERTUPLE_EMIT_COMPILER_WARNING(x)
  #define SUPERTUPLE_DISABLE_GCC_WARNING_BEGIN(x)           \
    SUPERTUPLE_EMIT_PRAGMA_CALL(GCC diagnostic push)        \
    SUPERTUPLE_EMIT_PRAGMA_CALL(GCC diagnostic ignored x)
  #define SUPERTUPLE_DISABLE_GCC_WARNING_END(x)             \
    SUPERTUPLE_EMIT_PRAGMA_CALL(GCC diagnostic pop)
#else
  #define SUPERTUPLE_DISABLE_GCC_WARNING_BEGIN(x)
  #define SUPERTUPLE_DISABLE_GCC_WARNING_END(x)
  #define SUPERTUPLE_EMIT_GCC_WARNING(x)
#endif

#if (SUPERTUPLE_COMPILER == SUPERTUPLE_OPT_COMPILER_CLANG)
  #define SUPERTUPLE_EMIT_CLANG_WARNING(x) SUPERTUPLE_EMIT_COMPILER_WARNING(x)
  #define SUPERTUPLE_DISABLE_CLANG_WARNING_BEGIN(x)           \
    SUPERTUPLE_EMIT_PRAGMA_CALL(clang diagnostic push)        \
    SUPERTUPLE_EMIT_PRAGMA_CALL(clang diagnostic ignored x)
  #define SUPERTUPLE_DISABLE_CLANG_WARNING_END(x)             \
    SUPERTUPLE_EMIT_PRAGMA_CALL(clang diagnostic pop)
#else
  #define SUPERTUPLE_DISABLE_CLANG_WARNING_BEGIN
  #define SUPERTUPLE_DISABLE_CLANG_WARNING_END
  #define SUPERTUPLE_EMIT_CLANG_WARNING
#endif

#if (SUPERTUPLE_COMPILER == SUPERTUPLE_OPT_COMPILER_GCC) && !defined(__CUDA_ARCH__)
  #define SUPERTUPLE_PUSH_GCC_OPTION_BEGIN(x)               \
    SUPERTUPLE_EMIT_PRAGMA_CALL(GCC push_options)           \
    SUPERTUPLE_EMIT_PRAGMA_CALL(GCC x)
  #define SUPERTUPLE_PUSH_GCC_OPTION_END(x)                 \
    SUPERTUPLE_EMIT_PRAGMA_CALL(GCC pop_options)
#else
  #define SUPERTUPLE_PUSH_GCC_OPTION_BEGIN(x)
  #define SUPERTUPLE_PUSH_GCC_OPTION_END(x)
#endif

#if (SUPERTUPLE_COMPILER == SUPERTUPLE_OPT_COMPILER_NVCC)
  #define SUPERTUPLE_DISABLE_NVCC_WARNING_BEGIN(x)          \
    SUPERTUPLE_EMIT_PRAGMA_CALL(push)                       \
    SUPERTUPLE_EMIT_PRAGMA_CALL(nv_diag_suppress = x)
  #define SUPERTUPLE_DISABLE_NVCC_WARNING_END(x)            \
    SUPERTUPLE_EMIT_PRAGMA_CALL(nv_diag_default = x)        \
    SUPERTUPLE_EMIT_PRAGMA_CALL(pop)
#else
  #define SUPERTUPLE_DISABLE_NVCC_WARNING_BEGIN(x)
  #define SUPERTUPLE_DISABLE_NVCC_WARNING_END(x)
#endif

/*
 * Discovers the C++ language dialect in use for the current compilation. A specific
 * dialect might not be supported or might be required for certain functionalities
 * to work properly.
 */
#if defined(__cplusplus)
  #if __cplusplus < 201103L
    #define SUPERTUPLE_CPP_DIALECT 2003
  #elif __cplusplus < 201402L
    #define SUPERTUPLE_CPP_DIALECT 2011
  #elif __cplusplus < 201703L
    #define SUPERTUPLE_CPP_DIALECT 2014
  #elif __cplusplus == 201703L
    #define SUPERTUPLE_CPP_DIALECT 2017
  #elif __cplusplus > 201703L
    #define SUPERTUPLE_CPP_DIALECT 2020
  #endif
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
  #if SUPERTUPLE_COMPILER == SUPERTUPLE_OPT_COMPILER_UNKNOWN
    #warning This software has not been tested with the current compiler.
  #endif
#endif

/*
 * Since only NVCC knows how to deal with `__host__` and `__device__` annotations,
 * we define them to empty strings when another compiler is in use. This allows
 * the use of these annotations without needing to care whether they'll be known
 * by the compiler or not.
 */
#ifdef __CUDACC__
  #define SUPERTUPLE_CUDA_ENABLED __host__ __device__
#else
  #define SUPERTUPLE_CUDA_ENABLED
#endif

/*
 * Macros for applying annotations and qualifiers to functions and methods. As the
 * minimum required language version is C++17, we assume it is guaranteed that all
 * compilers will have `inline` and `constexpr` implemented.
 */
#define SUPERTUPLE_INLINE SUPERTUPLE_CUDA_ENABLED inline
#define SUPERTUPLE_CONSTEXPR SUPERTUPLE_INLINE constexpr

/**
 * Defines the namespace in which the library lives. This might be overriden if
 * the default namespace value is already in use.
 * @since 1.0
 */
#if defined(SUPERTUPLE_OVERRIDE_NAMESPACE)
  #define SUPERTUPLE_NAMESPACE SUPERTUPLE_OVERRIDE_NAMESPACE
#else
  #define SUPERTUPLE_NAMESPACE supertuple
#endif

/**
 * This macro is used to open the `supertuple::` namespace block and must not be
 * in any way overriden. This namespace must not be prefixed by any other namespaces
 * to avoid problems when allowing the use some of the library's facilities to with
 * STL's algorithms, structures or constructions.
 * @since 1.0
 */
#define SUPERTUPLE_BEGIN_NAMESPACE      \
    namespace SUPERTUPLE_NAMESPACE {    \
        inline namespace v1 {           \
        namespace supertuple = ::SUPERTUPLE_NAMESPACE;

/**
 * This macro is used to close the `supertuple::` namespace block and must not be
 * in any way overriden.
 * @since 1.0
 */
#define SUPERTUPLE_END_NAMESPACE   }}
