set(SOURCE_FILES
        game.cpp game.h
        controller.cpp controller.h
        log_manager.cpp log_manager.h)

set(BACKEND_SOURCE_FILES
        model.cpp model.h
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
        pieces_manager.cpp pieces_manager.h

        qml_helper.h
        overlay_manager.h overlay_manager.cpp

        state_machine/abstract_state.h
        state_machine/game_state_manager.h
        state_machine/game_state_type.h
        state_machine/i_state_actions.h
        state_machine/states/ended_victory_player_upper.h
        state_machine/states/ended_victory_player_lower.h
        state_machine/states/escape_menu_state.h
        state_machine/states/initialization_state.h
        state_machine/states/paused_for_debug_state.h
        state_machine/states/ready_to_start_state.h
        state_machine/states/running_state.h

        game_coordinator.cpp game_coordinator.h

        input_handler.cpp input_handler.h
        window_manager.cpp window_manager.h

        game_result.h
        resolution.h)

add_library(lib${PROJECT_NAME}Backend ${BACKEND_SOURCE_FILES})
target_include_directories(lib${PROJECT_NAME}Backend PUBLIC .)
target_link_libraries(lib${PROJECT_NAME}Backend PUBLIC Qt6::Core Qt6::Quick)

# Create the main executable
qt_add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILES})

if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE $<CONFIG:Release>) # this avoids opening console window on Windows in Release mode
endif ()

target_include_directories(${PROJECT_NAME} PRIVATE ${BACKEND_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE lib${PROJECT_NAME}Backend CheckersQmlLibplugin)
