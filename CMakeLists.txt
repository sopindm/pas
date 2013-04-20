project(Asteroids)

find_path( GLEW_INCLUDE_DIR "GL/glew.h" )
find_library( GLEW_LIBRARIES GLEW )

include(${GLEW_INCLUDE_DIR})

find_package( OpenGL REQUIRED)

add_executable(Asteroids main.cpp Render.cpp Types.cpp EventLoop.cpp Objects.cpp Window.cpp)
target_link_libraries(Asteroids ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} glfw)
