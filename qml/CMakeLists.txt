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
        Checkerboard.qml
        GameArea.qml
        GameInput.qml
        UiScaler.qml

        AbstractPiece.qml
#        BlackPiece.qml
#        RedPiece.qml
        Crown.qml

        AbstractTile.qml
        PlayableTile.qml
        NonPlayableTile.qml

#        Arena.qml

#        entities/Pacman.qml
#        entities/ghosts/AbstractGhost.qml
#        entities/ghosts/BlueGhost.qml
#        entities/ghosts/OrangeGhost.qml
#        entities/ghosts/PurpleGhost.qml
#        entities/ghosts/RedGhost.qml
#
#        pellets/StandardPellet.qml
#        pellets/PowerPellet.qml
#
        overlays/EndGameOverlay.qml
        overlays/EscapeMenuOverlay.qml
)
