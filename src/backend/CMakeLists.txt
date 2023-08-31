set(SOURCE_FILES
        model/model.cpp model/model.h
        common.h
        piece.h piece.cpp
        selected_piece_manager.h
        multi_capture_manager.h
        coordinates.h coordinates.cpp
        player_manager.h
        log_manager.h
        piece_capture_manager.h piece_capture_manager.cpp
        piece_movement_manager.h piece_movement_manager.cpp
        piece_promotion_manager.h piece_promotion_manager.cpp
        coordinates_database.h coordinates_database.cpp
        pieces_placement.h pieces_placement.cpp
        piece_state_manager.h piece_state_manager.cpp)

add_library(lib${PROJECT_NAME}Backend ${SOURCE_FILES})
target_include_directories(lib${PROJECT_NAME}Backend PUBLIC .)
target_link_libraries(lib${PROJECT_NAME}Backend PUBLIC Qt${QT_VERSION_MAJOR}::Core)
