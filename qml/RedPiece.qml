import QtQuick

AbstractPiece {
    id: redPieceRoot

    color: Qt.rgba(220 / 255, 0, 0, 1)

    readonly property color disabledPieceOutlineColor: Qt.rgba(170 / 255, 0, 0, 1) // reddish

    MouseArea {
        anchors.fill: parent
        onClicked: {
            piecesModel.pieceClicked(number)

            console.log("QML: Red piece " + number + " piece state is " + pieceState)
        }
    }

    onPieceStateChanged: {
        console.log("QML: Red piece " + number + " piece state changed to " + pieceState)

        if (pieceState === 1) {
            redPieceRoot.border.color = disabledPieceOutlineColor
        } else if (pieceState === 2) {
            redPieceRoot.border.color = activePieceOutlineColor
        } else if (pieceState === 3) {
            redPieceRoot.border.color = selectedPieceOutlineColor
        } else {
            console.error("QML: Invalid piece state " + pieceState + " of red piece")
        }
    }
}
