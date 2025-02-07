set(CMAKE_OSX_ARCHITECTURES arm64)
enable_testing()

add_executable(
  MULTITHREADING_TEST
  ThreadPoolTest.cpp
)
target_link_libraries(
  MULTITHREADING_TEST
  PUBLIC
  MULTITHREADING
)
target_link_libraries(
  MULTITHREADING_TEST
  PUBLIC
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(MULTITHREADING_TEST)