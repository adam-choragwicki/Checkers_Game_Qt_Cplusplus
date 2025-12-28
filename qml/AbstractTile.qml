import QtQuick
import QtQuick.Controls // for tile tooltip

Rectangle {
    HoverHandler {
        id: hover
    }

    ToolTip.visible: hover.hovered
    ToolTip.text: (gridY + 1) + "," + (gridX + 1)
    ToolTip.delay: 200

    TapHandler {
        onTapped: {
            console.log("QML: Tile clicked at (" + (gridY + 1) + "," + (gridY + 1) + ")")
            Controller.onTileClicked(gridY + 1, gridX + 1)
        }
    }
}
