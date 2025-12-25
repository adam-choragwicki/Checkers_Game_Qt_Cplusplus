import QtQuick

AbstractPiece {
    id: blackPieceRoot

    color: Qt.rgba(50 / 255, 50 / 255, 50 / 255, 1)

    readonly property color disabledPieceOutlineColor: "black"

    MouseArea {
        anchors.fill: parent
        onClicked: {
            piecesModel.pieceClicked(number)
        }
    }

    onPieceStateChanged: {
        console.log("QML: Black piece " + number + " piece state changed to " + pieceState)

        if (pieceState === 1) {
            blackPieceRoot.border.color = disabledPieceOutlineColor
        } else if (pieceState === 2) {
            blackPieceRoot.border.color = activePieceOutlineColor
        } else if (pieceState === 3) {
            blackPieceRoot.border.color = selectedPieceOutlineColor
        } else {
            console.error("QML: Invalid piece state " + pieceState + " of black piece")
        }
    }
}
