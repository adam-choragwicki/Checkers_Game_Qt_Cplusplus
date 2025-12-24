import QtQuick

Rectangle {
    width: uiScaler.px(50) // TODO Taken from GuiConfig::Piece::SIZE
    height: uiScaler.px(50) // TODO Taken from GuiConfig::Piece::SIZE

    color: Qt.rgba(220 / 255, 0, 0, 1)
    radius: 50 // TODO any number which makes it circle

    border.width: uiScaler.px(5) // outline width
    border.color: Qt.rgba(170 / 255, 0, 0, 1) // outline color
}
