file(GLOB_RECURSE tests_SRC  
    "*.cpp"
)

add_library(Catch_interface INTERFACE)
target_include_directories(Catch_interface INTERFACE .)

add_executable(tests ${tests_SRC})
target_link_libraries(tests PUBLIC 
    Catch_interface 
    lemon
)
