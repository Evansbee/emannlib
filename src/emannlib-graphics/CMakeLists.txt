cmake_minimum_required (VERSION 3.0)

file(GLOB ALL_SOURCE_FILES
    "*.h"
    "*.cpp"
    "*.hpp"
)

add_library(emannlib-graphics STATIC ${ALL_SOURCE_FILES})