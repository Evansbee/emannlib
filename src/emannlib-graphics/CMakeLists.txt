cmake_minimum_required (VERSION 3.0)

file(GLOB ALL_SOURCE_FILES
    "*.h"
    "*.cpp"
    "*.hpp"
)

if (MSVC)
	set(ARCHIVE_OUTPUT_NAME_DEBUG ${ARCHIVE_OUTPUT_NAME}d)
	set(LIBRARY_OUTPUT_NAME_DEBUG ${LIBRARY_OUTPUT_NAME}d)
endif (MSVC)


add_library(emannlib-graphics STATIC ${ALL_SOURCE_FILES})

message("Freetype libraries: " ${FREETYPE_LIBRARY})

message("Glfw libraries: " ${GLFW_LIBRARY})
message("Glew libraries: " ${GLEW_LIBRARY})


target_link_libraries(emannlib-graphics PUBLIC ${FREETYPE_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY})

