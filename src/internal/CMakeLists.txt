# add the static internal library - this is supposed to expose basically everything for unit testing
add_library(ifcLibInternal STATIC)
target_include_directories(ifcLibInternal PUBLIC "${PROJECT_SOURCE_DIR}/src/internal")

string(REGEX REPLACE "/W3" "/Wall" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX") Don't treat warnings as errors for now
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4514") # Ignore unreferenced inline function warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4710") # Ignore warning about not inlined functions
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4820") # Ignore warning about padding being added

target_sources(ifcLibInternal PRIVATE
	IfcFileTokenizer.cpp
)
