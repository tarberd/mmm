cmake_minimum_required(VERSION 3.2.2)

set(PROJECT_NAME "mmm")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

execute_process(
    COMMAND git submodule update --init --recursive
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    RESULT_VARIABLE submodule_init_exit_code
)

set(OPHIDIAN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/ophidian)
set(OPHIDIAN_BINARY_DIR ${PROJECT_BINARY_DIR}/ophidian)
set(OPHIDIAN_INCLUDE_DIRECTORIES 
    ${OPHIDIAN_SOURCE_DIR}
    ${OPHIDIAN_SOURCE_DIR}/3rdparty
    ${OPHIDIAN_BINARY_DIR}/3rdparty/Lemon/
    ${OPHIDIAN_SOURCE_DIR}/3rdparty/Lemon/
    ${OPHIDIAN_BINARY_DIR}/3rdparty/Lemon/lemon
)
add_subdirectory(ophidian/3rdparty/Lemon)

include_directories(${OPHIDIAN_INCLUDE_DIRECTORIES})
include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
