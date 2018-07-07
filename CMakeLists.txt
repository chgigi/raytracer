cmake_minimum_required(VERSION 3.6)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -o3")

include_directories(src/parser lib/misc)

set(PARSER_DIR src/parser/)
set(SRC_DIR src/)
set(MISC_DIR lib/misc/)

set(LIB_MISC
    ${MISC_DIR}vector3.cc)

set(MAIN_SRC
    ${SRC_DIR}/main.cc)

add_library(lib STATIC ${LIB_MISC})

add_executable(raytracer ${MAIN_SRC})