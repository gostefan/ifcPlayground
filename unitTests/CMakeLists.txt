include(FetchContent)

set(BUILD_GMOCK OFF)

FetchContent_Declare(
  gtest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.10.0)
FetchContent_MakeAvailable(gtest)

add_executable(ifcLibUnitTests
	main.cpp
)

target_link_libraries(ifcLibUnitTests PRIVATE ifcLibInternal gtest)
