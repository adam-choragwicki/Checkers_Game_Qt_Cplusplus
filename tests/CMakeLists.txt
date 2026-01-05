cmake_minimum_required(VERSION 3.16)

set(GOOGLETEST_VERSION 1.17.0)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(googletest)

set(TEST_SOURCES
        src/common_test_fixture.h
        src/coordinates_generation_test.cpp
        src/piece_promotion_test.cpp
        src/piece_movement_test.cpp
        src/promoted_piece_movement_test.cpp
        src/piece_capture_test.cpp
        src/promoted_piece_capture_test.cpp)

# Create the test executable
add_executable(${PROJECT_NAME}Test_run src/main.cpp ${TEST_SOURCES})

target_include_directories(${PROJECT_NAME}Test_run PRIVATE src)
target_link_libraries(${PROJECT_NAME}Test_run PRIVATE gtest lib${PROJECT_NAME}Core)

# Enable CTest
enable_testing()
add_test(NAME AllTests COMMAND runTests)
