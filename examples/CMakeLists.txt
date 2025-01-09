# SuperTuple: A powerful and light-weight C++ tuple implementation.
# @file CMake examples configuration file.
# @author Rodrigo Siqueira <rodriados@gmail.com>
# @copyright 2025-present Rodrigo Siqueira
if(BUILD_TESTING)
  file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

  add_executable(examples ${TEST_SOURCES})
  target_link_libraries(examples PRIVATE Catch2::Catch2WithMain ${PROJECT_NAME})
  target_include_directories(examples PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/test)

  include_external_dependency(Catch)
  catch_discover_tests(examples)
endif()
