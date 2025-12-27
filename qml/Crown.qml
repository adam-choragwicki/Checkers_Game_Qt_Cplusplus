import QtQuick

Item {
    id: crownRoot

    property color color: Qt.rgba(150 / 255, 150 / 255, 150 / 255, 1)
    readonly property real baseWidth: 34
    readonly property real baseHeight: 20

    // Scale crown relative to piece
    width: parent ? parent.width * 0.7 : baseWidth
    height: width * (baseHeight / baseWidth)

    // Crown as polygon
    readonly property var vertices: [
        [0, 0],
        [6, 8],
        [12, 0],
        [18, 8],
        [23, 0],
        [29, 8],
        [34, 0],
        [33, 20],
        [2, 20]
    ]

    Canvas {
        anchors.fill: parent

        onPaint: {
            const context = getContext("2d")
            context.clearRect(0, 0, width, height)

            const scaleX = width / crownRoot.baseWidth
            const scaleY = height / crownRoot.baseHeight

            context.beginPath()

            // First vertex
            context.moveTo(
                crownRoot.vertices[0][0] * scaleX,
                crownRoot.vertices[0][1] * scaleY
            )

            // Remaining vertices
            for (let i = 1; i < crownRoot.vertices.length; ++i) {
                context.lineTo(
                    crownRoot.vertices[i][0] * scaleX,
                    crownRoot.vertices[i][1] * scaleY
                )
            }

            context.closePath()

            context.fillStyle = crownRoot.color
            context.fill()

            context.lineWidth = Math.max(1, width * 0.04)
            context.strokeStyle = "#666"
            context.stroke()
        }
    }
}
