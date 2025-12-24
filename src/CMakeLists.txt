set(SOURCE_FILES
        main.cpp
        game.cpp game.h
        controller.cpp controller.h
        log_manager.cpp log_manager.h)

set(BACKEND_SOURCE_FILES
        model.cpp model.h
        common.h
        piece.h piece.cpp
        selected_piece_manager.h
        multi_capture_manager.h
        coordinates.h coordinates.cpp
        player_manager.h
        piece_capture_manager.h piece_capture_manager.cpp
        piece_movement_manager.h piece_movement_manager.cpp
        piece_promotion_manager.h piece_promotion_manager.cpp
        coordinates_database.h coordinates_database.cpp
        pieces_placement.h pieces_placement.cpp
        piece_state_manager.h piece_state_manager.cpp
        game_config.cpp game_config.h
        piece_model.cpp piece_model.h
        pieces_model.cpp pieces_model.h
        pieces_manager.cpp pieces_manager.h)

add_library(lib${PROJECT_NAME}Backend ${BACKEND_SOURCE_FILES})
target_include_directories(lib${PROJECT_NAME}Backend PUBLIC .)
target_link_libraries(lib${PROJECT_NAME}Backend PUBLIC Qt6::Core Qt6::Quick)


set(UI_FORMS_DIR ../ui_forms)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${UI_FORMS_DIR})

set(FRONTEND_SOURCE_FILES
        main_window.cpp main_window.h ${UI_FORMS_DIR}/main_window.ui
        checkerboard.cpp checkerboard.h
        drawer.cpp drawer.h
        tile.cpp tile.h
        piece_frontend.cpp piece_frontend.h
        crown.cpp crown.h
        gui_config.h)

add_library(lib${PROJECT_NAME}Frontend ${FRONTEND_SOURCE_FILES})
target_include_directories(lib${PROJECT_NAME}Frontend PUBLIC ${BACKEND_DIR})
target_link_libraries(lib${PROJECT_NAME}Frontend PUBLIC Qt6::Widgets Qt6::Quick)


# Create the main executable
qt_add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILES})

if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE $<CONFIG:Release>) # this avoids opening console window on Windows in Release mode
endif ()

target_include_directories(${PROJECT_NAME} PRIVATE ${BACKEND_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE lib${PROJECT_NAME}Backend lib${PROJECT_NAME}Frontend CheckersQmlLibplugin)
