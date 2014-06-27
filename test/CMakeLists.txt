cmake_minimum_required (VERSION 3.0)

file(GLOB ALL_SOURCE_FILES
    "*.h"
    "*.cpp"
    "*.hpp"
)

add_executable(emannlib-tests ${ALL_SOURCE_FILES})

target_link_libraries(emannlib-tests PUBLIC ${FREETYPE_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY})