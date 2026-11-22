add_library(lab5_lib
        src/product.cpp
        src/product_selector.cpp
        src/selection.cpp
        src/binary_search_tree.cpp
)

target_include_directories(lab5_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(lab5_lib PUBLIC cxx_std_20)

target_compile_options(lab5_lib PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -g
        -fsanitize=address
        -fno-omit-frame-pointer
)

add_executable(lab5_main main.cpp)
target_link_libraries(lab5_main PRIVATE lab5_lib)
target_compile_options(lab5_main PRIVATE -Wall -Wextra -Wpedantic -g -fsanitize=address -fno-omit-frame-pointer)
target_link_options(lab5_main PRIVATE -fsanitize=address)

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

add_executable(lab5_tests tests/test_lab5.cpp)
target_link_libraries(lab5_tests PRIVATE lab5_lib GTest::gtest_main)
target_compile_options(lab5_tests PRIVATE -Wall -Wextra -Wpedantic -g -fsanitize=address -fno-omit-frame-pointer)
target_link_options(lab5_tests PRIVATE -fsanitize=address)

add_test(NAME Lab5Tests COMMAND lab5_tests)
