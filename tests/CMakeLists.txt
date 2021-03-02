set(TEST_SOURCES
        src/main.cpp
        src/common_test_fixture.h
        src/coordinates_generation_test.cpp
        src/piece_promotion_test.cpp
        src/piece_movement_test.cpp
        src/promoted_piece_movement_test.cpp
        src/piece_capture_test.cpp
        src/promoted_piece_capture_test.cpp)

add_subdirectory(googletest)

add_executable(${PROJECT_NAME}Test_run ${TEST_SOURCES})
target_include_directories(${PROJECT_NAME}Test_run PRIVATE src)
target_link_libraries(${PROJECT_NAME}Test_run PRIVATE gtest lib${PROJECT_NAME}Backend)
