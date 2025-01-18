#add_executable(app main.cpp)
#target_link_libraries(app PUBLIC GEO_LIB EA_LIB)
set(CMAKE_OSX_ARCHITECTURES arm64)
enable_testing()

add_executable(
  EA_APP
  EACircle.cpp
  main.cpp
)
target_link_libraries(
  EA_APP
  PUBLIC
  GEO_LIB
  EA_LIB
)