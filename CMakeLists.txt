cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project(frank CXX)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLM REQUIRED)

add_subdirectory(include)
add_subdirectory(src)

add_library(
  frank
  SHARED
  ${FRANK_HEADERS}
  ${FRANK_SRC}
)

add_executable(
   test_window
   "./test/tst.cpp"
)

target_include_directories(
  test_window
  PUBLIC
  "include"
  "ext/linmath.h"
  ${GLFW_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIR}
  ${GLM_INCLUDE_DIR}
  )
  
target_link_libraries(test_window
  frank
  ${OpenGL_LIBRARIES}
  ${OPENGL_gl_LIBRARY}
  ${OPENGL_glu_LIBRARY}
  ${GLEW_LIBRARY}
)

target_compile_definitions(frank PUBLIC -DBUILD_FRANK)

add_definitions(-DGLEW_STATIC)

target_link_libraries(frank
  ${OpenGL_LIBRARIES}
  ${OPENGL_gl_LIBRARY}
  ${OPENGL_glu_LIBRARY}
  ${GLEW_LIBRARY}
  ${GLFW_LIBRARIES}
  )

target_include_directories(
  frank
  PUBLIC
  "include"
  "ext/linmath.h"
  ${GLFW_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIR}
  ${GLM_INCLUDE_DIR}
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
