# SuperTuple: A powerful and light-weight C++ tuple implementation.
# @file The CMake script for including Catch2 test framework.
# @author Rodrigo Siqueira <rodriados@gmail.com>
# @copyright 2025-present Rodrigo Siqueira
set(CATCH2_REPOSITORY "https://github.com/catchorg/Catch2.git")
set(CATCH2_REPOSITORY_TAG "v3.5.4")

FetchContent_Declare(
  Catch2
    GIT_REPOSITORY ${CATCH2_REPOSITORY}
    GIT_TAG ${CATCH2_REPOSITORY_TAG}
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

include(Catch)
