project ( Framebuffer )

find_path( GLEW_INCLUDE_DIR "GL/glew.h" )
find_library( GLEW_LIBRARIES GLEW )

include(${GLEW_INCLUDE_DIR})

find_package( OpenGL REQUIRED)

add_executable(Framebuffer main.cpp Render.cpp Types.cpp)
target_link_libraries(Framebuffer ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} glfw)
