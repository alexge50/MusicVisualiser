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

add_library(GLFW UNKNOWN IMPORTED)
set_target_properties(GLFW PROPERTIES
        IMPORTED_LOCATION ${GLFW_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${GLFW_INCLUDE_DIRS}
        )

add_library(OPENGL UNKNOWN IMPORTED)
set_target_properties(OPENGL PROPERTIES
        IMPORTED_LOCATION ${OPENGL_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${OPENGL_INCLUDE_DIR}
        )

add_library(PORTAUDIO UNKNOWN IMPORTED)
set_target_properties(PORTAUDIO PROPERTIES
        IMPORTED_LOCATION ${PORTAUDIO_LIBRARIES}
        INTERFACE_INCLUDE_DIRECTORIES ${PORTAUDIO_INCLUDE_DIRS}
        )


include_directories(
        OPENGL
        GLFW
        PORTAUDIO
        ${GLAD_INCLUDE_DIR}
)

set(SOURCE_FILES main.cpp
                 Render.cpp
                 Renderer.h
                 IGraphRenderer.h
                 util.h
                 OscilloscopeRenderer.cpp
                 OscilloscopeRenderer.h
                 BaseRenderer.cpp
                 BaseRenderer.h
                 AudioBuffer.cpp
                 AudioBuffer.h)

add_executable(MusicVisualiser ${SOURCE_FILES} ${GLAD_SOURCE})
target_link_libraries(MusicVisualiser dl OPENGL GLFW PORTAUDIO)