cmake_minimum_required(VERSION 3.10)

project(Checkers LANGUAGES CXX)

set(QT_VERSION_MAJOR 6)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(PROJECT_ROOT ${CMAKE_SOURCE_DIR})

set(INCLUDES_DIR ${PROJECT_ROOT}/inc)
set(SOURCES_DIR ${PROJECT_ROOT}/src)
set(UI_FORMS_DIR ${PROJECT_ROOT}/ui_forms)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${UI_FORMS_DIR})

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(SOURCE_FILES
    ${SOURCES_DIR}/main.cpp
    ${INCLUDES_DIR}/common.h
    ${INCLUDES_DIR}/game_window.h ${SOURCES_DIR}/game_window.cpp ${UI_FORMS_DIR}/game_window.ui
    ${INCLUDES_DIR}/game_engine.h ${SOURCES_DIR}/game_engine.cpp
    ${INCLUDES_DIR}/selected_piece_manager.h
    ${INCLUDES_DIR}/multi_capture_manager.h
    ${INCLUDES_DIR}/checkerboard.h ${SOURCES_DIR}/checkerboard.cpp
    ${INCLUDES_DIR}/coordinates.h ${SOURCES_DIR}/coordinates.cpp
    ${INCLUDES_DIR}/piece.h ${SOURCES_DIR}/piece.cpp
    ${INCLUDES_DIR}/tile.h ${SOURCES_DIR}/tile.cpp
    ${INCLUDES_DIR}/player_manager.h
    ${INCLUDES_DIR}/log_manager.h
    ${INCLUDES_DIR}/piece_capture_manager.h ${SOURCES_DIR}/piece_capture_manager.cpp
    ${INCLUDES_DIR}/piece_movement_manager.h ${SOURCES_DIR}/piece_movement_manager.cpp
    ${INCLUDES_DIR}/piece_promotion_manager.h ${SOURCES_DIR}/piece_promotion_manager.cpp
    ${INCLUDES_DIR}/starting_coordinates_generator.h ${SOURCES_DIR}/starting_coordinates_generator.cpp
    ${INCLUDES_DIR}/tile_manager.h ${SOURCES_DIR}/tile_manager.cpp
    ${INCLUDES_DIR}/pieces_placement.h ${SOURCES_DIR}/pieces_placement.cpp
    ${INCLUDES_DIR}/drawer.h ${SOURCES_DIR}/drawer.cpp)

add_library(libCheckers ${SOURCE_FILES})
target_include_directories(libCheckers PUBLIC ${INCLUDES_DIR})
target_link_libraries(libCheckers Qt${QT_VERSION_MAJOR}::Widgets)

add_executable(Checkers WIN32 ${SOURCES_DIR}/main.cpp)
target_link_libraries(Checkers libCheckers)

if(WIN32)
    set_target_properties(Checkers PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/executable_windows)
elseif(UNIX)
    set_target_properties(Checkers PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/executable_linux)
endif(WIN32)

add_subdirectory(tests)
