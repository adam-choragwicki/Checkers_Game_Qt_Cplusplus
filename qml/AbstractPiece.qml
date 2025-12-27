import QtQuick

Rectangle {
    id: abstractPiece

    property int number: -1     // TODO default value, should be set by concrete piece
    property int pieceState: -1 // TODO default value, should be set by concrete piece
    property bool isPromoted: false

    readonly property color activePieceOutlineColor: Qt.rgba(255 / 255, 255 / 255, 0, 1) // 255, 255, 0
    readonly property color selectedPieceOutlineColor: "white"

    width: uiScaler.px(50) // TODO Taken from GuiConfig::Piece::SIZE
    height: uiScaler.px(50) // TODO Taken from GuiConfig::Piece::SIZE

    radius: 50 // circle

    border.width: uiScaler.px(5) // outline width

    Crown {
        anchors.centerIn: parent
        visible: isPromoted

        // opacity: isPromoted ? 1 : 0
        // scale: isPromoted ? 1 : 0.6

        // Behavior on opacity { // TODO optional animation
        //     NumberAnimation {
        //         duration: 1500
        //     }
        // }
        // Behavior on scale {
        //     NumberAnimation {
        //         duration: 1500
        //     }
        // }
    }

    Text {
        anchors.centerIn: parent
        text: number
        font.bold: true
        font.pixelSize: uiScaler.px(30)
        color: "white"
    }
}
