cmake_minimum_required (VERSION 3.0)

project (emannlib)

# Nothing uses this yet
set (emannlib_VERSION_MAJOR 0)
set (emannlib_VERSION_MINOR 1)

# sets the output locations for all
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

if(MSVC)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/lib)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/lib)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin)

	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/lib)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/lib)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin)
endif (MSVC)


# this might work
link_directories(${PROJECT_SOURCE_DIR}/3rdparty/lib)

# we know this works, sets the 3rd party include directories for
# all projects
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/include)

#find all relevant directories
#

set(GLFW_LIBRARY ${PROJECT_SOURCE_DIR}/3rdparty/lib/glfw3.lib)
set(GLEW_LIBRARY ${PROJECT_SOURCE_DIR}/3rdparty/lib/glew32s.lib)
set(FREETYPE_LIBRARY ${PROJECT_SOURCE_DIR}/3rdparty/lib/freetype253.lib)

#find_library(GLFW NAMES "glfw3.lib" glfw3.a glfw3.so glfw3 PATHS ${PROJECT_BINARY_DIR}/3rdparty/lib NO_DEFAULT_PATH)
#find_library(GLEW NAMES "glew32s.lib" glew32s.a glew32s.so glew32s PATHS ${PROJECT_BINARY_DIR}/3rdparty/lib NO_DEFAULT_PATH)
#find_library(FREETYPE NAMES freetype253.lib freetype253.a freetype253.so freetype253 PATHS ${PROJECT_BINARY_DIR}/3rdparty/lib NO_DEFAULT_PATH)

#if(NOT GLFW_FOUND)
#	message(ERROR " GLFW Not Found")
#endif(NOT GLFW_FOUND)

#if(NOT GLEW_FOUND)
#	message(ERROR " GLEW Not Found")
#endif(NOT GLEW_FOUND)

#if(NOT FREETYPE_FOUND)
#	message(ERROR " FREETYPE Not Found")
#endif(NOT FREETYPE_FOUND)

add_subdirectory(src)
add_subdirectory(test)
