import QtQuick

Rectangle {
    id: borderRect
    anchors.centerIn: parent

    // outer size = board size and border on all sides
    width: checkerboardRoot.width + 2 * border.width
    height: checkerboardRoot.height + 2 * border.width

    color: "transparent"
    border.color: "black"
    border.width: 4 // this has to be even, otherwise there is sub-pixel positioning and rendering issues

    Rectangle {
        id: checkerboardRoot
        anchors.centerIn: parent
        width: 640 // 8 * 80 px per tile
        height: 640 // 8 * 80 px per tile

        color: "white"

        // Colors used in the checkerboard
        readonly property color playableTileColor: Qt.rgba(140 / 255, 90 / 255, 40 / 255, 1) // whitish
        readonly property color nonPlayableTileColor: Qt.rgba(230 / 255, 200 / 255, 160 / 255, 1) // brownish

        readonly property int gridRowCount: 8
        readonly property int gridColumnCount: 8

        property real tileSize: 80 // TODO scalable

        // Checkerboard tiles
        Repeater {
            model: checkerboardRoot.gridRowCount * checkerboardRoot.gridColumnCount // total number of squares in the grid

            delegate: Rectangle {
                width: checkerboardRoot.tileSize
                height: checkerboardRoot.tileSize

                // Compute the coordinates in the grid
                // gridX: column index (0 to gridColumnCount-1)
                // gridY: row index (0 to gridRowCount-1)
                property int gridX: index % checkerboardRoot.gridColumnCount
                property int gridY: Math.floor(index / checkerboardRoot.gridColumnCount)

                x: gridX * checkerboardRoot.tileSize
                y: gridY * checkerboardRoot.tileSize

                color: {
                    if (gridX % 2 === 0) {
                        return (gridY % 2 === 0) ? checkerboardRoot.nonPlayableTileColor : checkerboardRoot.playableTileColor;
                    } else {
                        return (gridY % 2 === 0) ? checkerboardRoot.playableTileColor : checkerboardRoot.nonPlayableTileColor;
                    }
                }
            }
        }
    }

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
