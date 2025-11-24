cmake_minimum_required(VERSION 3.16)
project(gladAndGLFWWrapper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG latest
)
FetchContent_MakeAvailable(glfw)

set( SOURCES
    src/GLBuffer.cpp
    src/GLContext.cpp
    src/GLDebug.cpp
    src/GLMesh.cpp
    src/GLShaderFile.cpp
    src/GLShaderProgram.cpp
    src/GLTexture.cpp
    src/GLTimer.cpp
    src/GLUtils.cpp
    externalLib/glad/src/glad.c
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/externalLib/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/externalLib
)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

if (UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE X11 pthread dl m)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/externalLib/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/externalLib
)