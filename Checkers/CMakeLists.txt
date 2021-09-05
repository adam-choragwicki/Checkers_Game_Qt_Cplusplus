cmake_minimum_required(VERSION 3.5)

project(Checkers LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        common.h
        game_window.cpp
        game_window.h
        game_window.ui
        piece.cpp
        piece.h
        logic.cpp
        logic.h
        checkerboard.cpp
        checkerboard.h
        tile.cpp
        tile.h
        coordinates.cpp
        coordinates.h
        game_engine.cpp
        game_engine.h
        drawer.cpp
        drawer.h
        player_manager.cpp
        player_manager.h
        active_piece_manager.cpp
        active_piece_manager.h
        log_manager.cpp
        log_manager.h
)

qt_add_executable(Checkers WIN32 ${PROJECT_SOURCES})

target_link_libraries(Checkers PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/executable)
