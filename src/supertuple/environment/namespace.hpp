/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file Namespace configuration and macro definitions.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

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
#define SUPERTUPLE_END_NAMESPACE        \
    }}
