cmake_minimum_required(VERSION 3.10)

# set the project name
project(ifcPlayground VERSION 0.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_BUILD_FILES_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(ifcPlayground)

target_include_directories(ifcPlayground PUBLIC "${PROJECT_SOURCE_DIR}/src")
add_subdirectory(src)
