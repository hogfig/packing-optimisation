set(CMAKE_OSX_ARCHITECTURES arm64)
enable_testing()

add_executable(
  EA_TESTS
  GenotypeDataTests.cpp
  GenotypeTests.cpp
  PopulationTests.cpp
  EvolutionAlgorithmTest.cpp
)
target_link_libraries(
  EA_TESTS
  PUBLIC
  GEO_LIB
  EA_LIB
)
target_link_libraries(
  EA_TESTS
  PUBLIC
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(EA_TESTS)