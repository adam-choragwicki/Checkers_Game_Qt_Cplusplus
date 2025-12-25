import QtQuick

AbstractPiece {
    id: blackPieceRoot

    color: Qt.rgba(50 / 255, 50 / 255, 50 / 255, 1)
    border.color: "black" // outline color

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("Black piece clicked")
            blackPieceRoot.border.color = selectedPieceOutlineColor
        }
    }

    onStateChanged: {
        console.log("Black piece " + number + " state changed to " + state)

        if(state === 1)
        {
            blackPieceRoot.border.color = "transparent" // no outline
        }
        else if(state === 2)
        {
            blackPieceRoot.border.color = activePieceOutlineColor
        }
        else if(state === 3)
        {
            blackPieceRoot.border.color = selectedPieceOutlineColor
        }
        else
        {
            console.error("Invalid state " + state + " of black piece")
        }
    }
}
