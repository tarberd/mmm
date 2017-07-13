cmake_minimum_required(VERSION 3.2.2)

set(PROJECT_NAME "OPHIDIAN_PROJECT_TEMPLATE")
project(${PROJECT_NAME})

set(OPHIDIAN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/ophidian)
set(OPHIDIAN_BINARY_DIR ${PROJECT_BINARY_DIR}/ophidian)
set(OPHIDIAN_INCLUDE_DIRECTORIES 
    ${OPHIDIAN_SOURCE_DIR}
    ${OPHIDIAN_SOURCE_DIR}/3rdparty
    ${OPHIDIAN_BINARY_DIR}/3rdparty/Lemon/
    ${OPHIDIAN_SOURCE_DIR}/3rdparty/Lemon/
    ${OPHIDIAN_BINARY_DIR}/3rdparty/Lemon/lemon
)
add_subdirectory(ophidian)
