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
#target_link_libraries(emannlib-graphics ${FREETYPE_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY})

