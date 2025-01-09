set(CMAKE_OSX_ARCHITECTURES arm64)
enable_testing()

add_executable(
  GEOMETRY_TESTS
  CircleDataTest.cpp
  CircleFactoryTest.cpp
  AlignGeometryTest.cpp
)
target_link_libraries(
  GEOMETRY_TESTS
  PUBLIC
  GEO_LIB
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(GEOMETRY_TESTS)