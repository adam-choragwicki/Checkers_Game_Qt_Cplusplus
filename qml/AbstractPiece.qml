import QtQuick

Rectangle {
    id: abstractPiece

    property int idNumber
    property int pieceState
    property bool isPromoted
    property string player
    property color disabledPieceOutlineColor

    readonly property color activePieceOutlineColor: Qt.rgba(255 / 255, 255 / 255, 0, 1) // 255, 255, 0
    readonly property color selectedPieceOutlineColor: "white"

    width: uiScaler.px(50) // TODO Taken from GuiConfig::Piece::SIZE
    height: uiScaler.px(50) // TODO Taken from GuiConfig::Piece::SIZE

    radius: 50 // circle

    border.width: uiScaler.px(5) // outline width

    onPieceStateChanged: {
        console.log("QML: Player " + player + " piece " + idNumber + " piece state changed to " + pieceState)

        if (pieceState === 1) {
            border.color = disabledPieceOutlineColor
        } else if (pieceState === 2) {
            border.color = activePieceOutlineColor
        } else if (pieceState === 3) {
            border.color = selectedPieceOutlineColor
        } else {
            console.error("QML: Invalid piece state " + pieceState + " of player " + player + " piece")
        }
    }

    MouseArea {
        enabled: Controller.gameRunning
        anchors.fill: parent
        onClicked: {
            Controller.onPieceClicked(idNumber)
        }
    }

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
        text: idNumber
        font.bold: true
        font.pixelSize: uiScaler.px(30)
        color: "white"
    }
}
