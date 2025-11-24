cmake_minimum_required(VERSION 3.16)
project(gladAndGLFWWrapper)

set(CMAKE_LANGUAGE CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG latest
)
FetchContent_MakeAvailable(glfw)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/externalLib/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/externalLib
)

file( SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GLBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GLContext.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GLDebug.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GLMesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GLShaderFile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GLShaderProgram.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GLTexture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stc/GLTimer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GLutils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/externalLib/glad/src/glad.c
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

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