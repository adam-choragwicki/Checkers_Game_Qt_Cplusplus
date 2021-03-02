set(UI_FORMS_DIR ui_forms)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${UI_FORMS_DIR})

set(SOURCE_FILES
        main_window.cpp main_window.h ${UI_FORMS_DIR}/main_window.ui
        checkerboard.cpp checkerboard.h
        drawer.cpp drawer.h
        tile.cpp tile.h
        piece_frontend.cpp piece_frontend.h
        crown.cpp crown.h
        gui_config.h)

add_library(lib${PROJECT_NAME}Frontend ${SOURCE_FILES})
target_include_directories(lib${PROJECT_NAME}Frontend PUBLIC ${BACKEND_DIR})
target_link_libraries(lib${PROJECT_NAME}Frontend PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
