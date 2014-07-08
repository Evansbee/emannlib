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

if(APPLE)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/lib)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/lib)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin)

	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/lib)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/lib)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin)
endif (APPLE)


# this might work
link_directories(${PROJECT_SOURCE_DIR}/3rdparty/lib)
link_directories(${PROJECT_SOURCE_DIR}/lib)

# we know this works, sets the 3rd party include directories for
# all projects
include_directories(${PROJECT_SOURCE_DIR}/3rdparty/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

#find all my libraries
find_package(OpenGL REQUIRED)
find_library(GLFW_LIBRARY NAMES glfw3d glfw3 PATHS ${PROJECT_SOURCE_DIR}/3rdparty/ PATH_SUFFIXES lib NO_DEFAULT_PATH)
find_library(GLEW_LIBRARY NAMES glew32sd glew32s GLEW PATHS ${PROJECT_SOURCE_DIR}/3rdparty/	PATH_SUFFIXES lib NO_DEFAULT_PATH)
find_library(FREETYPE_LIBRARY NAMES freetype253d freetype253 freetype freetyped	PATHS ${PROJECT_SOURCE_DIR}/3rdparty/ PATH_SUFFIXES lib	NO_DEFAULT_PATH)


include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(FATAL_ERROR  " OPENGL not found!")
endif(NOT OPENGL_FOUND)

if(GLFW_LIBRARY-NOTFOUND)
	message(FATAL_ERROR  "GLFW Not Found")
endif(GLFW_LIBRARY-NOTFOUND)

if(GLEW_LIBRARY-NOTFOUND)
	message(FATAL_ERROR  "GLEW Not Found")
endif(GLEW_LIBRARY-NOTFOUND)

if(FREETYPE_LIBRARY-NOTFOUND)
	message(FATAL_ERROR  "FREETYPE Not Found")
endif(FREETYPE_LIBRARY-NOTFOUND)


#if(APPLE)
#	set(GLFW_LIBRARY ${PROJECT_SOURCE_DIR}/3rdparty/lib/libglfw3d.a)
#	set(GLEW_LIBRARY ${PROJECT_SOURCE_DIR}/3rdparty/lib/libGLEW.a)
#	set(FREETYPE_LIBRARY ${PROJECT_SOURCE_DIR}/3rdparty/lib/libfreetyped.a)
#endif (APPLE)

IF(APPLE)

	add_definitions(-std=c++11 -stdlib=libc++)

	INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
	FIND_PATH(COREVIDEO_INCLUDE_DIR CoreVideo/CoreVideo.h)
	FIND_LIBRARY(COREVIDEO_LIBRARY CoreVideo)
	FIND_LIBRARY(COCOA_LIBRARY Cocoa)
	FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
	FIND_LIBRARY(IOKit_LIBRARY IOKit )


	MARK_AS_ADVANCED (	COCOA_LIBRARY
						GLUT_LIBRARY
						IOKit_LIBRARY
						COREVIDEO_LIBRARY	)
	SET(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKit_LIBRARY} ${COREVIDEO_LIBRARY})
ENDIF (APPLE)

add_subdirectory(src)
add_subdirectory(test)
