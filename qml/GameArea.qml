import QtQuick

Item {
    id: gameArea

    onWidthChanged: {
        console.log("Game area width changed to " + width)
    }

    onHeightChanged: {
        console.log("Game area height changed to " + height)
    }

    Checkerboard {
        id: checkerboard
        anchors.centerIn: parent
    }

    /* Pieces */
    Repeater {
        model: piecesModel
        delegate: Rectangle {

            Component.onCompleted: {
                console.log(
                    "Delegate created:",
                    "index =", index,
                    "xRole =", model.xRole,
                    "yRole =", model.yRole,
                    "alive =", model.aliveRole
                )
            }

            x: (model.xRole * 80) + 15 // TODO Taken from GuiConfig::Tile::SIZE plus GuiConfig::Piece::OFFSET_X
            y: (model.yRole * 80) + 15 // TODO Taken from GuiConfig::Tile::SIZE plus GuiConfig::Piece::OFFSET_Y
            width: 50 // TODO Taken from GuiConfig::Piece::SIZE
            height: 50 // TODO Taken from GuiConfig::Piece::SIZE
            visible: model.aliveRole
            color: Qt.rgba(50 / 255, 50 / 255, 50 / 255, 1)

            radius: 50 // TODO any number which makes it circle

            border.width: 5 // outline width
            border.color: "black" // outline color
        }

        // delegate: Rectangle {
        //     x: ScalingUtilities.scaleX(model.x, Controller.gameArenaSize.width, gameArea.width)
        //     y: ScalingUtilities.scaleY(model.y, Controller.gameArenaSize.height, gameArea.height)
        //     width: ScalingUtilities.scaleX(model.width, Controller.gameArenaSize.width, gameArea.width)
        //     height: ScalingUtilities.scaleY(model.height, Controller.gameArenaSize.height, gameArea.height)
        //     radius: model.radius
        //     color: model.color
        //     visible: model.alive
        // }
    }

    // //
    // // INPUT HANDLER
    // //
    // GameInput {
    //     id: gameInput
    //     objectName: "gameInput"
    //     anchors.fill: parent
    // }
}
