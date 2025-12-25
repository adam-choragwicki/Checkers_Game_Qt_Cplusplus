import QtQuick

Item {
    id: gameArea

    onWidthChanged: {
        // console.log("Game area width changed to " + width)
    }

    onHeightChanged: {
        // console.log("Game area height changed to " + height)
    }

    Checkerboard {
        id: checkerboard
        anchors.centerIn: parent
    }

    /* Pieces */
    Repeater {
        model: piecesModel

        delegate: Loader {
            x: (xRole * checkerboard.tileSize) + uiScaler.px(15) // TODO Taken from GuiConfig::Tile::SIZE plus GuiConfig::Piece::OFFSET_X
            y: (yRole * checkerboard.tileSize) + uiScaler.px(15) // TODO Taken from GuiConfig::Tile::SIZE plus GuiConfig::Piece::OFFSET_X
            visible: aliveRole
            sourceComponent: playerRole === 1 ? redPieceComponent : blackPieceComponent

            onLoaded: {
                item.number = idRole
                item.pieceState = stateRole
            }
        }
    }

    Component {
        id: redPieceComponent
        RedPiece {
            number: idRole
            pieceState: stateRole
        }
    }

    Component {
        id: blackPieceComponent
        BlackPiece {
            number: idRole
            pieceState: stateRole
        }
    }

    // //
    // // INPUT HANDLER
    // //
    // GameInput {
    //     id: gameInput
    //     objectName: "gameInput"
    //     anchors.fill: parent
    // }
}
