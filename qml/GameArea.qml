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

        delegate: Piece {
        }
    }

    GameInput {
        id: gameInput
        objectName: "gameInput"
        anchors.fill: parent
    }
}
