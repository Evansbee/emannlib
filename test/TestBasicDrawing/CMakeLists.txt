cmake_minimum_required (VERSION 3.0)

file(GLOB ALL_SOURCE_FILES
    "*.h"
    "*.cpp"
    "*.hpp"
)

add_executable(BasicDrawingTests ${ALL_SOURCE_FILES})

if(MSVC)
target_link_libraries(BasicDrawingTests PUBLIC ${FREETYPE_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY} emannlib-graphics.lib emannlib-math.lib emannlib-common.lib ${OPENGL_LIBRARIES})
endif (MSVC)

if(APPLE)
target_link_libraries(BasicDrawingTests PUBLIC ${FREETYPE_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY} emannlib-graphics.a emannlib-math.a emannlib-common.a ${OPENGL_LIBRARIES})
endif (APPLE)