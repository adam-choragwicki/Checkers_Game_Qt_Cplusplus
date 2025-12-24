import QtQuick

Rectangle {
    readonly property color selectedPieceOutlineColor: "white"
    readonly property color activePieceOutlineColor: Qt.rgba(255 / 255, 255 / 255, 0, 1) // 255, 255, 0

    width: uiScaler.px(50) // TODO Taken from GuiConfig::Piece::SIZE
    height: uiScaler.px(50) // TODO Taken from GuiConfig::Piece::SIZE

    radius: 50 // circle

    border.width: uiScaler.px(5) // outline width
}
