import QtQuick
import QtQuick.Controls // for tile tooltip

AbstractTile {
    color: Qt.rgba(140 / 255, 90 / 255, 40 / 255, 1) // whitish

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
}
