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
            x: 150
            y: 150
            width: 150
            height: 150
            color: "red"
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
