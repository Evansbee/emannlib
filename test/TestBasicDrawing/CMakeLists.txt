cmake_minimum_required (VERSION 3.0)

file(GLOB ALL_SOURCE_FILES
    "*.h"
    "*.cpp"
    "*.hpp"
)

add_executable(BasicDrawingTests ${ALL_SOURCE_FILES})


if(MSVC)
target_link_libraries(BasicDrawingTests PUBLIC ${FREETYPE_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY} emannlib-graphics emannlib-math emannlib-common emannlib-filesystem ${OPENGL_LIBRARIES})
endif (MSVC)

if(APPLE)
target_link_libraries(BasicDrawingTests PUBLIC ${FREETYPE_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY} emannlib-graphics emannlib-math emannlib-common emannlib-filesystem ${EXTRA_LIBS})
endif (APPLE)