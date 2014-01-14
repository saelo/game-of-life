cmake_minimum_required (VERSION 2.6)
project (Game-Of-Life)

add_executable (game-of-life main.cpp gofl.cpp view.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(game-of-life ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
