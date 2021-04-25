cmake_minimum_required(VERSION 3.14)

project(
	ifcPlayground
	VERSION 0.1
	DESCRIPTION "Let's have some fun with IFC"
	LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_BUILD_FILES_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

string(REGEX REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

message("CXX Flags ${CMAKE_CXX_FLAGS_DEBUG}")

add_subdirectory(src/internal)
add_subdirectory(src/public)

# Testing only available if this is the main app
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	add_subdirectory(unitTests)
endif()
 