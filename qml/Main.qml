import QtQuick

Window {
    id: mainWindow
    minimumWidth: 800 // TODO remove, taken from main_window.cpp
    minimumHeight: 800 // TODO remove, taken from main_window.cpp
    visible: true

    // Component.onCompleted: {
    //     if (Controller.startInFullScreenEnabled) {
    //         console.log("Starting in fullscreen")
    //         mainWindow.showFullScreen()
    //     } else {
    //         console.log("Starting in windowed mode")
    //         mainWindow.showNormal()
    //     }
    // }
    //
    property real aspectRatio: width / height

    onAspectRatioChanged: {
        // console.log("Window size is now " + width + "x" + height)
        // console.log("Aspect ratio is now " + aspectRatio)
    }

    UiScaler {
        id: uiScaler
        target: gameArea   // this ensures UI scales with a visible gameplay area
    }

    /* Maintain the 800/800 aspect ratio with black bars */
    Rectangle {
        id: letterboxContainer
        anchors.fill: parent
        color: Qt.rgba(0, 160 / 255, 0, 1)

        /* This Item keeps the correct 800/800 scaling inside any window shape */
        Item {
            id: gameViewport
            anchors.centerIn: parent

            property real targetAspect: 800 / 800
            property real currentAspect: letterboxContainer.width / letterboxContainer.height

            /* Maintain the 800/800 aspect ratio and center it */
            width: currentAspect > targetAspect ? letterboxContainer.height * targetAspect : letterboxContainer.width
            height: currentAspect > targetAspect ? letterboxContainer.height : letterboxContainer.width / targetAspect

            GameArea {
                id: gameArea
                anchors.fill: parent
            }
        }
    }

    //
    // /* Overlays */
    // TextOverlay {
    //     visible: false
    // }
    //
    // EndGameOverlay {
    //     visible: false
    //     objectName: "endGameOverlay"
    //     anchors.fill: parent
    //     onPlayAgainClicked: Controller.onPlayAgainClicked()
    //     onQuitClicked: Controller.onQuitClicked()
    // }
    //
    // EscapeMenuOverlay {
    //     visible: false
    //     objectName: "escapeMenuOverlay"
    //     anchors.fill: parent
    //
    //     onResumeClicked: Controller.onResumeClicked()
    //     onRestartClicked: Controller.onRestartClicked()
    //     onQuitClicked: Controller.onQuitClicked()
    // }
}
