cmake_minimum_required(VERSION 3.26)
project(AC4176 C)

set(CMAKE_C_STANDARD 11)

set(MainFiles
        src/bignumber.c
        src/bignumber.h
        src/modnumber.c
        src/modnumber.h)

# Set up the main executable.
add_executable(AC4176 main.c ${MainFiles})

# Specify the path to the Unity source files
add_library(Unity STATIC
        Unity/src/unity.c
)

# Include the Unity headers
target_include_directories(Unity PUBLIC
        Unity/src
)

# Create a test executable
add_executable(AC4176_Test ${MainFiles}
        tests/bignumber_test.c
        tests/_test_util.h
        tests/_test_util.c
)

# Link Unity to the test executable
target_link_libraries(AC4176_Test PRIVATE Unity)
