file(GLOB_RECURSE tests_SRC  
    "*.cpp"
)

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE .)

add_executable(run_tests ${tests_SRC})
target_link_libraries(run_tests PUBLIC 
    Catch 
)
