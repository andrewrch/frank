cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(frank CXX)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)

add_subdirectory(src)

add_library(
  frank
  SHARED
  ${FRANK_SRC}
)

target_link_libraries(frank
  ${OpenGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${GLFW_STATIC_LIBRARIES}
  ${FT_LIBRARIES}
  "-ljpeg"
  )

include_directories(
  "include"
  "ext/linmath.h"
  ${GLFW_INCLUDE_DIRS}
  ${FT_INCLUDE_DIRS}
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

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
