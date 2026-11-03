cmake_minimum_required(VERSION 3.20)
project(lab3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "Use GNU GCC: configure with -DCMAKE_CXX_COMPILER=g++-16")
endif()

add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -g
        -fsanitize=address
        -fno-omit-frame-pointer
)

add_link_options(-fsanitize=address)

if(NOT TARGET GTest::gtest_main)
    find_package(GTest QUIET)
endif()

if(NOT TARGET GTest::gtest_main)
    include(FetchContent)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.15.2
    )

    FetchContent_MakeAvailable(googletest)
endif()

add_library(lab3_lib
        src/student.cpp
        src/student_set.cpp
)

target_include_directories(lab3_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(lab3_main src/main.cpp)

target_link_libraries(lab3_main PRIVATE lab3_lib)

add_executable(lab3_tests
        tests/test_student.cpp
        tests/test_student_set.cpp
)

target_link_libraries(lab3_tests PRIVATE
        lab3_lib
        GTest::gtest_main
)

add_test(NAME Lab3Tests COMMAND lab3_tests)