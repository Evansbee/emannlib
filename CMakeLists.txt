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



find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)


#find all relevant directories
if(MSVC)
set(GLFW_LIBRARY ${PROJECT_SOURCE_DIR}/3rdparty/lib/glfw3d.lib)
set(GLEW_LIBRARY ${PROJECT_SOURCE_DIR}/3rdparty/lib/glew32sd.lib)
set(FREETYPE_LIBRARY ${PROJECT_SOURCE_DIR}/3rdparty/lib/freetype253d.lib)
endif (MSVC)

if(APPLE)
set(GLFW_LIBRARY ${PROJECT_SOURCE_DIR}/3rdparty/lib/libglfw3d.a)
set(GLEW_LIBRARY ${PROJECT_SOURCE_DIR}/3rdparty/lib/libGLEW.a)
set(FREETYPE_LIBRARY ${PROJECT_SOURCE_DIR}/3rdparty/lib/libfreetyped.a)
endif (APPLE)

IF(APPLE)
   #SET(GUI_TYPE MACOSX_BUNDLE)
   INCLUDE_DIRECTORIES ( /Developer/Headers/FlatCarbon )
   FIND_LIBRARY(COCOA_LIBRARY Cocoa)
   MARK_AS_ADVANCED (COCOA_LIBRARY)
   SET(EXTRA_LIBS ${COCOA_LIBRARY} )
ENDIF (APPLE)


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
