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
            id: loader
            x: (xRole * checkerboard.tileSize) + uiScaler.px(15) // TODO Taken from GuiConfig::Tile::SIZE plus GuiConfig::Piece::OFFSET_X
            y: (yRole * checkerboard.tileSize) + uiScaler.px(15) // TODO Taken from GuiConfig::Tile::SIZE plus GuiConfig::Piece::OFFSET_X

            property bool pieceAnimationsEnabled: animationEnabledRole
            property int pieceMovementAnimationDurationMs: 100 // TODO ( take it from C++ context property)

            Behavior on x {
                enabled: loader.pieceAnimationsEnabled

                NumberAnimation {
                    duration: pieceMovementAnimationDurationMs
                    easing.type: Easing.Linear
                }
            }
            Behavior on y {
                enabled: loader.pieceAnimationsEnabled

                NumberAnimation {
                    duration: pieceMovementAnimationDurationMs
                    easing.type: Easing.Linear
                }
            }

            visible: aliveRole
            sourceComponent: playerRole === 1 ? redPieceComponent : blackPieceComponent

            onLoaded: {
                console.log("QML: Loader loaded piece " + idRole)
            }

            Binding {
                target: loader.item
                property: "number"
                value: idRole
            }

            Binding {
                target: loader.item
                property: "pieceState"
                value: stateRole
            }
        }
    }

    Component {
        id: redPieceComponent
        RedPiece {
        }
    }

    Component {
        id: blackPieceComponent
        BlackPiece {
        }
    }

    GameInput {
        id: gameInput
        objectName: "gameInput"
        anchors.fill: parent
    }
}
