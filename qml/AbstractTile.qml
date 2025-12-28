import QtQuick
import QtQuick.Controls // for tile tooltip

Rectangle {
    HoverHandler {
        id: hover
        enabled: Controller.gameRunning
    }

    ToolTip {
        visible: hover.enabled && hover.hovered
        delay: 200
        text: (gridY + 1) + "," + (gridX + 1)

        // position relative to the tile
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
