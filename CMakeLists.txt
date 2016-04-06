cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(frank CXX)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)

add_subdirectory(include)
add_subdirectory(src)

add_library(
  frank
  SHARED
  ${FRANK_HEADERS}
  ${FRANK_SRC}
)

add_definitions(-DGLEW_STATIC)

target_link_libraries(frank
  ${OpenGL_LIBRARIES}
  ${OPENGL_gl_LIBRARY}
  ${OPENGL_glu_LIBRARY}
  ${GLEW_LIBRARY}
  ${GLFW_glfw_LIBRARIES}
  )

target_include_directories(
  frank
  PUBLIC
  "include"
  "ext/linmath.h"
  ${GLFW_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIR}
  )

target_compile_features(frank PRIVATE cxx_range_for)

add_custom_target(debug
  COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
  COMMENT "Switch CMAKE_BUILD_TYPE to Debug"
  )

add_custom_target(release
  COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release ${CMAKE_SOURCE_DIR}
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
  COMMENT "Switch CMAKE_BUILD_TYPE to Release"
  )
