set(MODULE_NAME CheckersQml)
set(LIB_NAME ${MODULE_NAME}Lib) # CheckersQmlLib

qt_add_library(${LIB_NAME} STATIC)

target_link_libraries(${LIB_NAME} PRIVATE Qt6::Quick)

qt_add_qml_module(${LIB_NAME}
        URI ${MODULE_NAME}
        VERSION 1.0
        OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CheckersQml
        QML_FILES
        Main.qml
        GameArea.qml
        Checkerboard.qml
        GameInput.qml
        UiScaler.qml

        Piece.qml
        Crown.qml

        overlays/EndGameOverlay.qml
        overlays/EscapeMenuOverlay.qml
)
