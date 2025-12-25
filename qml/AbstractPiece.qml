import QtQuick

Rectangle {
    id: abstractPiece

    required property int number
    required property int state

    readonly property color activePieceOutlineColor: Qt.rgba(255 / 255, 255 / 255, 0, 1) // 255, 255, 0
    readonly property color selectedPieceOutlineColor: "white"

    width: uiScaler.px(50) // TODO Taken from GuiConfig::Piece::SIZE
    height: uiScaler.px(50) // TODO Taken from GuiConfig::Piece::SIZE

    radius: 50 // circle

    border.width: uiScaler.px(5) // outline width

    Text {
        anchors.centerIn: parent
        text: number
        font.bold: true
        font.pixelSize: uiScaler.px(30)
        color: "white"
    }
}
