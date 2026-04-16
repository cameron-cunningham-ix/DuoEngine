cmake_minimum_required(VERSION 3.21) # 3.21+ for TARGET_RUNTIME_DLLS
project(DuoEngine
    VERSION 0.0.1
    DESCRIPTION "2D & 3D Rendering Engine"
    LANGUAGES CXX C
)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------
# Default to Release for single-config generators (Ninja/Make)
# -----------------------------
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

include(FetchContent)

# -----------------------------
# OpenGL
# -----------------------------
find_package(OpenGL REQUIRED)

# -----------------------------
# GLFW
# -----------------------------
# Turn off GLFW's examples 
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Disable GLFW examples" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Disable GLFW tests" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Disable GLFW docs" FORCE)
add_subdirectory(external/glfw)

# -----------------------------
# GLM
# -----------------------------
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 8d1fd52e5ab5590e2c81768ace50c72bae28f2ed # v1.0.3
)
FetchContent_MakeAvailable(glm)

# -----------------------------
# GLAD
# -----------------------------
add_library(glad STATIC external/glad/glad.c)
target_include_directories(glad PUBLIC external)

# -----------------------------
# Dear ImGui (use OpenGL3 and GLFW backends)
# -----------------------------
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG docking
)

FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
  FetchContent_Populate(imgui)

  add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp

    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp

  )

  target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
  )
  target_link_libraries(imgui PUBLIC glfw OpenGL::GL)
endif()

# -----------------------------
# Native File Dialog Extended
# -----------------------------
FetchContent_Declare(
    nfd
    GIT_REPOSITORY https://github.com/btzy/nativefiledialog-extended.git
    GIT_TAG 86d5f2005fe1c00747348a12070fec493ea2407e    # v1.2.1
)
FetchContent_MakeAvailable(nfd)

# -----------------------------
# Executable
# -----------------------------
add_executable(DuoEngine
  main.cpp
  src/renderer/Shader.cpp
)

target_include_directories(DuoEngine PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(DuoEngine PRIVATE glm::glm glad imgui nfd)
# if(TARGET SDL3::SDL3main)
#   target_link_libraries(DuoEngine PRIVATE SDL3::SDL3main)
# endif()

# Warnings
if(MSVC)
  target_compile_options(DuoEngine PRIVATE /W4 /wd4101 /permissive- /Zc:preprocessor /utf-8)
else()
  target_compile_options(DuoEngine PRIVATE -Wall -Wextra -Wpedantic -Wno-unused-parameter)
endif()

# Nice output layout (esp. on MSVC multi-config)
set_target_properties(DuoEngine PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>"
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>"
)