cmake_minimum_required(VERSION 2.8)
project(parallel)

set(CMAKE_CXX_STANDARD 11)

# Set our binary folder
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# Make sure we can import our CMake functions
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Import our CMake modules
include(AddCXXCompilerFlag)

# Add some compiler flags
add_cxx_compiler_flag(-std=c++11)
add_cxx_compiler_flag(-Wall)
add_cxx_compiler_flag(-pthread)
add_cxx_compiler_flag(-fopenmp)

set(SOURCE_FILES src/main.cpp src/tools/vector3.cpp src/tools/vector3.hpp src/tools/stopwatch.h src/environment/entity.cpp src/environment/entity.hpp src/environment/virtualenvironment.cpp src/environment/virtualenvironment.hpp src/tools/entitygenerator.cpp src/tools/entitygenerator.hpp src/gjk/gjk.cpp src/gjk/gjk.hpp src/gjk/simplex.cpp src/gjk/simplex.hpp src/test/test.cpp)
add_executable(parallel ${SOURCE_FILES})
