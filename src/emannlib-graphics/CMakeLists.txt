cmake_minimum_required (VERSION 3.0)

file(GLOB ALL_SOURCE_FILES
    "*.h"
    "*.cpp"
    "*.hpp"
)
add_library(emannlib-graphics STATIC ${ALL_SOURCE_FILES})
target_link_libraries(emannlib-graphics freetype253.lib glew32s.lib glfw3.lib)

