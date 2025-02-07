set(CMAKE_OSX_ARCHITECTURES arm64)
add_library(EA_LIB STATIC IEvolutionAlgorithm.cpp Genotype.cpp Population.cpp GenotypeData.cpp)

target_include_directories(EA_LIB PUBLIC "./")
target_link_libraries(EA_LIB PUBLIC GEO_LIB MULTITHREADING)