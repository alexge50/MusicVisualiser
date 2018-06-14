cmake_minimum_required(VERSION 3.11)
project(MusicVisualiser)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
find_package(Portaudio REQUIRED)

# glad
set(GLAD_INCLUDE_DIR glad/include/)
set(GLAD_SOURCE glad/src/glad.c)

include_directories(
        ${OPENGL_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIRS}
        ${PORTAUDIO_INCLUDE_DIRS}
        ${GLAD_INCLUDE_DIR}
)

set(SOURCE_FILES main.cpp
                 Render.cpp
                 Renderer.h
                 IGraphRenderer.h
                 util.h OscilloscopeRenderer.cpp OscilloscopeRenderer.h BaseRenderer.cpp BaseRenderer.h)

add_executable(MusicVisualiser ${SOURCE_FILES} ${GLAD_SOURCE})
target_link_libraries(MusicVisualiser dl ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES} ${PORTAUDIO_LIBRARIES})