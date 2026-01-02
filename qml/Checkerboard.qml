import QtQuick
import QtQuick.Controls // for tile tooltip

Item {
    width: borderRect.width
    height: borderRect.height

    property alias tileSize: checkerboard.tileSize

    Rectangle {
        id: borderRect
        anchors.centerIn: parent

        // outer size = board size and border on all sides
        width: checkerboard.width + 2 * border.width
        height: checkerboard.height + 2 * border.width

        color: "transparent"
        border.color: "black"
        border.width: 4 // this has to be even, otherwise there is sub-pixel positioning and rendering issues

        Rectangle {
            id: checkerboard
            anchors.centerIn: parent
            width: 8 * tileSize
            height: 8 * tileSize

            color: "white"

            readonly property int gridRowCount: 8
            readonly property int gridColumnCount: 8

            property real tileSize: uiScaler.px(80)

            // Checkerboard tiles
            Repeater {
                model: checkerboard.gridRowCount * checkerboard.gridColumnCount // total number of squares in the grid

                delegate: Item {
                    x: gridX * checkerboard.tileSize
                    y: gridY * checkerboard.tileSize
                    width: checkerboard.tileSize
                    height: checkerboard.tileSize

                    // Compute the coordinates in the grid
                    // gridX: column index (0 to gridColumnCount-1)
                    // gridY: row index (0 to gridRowCount-1)
                    property int gridX: index % checkerboard.gridColumnCount
                    property int gridY: Math.floor(index / checkerboard.gridColumnCount)

                    readonly property bool isPlayable: (gridX + gridY) % 2 === 1

                    readonly property color playableTileColor: Qt.rgba(140 / 255, 90 / 255, 40 / 255, 1) // brownish
                    readonly property color nonPlayableTileColor: Qt.rgba(230 / 255, 200 / 255, 160 / 255, 1) // ecru like

                    // Base tile (always exists)
                    Rectangle {
                        anchors.fill: parent
                        color: isPlayable ? playableTileColor : nonPlayableTileColor
                    }

                    // Interaction layer – only created for playable tiles
                    Item {
                        anchors.fill: parent
                        visible: isPlayable

                        HoverHandler {
                            id: hover
                            enabled: Controller.gameRunning
                        }

                        ToolTip {
                            visible: hover.enabled && hover.hovered
                            delay: 200
                            text: (gridY + 1) + "," + (gridX + 1)
                            x: hover.point.position.x + 12
                            y: hover.point.position.y + 12
                        }

                        TapHandler {
                            enabled: Controller.gameRunning

                            onTapped: {
                                console.log("QML: Tile clicked at (" + (gridY + 1) + "," + (gridX + 1) + ")")
                                Controller.onTileClicked(gridY + 1, gridX + 1)
                            }
                        }
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
