cmake_minimum_required (VERSION 2.6)
project (Game-Of-Life)

add_executable (game-of-life main.cpp game.cpp view.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

find_path(OpenGLIncludeSubdir
            NAMES gl.h
            PATHS ${OPENGL_INCLUDE_DIR}
            PATH_SUFFIXES GL OpenGL Headers
            NO_DEFAULT_PATH)
include_directories(${OpenGLIncludeSubdir})
find_path(GLUTIncludeSubdir
            NAMES glut.h
            PATHS ${GLUT_INCLUDE_DIR}
            PATH_SUFFIXES GL OpenGL Headers
            NO_DEFAULT_PATH)
include_directories(${GLUTIncludeSubdir})


target_link_libraries(game-of-life ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
