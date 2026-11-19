add_library(lab4_lib
    src/shape.cpp
    src/circle.cpp
    src/ellipse.cpp
    src/sector.cpp
    src/shape_collection.cpp
)

target_include_directories(lab4_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(lab4_lib PUBLIC cxx_std_20)
target_compile_options(lab4_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(lab4_main main.cpp)
target_link_libraries(lab4_main PRIVATE lab4_lib)
target_compile_options(lab4_main PRIVATE -Wall -Wextra -Wpedantic)

if(NOT TARGET GTest::gtest_main)
    find_package(GTest QUIET)
endif()

if(NOT TARGET GTest::gtest_main)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
    )
    FetchContent_MakeAvailable(googletest)
endif()

add_executable(lab4_tests tests/test_lab4.cpp)
target_link_libraries(lab4_tests PRIVATE lab4_lib GTest::gtest_main)
target_compile_options(lab4_tests PRIVATE -Wall -Wextra -Wpedantic)

if(APPLE AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_options(lab4_tests PRIVATE -fsanitize=address)
endif()

include(GoogleTest)
gtest_discover_tests(lab4_tests)
