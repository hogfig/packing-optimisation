add_library(GEO_LIB STATIC Circle.cpp CircleFactory.cpp IGeometry.cpp IGeometryData.cpp Logger.cpp GeometryHelper.cpp CircleData.cpp)

target_include_directories(GEO_LIB PUBLIC "./")