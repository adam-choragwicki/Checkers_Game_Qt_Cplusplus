import QtQuick

Rectangle {
    id: checkerboardRoot
    width: 640 // 8 * 80 px per tile
    height: 640 // 8 * 80 px per tile
    visible: true

    color: "white"

    anchors.centerIn: parent

    border.width: 5

    border.color: "black"

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
    // property real aspectRatio: width / height
    //
    // onAspectRatioChanged: {
    //     console.log("Window size is now " + width + "x" + height)
    //     console.log("Aspect ratio is now " + aspectRatio)
    // }
    //
    // UiScaler {
    //     id: uiScaler
    //     target: gameArea   // this ensures UI scales with a visible gameplay area
    // }
    //
    // /* Maintain the 614/740 aspect ratio with black bars */
    // Rectangle {
    //     id: letterboxContainer
    //     anchors.fill: parent
    //     color: "black"
    //
    //     /* This Item keeps the correct 614/740 scaling inside any window shape */
    //     Item {
    //         id: gameViewport
    //         anchors.centerIn: parent
    //
    //         property real targetAspect: 614/740
    //         property real currentAspect: letterboxContainer.width / letterboxContainer.height
    //
    //         /* Maintain the 614/740 aspect ratio and center it */
    //         width: currentAspect > targetAspect ? letterboxContainer.height * targetAspect : letterboxContainer.width
    //         height: currentAspect > targetAspect ? letterboxContainer.height : letterboxContainer.width / targetAspect
    //
    //         GameArea {
    //             id: gameArea
    //             anchors.fill: parent
    //         }
    //     }
    // }
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
