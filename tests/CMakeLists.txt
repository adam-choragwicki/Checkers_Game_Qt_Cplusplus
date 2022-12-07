cmake_minimum_required(VERSION 3.10)

project(CheckersTest LANGUAGES CXX)

set(TEST_SOURCES
    src/main.cpp
    inc/common_test_fixture.h src/common_test_fixture.cpp
    src/object_generation_test.cpp
    src/promotion_test.cpp
    src/movement_test.cpp
    src/promoted_movement_test.cpp
    src/capture_test.cpp
    src/promoted_capture_test.cpp
)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(CheckersTest_run ${TEST_SOURCES})
target_include_directories(CheckersTest_run PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(CheckersTest_run gtest gtest_main libCheckers)
