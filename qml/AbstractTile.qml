import QtQuick

Rectangle {
    TapHandler {
        enabled: Controller.gameRunning

        onTapped: {
            console.log("QML: Tile clicked at (" + (gridY + 1) + "," + (gridX + 1) + ")")
            Controller.onTileClicked(gridY + 1, gridX + 1)
        }
    }
}
