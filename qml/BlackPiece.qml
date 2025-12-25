import QtQuick

AbstractPiece {
    id: blackPieceRoot

    color: Qt.rgba(50 / 255, 50 / 255, 50 / 255, 1)
    border.color: "black" // outline color

    MouseArea {
        anchors.fill: parent
        onClicked: {
            piecesModel.pieceClicked(number)

            console.log("QML: Black piece " + number + " piece state is " + pieceState)
        }
    }

    onPieceStateChanged: {
        console.log("QML: Black piece " + number + " piece state changed to " + pieceState)

        if (pieceState === 1) {
            blackPieceRoot.border.color = "transparent" // no outline
        } else if (pieceState === 2) {
            blackPieceRoot.border.color = activePieceOutlineColor
        } else if (pieceState === 3) {
            blackPieceRoot.border.color = selectedPieceOutlineColor
        } else {
            console.error("QML: Invalid piece state " + pieceState + " of black piece")
        }
    }
}
