# SuperTuple: A powerful and light-weight C++ tuple implementation.
# @file Script responsible for finding the Catch2 project.
# @author Rodrigo Siqueira <rodriados@gmail.com>
# @copyright 2025-present Rodrigo Siqueira
include(FetchContent)

set(CATCH2_REPOSITORY "https://github.com/catchorg/Catch2.git")
set(CATCH2_REPOSITORY_TAG "v3.5.4")

# Let's try checking whether the project is already known and/or cached. If so,
# we should avoid unnecessary downloads, thus improving build performance.
find_package(Catch2 QUIET CONFIG)

if(NOT Catch2_FOUND)
  FetchContent_Declare(
    Catch2
      GIT_SHALLOW true
      GIT_REPOSITORY ${CATCH2_REPOSITORY}
      GIT_TAG ${CATCH2_REPOSITORY_TAG})
  FetchContent_MakeAvailable(Catch2)
endif()

# Now that the package is guaranteed to be known, we must configure it so that its
# variables and targets are made available in the callee context.
find_package(Catch2 CONFIG REQUIRED)

# Also, a helper function for automatically finding tests is provided. We must include
# this function as well, to provide a better downstream experience.
include(Catch)
