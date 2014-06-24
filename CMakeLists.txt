cmake_minimum_required (VERSION 3.0)

project (emannlib)

set (emannlib_VERSION_MAJOR 0)
set (emannlib_VERSION_MINOR 1)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

add_subdirectory(src)
add_subdirectory(test)
