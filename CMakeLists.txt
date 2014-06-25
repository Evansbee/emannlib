cmake_minimum_required (VERSION 3.0)

project (emannlib)

# Nothing uses this yet
set (emannlib_VERSION_MAJOR 0)
set (emannlib_VERSION_MINOR 1)

# sets the output locations for all
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

if(MSVC)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/lib)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/lib)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/bin)

	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/lib)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/lib)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/bin)
endif (MSVC)


# this might work
link_directories(${CMAKE_CURRENT_LIST_DIR}/3rdparty/lib)

# we know this works, sets the 3rd party include directories for
# all projects
include_directories(${CMAKE_CURRENT_LIST_DIR}/3rdparty/include)

#find all relevant directories
#
#find_package(GLFW_LIBRARY REQUIRED glfw3)
#find_package(GLEW_LIBRARY REQUIRED glew32s)
#find_package(FREETYPE_LIBRARY REQUIRED freetype253)

add_subdirectory(src)
add_subdirectory(test)
