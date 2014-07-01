cmake_minimum_required (VERSION 3.0)

file(GLOB ALL_SOURCE_FILES
    "*.h"
    "*.cpp"
    "*.hpp"
)

add_executable(UnitTests ${ALL_SOURCE_FILES})

target_link_libraries(UnitTests PUBLIC ${FREETYPE_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY})