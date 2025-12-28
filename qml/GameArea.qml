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

        delegate: AbstractPiece {
            id: piece

            idNumber: idRole
            pieceState: stateRole
            isPromoted: promotedRole

            readonly property bool isPlayerOne: playerRole === 1

            player: isPlayerOne ? "SOUTH" : "NORTH"

            color: isPlayerOne ? Qt.rgba(50 / 255, 50 / 255, 50 / 255, 1) : Qt.rgba(220 / 255, 0, 0, 1)

            disabledPieceOutlineColor: isPlayerOne ? "black" : Qt.rgba(170 / 255, 0, 0, 1)

            x: (xRole * checkerboard.tileSize) + uiScaler.px(15) // TODO Taken from GuiConfig::Tile::SIZE plus GuiConfig::Piece::OFFSET_X
            y: (yRole * checkerboard.tileSize) + uiScaler.px(15) // TODO Taken from GuiConfig::Tile::SIZE plus GuiConfig::Piece::OFFSET_Y

            property bool pieceAnimationsEnabled: animationEnabledRole
            property int pieceMovementAnimationDurationMs: 100 // TODO ( take it from C++ context property)

            Behavior on x {
                enabled: piece.pieceAnimationsEnabled

                NumberAnimation {
                    duration: piece.pieceMovementAnimationDurationMs
                    easing.type: Easing.Linear
                }
            }

            Behavior on y {
                enabled: piece.pieceAnimationsEnabled

                NumberAnimation {
                    duration: piece.pieceMovementAnimationDurationMs
                    easing.type: Easing.Linear
                }
            }

            visible: aliveRole
        }
    }

    GameInput {
        id: gameInput
        objectName: "gameInput"
        anchors.fill: parent
    }
}
