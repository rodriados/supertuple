# SuperTuple: A powerful and light-weight C++ tuple implementation.
# @file CMake configuration file.
# @author Rodrigo Siqueira <rodriados@gmail.com>
# @copyright 2025-present Rodrigo Siqueira
cmake_minimum_required(VERSION 3.15)

# Determines whether the current project is the master target or it is being built
# as a dependency, potentially as a thirdparty, to an external project.
if(NOT DEFINED SUPERTUPLE_MASTER_PROJECT)
  set(SUPERTUPLE_MASTER_PROJECT OFF)
  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(SUPERTUPLE_MASTER_PROJECT ON)
    message(STATUS "Project: SuperTuple")
    message(STATUS "CMake version: ${CMAKE_VERSION}")
  endif()
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Command line options to control the conditions and generation of the targets.
# The targets may be enabled on demand, depending on the user or environment needs.
option(SUPERTUPLE_INSTALL "Generate the install target." ${SUPERTUPLE_MASTER_PROJECT})
option(SUPERTUPLE_INSTALL_DOCS "Install documentation alongside library." ON)

include(CMakeDependentOption)
cmake_dependent_option(SUPERTUPLE_DEVELOPMENT_BUILD "Build tests, enable warnings and errors." ON "BUILD_TESTING" OFF)
cmake_dependent_option(SUPERTUPLE_BUILD_TESTING "Generate the test targets." ON "SUPERTUPLE_DEVELOPMENT_BUILD" OFF)
cmake_dependent_option(SUPERTUPLE_BUILD_EXAMPLES "Build code examples." OFF "SUPERTUPLE_DEVELOPMENT_BUILD" OFF)
cmake_dependent_option(SUPERTUPLE_ENABLE_COVERAGE "Generate test coverage." OFF "SUPERTUPLE_DEVELOPMENT_BUILD" OFF)
cmake_dependent_option(SUPERTUPLE_ENABLE_PEDANTIC "Errors on warnings." ON "SUPERTUPLE_DEVELOPMENT_BUILD" OFF)

# Provides paths for scripts. We first add path to the scripts we don't use but
# parent projects might, and set the path up to parent scope.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/support")
if(NOT SUPERTUPLE_MASTER_PROJECT)
  set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" PARENT_SCOPE)
endif()
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(HelperFunctions)

# Discovers the project's current version and initializes it. The version is retrieved
# from a source file where the version should be explicitly set.
get_project_version(SUPERTUPLE_VERSION "src/supertuple/version.h")

project(SuperTuple
  LANGUAGES CXX
  VERSION ${SUPERTUPLE_VERSION}
  HOMEPAGE_URL "https://github.com/rodriados/supertuple"
  DESCRIPTION "A powerful and light-weight C++ tuple implementation.")

# Installation, configuration and targets variables. These variables are used to
# define where the project must be installed on and where to store its config files.
set(SUPERTUPLE_CMAKE_CONFIG_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/SuperTuple")
set(SUPERTUPLE_INCLUDE_DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/supertuple")
set(SUPERTUPLE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(SUPERTUPLE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/SuperTupleConfigVersion.cmake")
set(SUPERTUPLE_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/SuperTupleConfig.cmake")
set(SUPERTUPLE_CONFIG_FILE_TEMPLATE "${CMAKE_CURRENT_LIST_DIR}/cmake/SuperTupleConfig.cmake.in")
set(SUPERTUPLE_TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
endif()

# As we define our library as header-only, we must allow all header files to be
# found and eventually exported and installed in the user machine.
add_library(SuperTuple INTERFACE)
add_library(SuperTuple::SuperTuple ALIAS SuperTuple)

target_compile_features(SuperTuple INTERFACE cxx_std_17)
target_include_directories(SuperTuple
  INTERFACE
    $<BUILD_INTERFACE:${SUPERTUPLE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Sets the compiler flags for a pedantic compilation. We mostly assume that the
# used compiler is GNU-compatible, although some special cases might be cared for.
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(PEDANTIC_COMPILE_FLAGS -pedantic-errors -Wall -Wextra -pedantic -Werror)
elseif(MSVC)
  set(PEDANTIC_COMPILE_FLAGS /W3 /WX)
endif()

if(SUPERTUPLE_ENABLE_PEDANTIC)
  target_compile_options(SuperTuple INTERFACE ${PEDANTIC_COMPILE_FLAGS})
endif()

# Installs the library by copying all needed files to their corresponding destination
# folders. The library should be installed globally in the user system.
if(SUPERTUPLE_INSTALL)
  install(
    TARGETS SuperTuple
    EXPORT SuperTupleTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR})

  install(
    EXPORT SuperTupleTargets
    NAMESPACE SuperTuple::
    DESTINATION ${SUPERTUPLE_CMAKE_CONFIG_DESTINATION})

  install(
    DIRECTORY "${SUPERTUPLE_SOURCE_DIR}/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

  configure_package_config_file(
    ${SUPERTUPLE_CONFIG_FILE_TEMPLATE}
    ${SUPERTUPLE_CONFIG_FILE}
    INSTALL_DESTINATION ${SUPERTUPLE_CMAKE_CONFIG_DESTINATION})

  write_basic_package_version_file(
    ${SUPERTUPLE_VERSION_FILE}
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

  install(
    FILES
      ${SUPERTUPLE_CONFIG_FILE}
      ${SUPERTUPLE_VERSION_FILE}
    DESTINATION ${SUPERTUPLE_CMAKE_CONFIG_DESTINATION})
endif()

# Declaration of targets for testing. These targets are only available when this
# project is root, therefore not used as dependency for any other.
if(SUPERTUPLE_MASTER_PROJECT AND SUPERTUPLE_DEVELOPMENT_BUILD)
  include(CTest)
  enable_testing()

  if(SUPERTUPLE_BUILD_TESTING)
    set(CMAKE_FOLDER "test")
    add_subdirectory(test)
  endif()

  if(SUPERTUPLE_BUILD_EXAMPLES)
    set(CMAKE_FOLDER "examples")
    add_subdirectory(examples)
  endif()
endif()
