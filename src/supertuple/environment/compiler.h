/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Compiler-specific configurations and macro definitions.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

/*
 * Enumerating known host compilers. These compilers are not all necessarily officially
 * supported. Nevertheless, some special adaptation or fixes might be implemented
 * to each one of these if so needed.
 */
#define SUPERTUPLE_HOST_COMPILER_UNKNOWN 0
#define SUPERTUPLE_HOST_COMPILER_GCC     1
#define SUPERTUPLE_HOST_COMPILER_CLANG   2

/*
 * Enumerating known device compilers. These compilers are not all necessarily officially
 * supported. Nevertheless, some special adaptation or fixes might be implemented
 * to each one of these if so needed.
 */
#define SUPERTUPLE_DEVICE_COMPILER_UNKNOWN 0
#define SUPERTUPLE_DEVICE_COMPILER_GCC     1
#define SUPERTUPLE_DEVICE_COMPILER_CLANG   2
#define SUPERTUPLE_DEVICE_COMPILER_NVCC    3

/*
 * Finds the version of the host compiler being used. Some features might change
 * or be unavailable depending on the current compiler configuration.
 */
#if defined(__clang__)
  #define SUPERTUPLE_HOST_COMPILER SUPERTUPLE_HOST_COMPILER_CLANG
  #define SUPERTUPLE_CLANG_VERSION (__clang_major__ * 100 + __clang_minor__)
#elif defined(__GNUC__) || defined(__GNUG__)
  #define SUPERTUPLE_HOST_COMPILER SUPERTUPLE_HOST_COMPILER_GCC
  #define SUPERTUPLE_GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
#else
  #define SUPERTUPLE_HOST_COMPILER SUPERTUPLE_HOST_COMPILER_UNKNOWN
#endif

/*
 * Finds the version of the device compiler being used. Some features might change
 * or be unavailable depending on the current compiler configuration.
 */
#if defined(__clang__)
  #define SUPERTUPLE_DEVICE_COMPILER SUPERTUPLE_DEVICE_COMPILER_CLANG
#elif defined(__CUDACC__) || defined(__NVCOMPILER_CUDA__)
  #define SUPERTUPLE_DEVICE_COMPILER SUPERTUPLE_DEVICE_COMPILER_NVCC
#elif SUPERTUPLE_HOST_COMPILER == SUPERTUPLE_HOST_COMPILER_GCC
  #define SUPERTUPLE_DEVICE_COMPILER SUPERTUPLE_DEVICE_COMPILER_GCC
#else
  #define SUPERTUPLE_DEVICE_COMPILER SUPERTUPLE_DEVICE_COMPILER_UNKNOWN
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
  #if (SUPERTUPLE_HOST_COMPILER == SUPERTUPLE_HOST_COMPILER_GCC)
    #define SUPERTUPLE_EMIT_COMPILER_WARNING(msg)           \
      SUPERTUPLE_EMIT_PRAGMA_CALL(GCC warning msg)
  #elif (SUPERTUPLE_HOST_COMPILER == SUPERTUPLE_HOST_COMPILER_CLANG)
    #define SUPERTUPLE_EMIT_COMPILER_WARNING(msg)           \
      SUPERTUPLE_EMIT_PRAGMA_CALL(clang warning msg)
  #else
    #define SUPERTUPLE_EMIT_COMPILER_WARNING(msg)
  #endif
#endif

/*
 * Macro for disabling or manually emitting warnings when compiling host code with
 * GCC. This is useful for hiding buggy compiler warnings or compiler exploits that
 * have intentionally been taken advantage of.
 */
#if (SUPERTUPLE_HOST_COMPILER == SUPERTUPLE_HOST_COMPILER_GCC) && !defined(__CUDA_ARCH__)
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

#if (SUPERTUPLE_HOST_COMPILER == SUPERTUPLE_HOST_COMPILER_CLANG)
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

/*
 * Macro for pushing compiling options for GCC. These allow certain compiler behaviors
 * to be modified for the code within the block of changed settings.
 */
#if (SUPERTUPLE_HOST_COMPILER == SUPERTUPLE_HOST_COMPILER_GCC) && !defined(__CUDA_ARCH__)
  #define SUPERTUPLE_PUSH_GCC_OPTION_BEGIN(x)               \
    SUPERTUPLE_EMIT_PRAGMA_CALL(GCC push_options)           \
    SUPERTUPLE_EMIT_PRAGMA_CALL(GCC x)
  #define SUPERTUPLE_PUSH_GCC_OPTION_END(x)                 \
    SUPERTUPLE_EMIT_PRAGMA_CALL(GCC pop_options)
#else
  #define SUPERTUPLE_PUSH_GCC_OPTION_BEGIN(x)
  #define SUPERTUPLE_PUSH_GCC_OPTION_END(x)
#endif

/*
 * Macro for disabling warnings when compiling device code with NVCC. This is useful
 * for hiding buggy compiler warnings or intentional compiler exploits.
 */
#if (SUPERTUPLE_DEVICE_COMPILER == SUPERTUPLE_DEVICE_COMPILER_NVCC)
  #define SUPERTUPLE_DISABLE_NVCC_WARNING_BEGIN(x)          \
    SUPERTUPLE_EMIT_PRAGMA_CALL(push)                       \
    SUPERTUPLE_EMIT_PRAGMA_CALL(nv_diag_suppress = x)
  #define SUPERTUPLE_DISABLE_NVCC_WARNING_END(x)            \
    SUPERTUPLE_EMIT_PRAGMA_CALL(pop)
#else
  #define SUPERTUPLE_DISABLE_NVCC_WARNING_BEGIN(x)
  #define SUPERTUPLE_DISABLE_NVCC_WARNING_END(x)
#endif
