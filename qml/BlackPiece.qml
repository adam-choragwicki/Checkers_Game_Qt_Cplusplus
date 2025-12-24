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
}
