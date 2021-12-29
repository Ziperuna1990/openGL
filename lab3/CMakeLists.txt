cmake_minimum_required(VERSION 3.20)
project(cg_university_task3)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(
        ${OPENGL_INCLUDE_DIRS}
        ${GLUT_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
)


add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} OpenGL::OpenGL ${GLUT_LIBRARY} glfw GLU GL glut)


