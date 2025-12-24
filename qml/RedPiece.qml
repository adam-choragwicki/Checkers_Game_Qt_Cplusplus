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
}
