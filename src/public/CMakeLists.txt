# add the dynamic public library - this should only export the actual API
add_library(ifcLib SHARED)
target_include_directories(ifcLibInternal PUBLIC "${PROJECT_SOURCE_DIR}/src/public")
target_link_libraries(ifcLib PRIVATE ifcLibInternal)

target_sources(ifcLib PRIVATE
)
