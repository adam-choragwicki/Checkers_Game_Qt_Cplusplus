import QtQuick

AbstractPiece {
    id: redPieceRoot

    color: Qt.rgba(220 / 255, 0, 0, 1)
    border.color: Qt.rgba(170 / 255, 0, 0, 1) // outline color

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("Red piece clicked")
            redPieceRoot.border.color = selectedPieceOutlineColor
        }
    }

    onStateChanged: {
        console.log("Red piece " + number + " state changed to " + state)

        if(state === 1)
        {
            redPieceRoot.border.color = "transparent" // no outline
        }
        else if(state === 2)
        {
            redPieceRoot.border.color = activePieceOutlineColor
        }
        else if(state === 3)
        {
            redPieceRoot.border.color = selectedPieceOutlineColor
        }
        else
        {
            console.error("Invalid state " + state + " of red piece")
        }
    }
}
