import QtQuick

Rectangle {
    id: blackPieceRoot
    readonly property color selectedPieceOutlineColor: "white"
    readonly property color activePieceOutlineColor: Qt.rgba(255 / 255, 255 / 255, 0, 1) // 255, 255, 0

    width: uiScaler.px(50) // TODO Taken from GuiConfig::Piece::SIZE
    height: uiScaler.px(50) // TODO Taken from GuiConfig::Piece::SIZE

    color: Qt.rgba(50 / 255, 50 / 255, 50 / 255, 1)
    radius: 50 // TODO any number which makes it circle

    border.width: uiScaler.px(5) // outline width
    border.color: "black" // outline color
    // border.color: activePieceOutlineColor

    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("Black piece clicked")
            blackPieceRoot.border.color = blackPieceRoot.selectedPieceOutlineColor
        }
    }
}
