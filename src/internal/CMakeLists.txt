# add the static internal library - this is supposed to expose basically everything for unit testing
add_library(ifcLibInternal STATIC)
target_include_directories(ifcLibInternal PUBLIC "${PROJECT_SOURCE_DIR}/src/internal")

target_sources(ifcLibInternal PRIVATE
	IfcFileTokenizer.cpp
)
