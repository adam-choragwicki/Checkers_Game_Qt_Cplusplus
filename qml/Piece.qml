import QtQuick
import PieceStateEnum

Rectangle {
    required property int xRole
    required property int yRole
    required property int playerRole
    required property int aliveRole
    required property int idRole
    required property int stateRole
    required property bool animationEnabledRole
    required property bool promotedRole

    // Config
    readonly property bool showId: true

    readonly property color northPlayerMainColor: Qt.rgba(220 / 255, 0, 0, 1) // red
    readonly property color northPlayerDisabledPieceOutlineColor: Qt.rgba(170 / 255, 0, 0, 1)

    readonly property color southPlayerMainColor: Qt.rgba(50 / 255, 50 / 255, 50 / 255, 1)
    readonly property color southPlayerDisabledPieceOutlineColor: "black"

    x: (xRole * checkerboard.tileSize) + uiScaler.px(15)
    y: (yRole * checkerboard.tileSize) + uiScaler.px(15)

    width: uiScaler.px(50)
    height: uiScaler.px(50)
    radius: 50 // circle

    readonly property bool isPlayerNorth: playerRole === 1
    readonly property string player: isPlayerNorth ? "NORTH" : "SOUTH"

    visible: aliveRole

    color: isPlayerNorth ? northPlayerMainColor : southPlayerMainColor

    //Outline (border)
    readonly property color activePieceOutlineColor: Qt.rgba(255 / 255, 255 / 255, 0, 1)
    readonly property color selectedPieceOutlineColor: "white"
    readonly property color disabledPieceOutlineColor: isPlayerNorth ? northPlayerDisabledPieceOutlineColor : southPlayerDisabledPieceOutlineColor
    border.width: uiScaler.px(5) // outline width

    border.color: {
        if (stateRole === PieceState.DISABLED) return disabledPieceOutlineColor;
        if (stateRole === PieceState.ACTIVE) return activePieceOutlineColor;
        if (stateRole === PieceState.SELECTED) return selectedPieceOutlineColor;

        console.error("QML: Unknown piece state: " + stateRole)
    }

    // Animation

    Behavior on x {
        enabled: animationEnabledRole

        NumberAnimation {
            duration: PieceMovementAnimationManager.pieceMovementAnimationDurationMs // exposed from C++
            easing.type: Easing.Linear
        }
    }

    Behavior on y {
        enabled: animationEnabledRole

        NumberAnimation {
            duration: PieceMovementAnimationManager.pieceMovementAnimationDurationMs  // exposed from C++
            easing.type: Easing.Linear
        }
    }

    onStateRoleChanged: {
        console.log("QML: Player " + player + " piece " + idRole + " piece state changed to " + stateRole)
    }

    MouseArea {
        enabled: Controller.gameRunning
        anchors.fill: parent
        onClicked: {
            Controller.onPieceClicked(idRole)
        }
    }

    Crown {
        anchors.centerIn: parent
        visible: promotedRole

        // opacity: promotedRole ? 1 : 0
        // scale: promotedRole ? 1 : 0.6

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
        visible: showId
        anchors.centerIn: parent
        text: idRole
        font.bold: true
        font.pixelSize: uiScaler.px(30)
        color: "white"
    }
}
