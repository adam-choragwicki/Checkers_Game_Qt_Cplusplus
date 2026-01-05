import QtQuick

Item {
    id: gameArea

    Checkerboard {
        id: checkerboard
        anchors.centerIn: parent
    }

    /* Pieces */
    Repeater {
        model: piecesModel

        delegate: Piece {
        }
    }

    GameInput {
        id: gameInput
        objectName: "gameInput"
        anchors.fill: parent
    }
}
