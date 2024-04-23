/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Definition of compiler-specific annotations.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <supertuple/environment/compiler.h>

/*
 * Since only NVCC knows how to deal with `__host__` and `__device__` annotations,
 * we define them to empty strings when another compiler is in use. This allows
 * the use of these annotations without needing to care whether they'll be known
 * by the compiler or not.
 */
#if SUPERTUPLE_DEVICE_COMPILER == SUPERTUPLE_DEVICE_COMPILER_NVCC
  #define SUPERTUPLE_CUDA_ENABLED __host__ __device__
#else
  #define SUPERTUPLE_CUDA_ENABLED
#endif
