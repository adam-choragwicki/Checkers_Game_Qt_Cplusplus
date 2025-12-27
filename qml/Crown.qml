import QtQuick

Item {
    id: crownRoot

    property color color: Qt.rgba(150 / 255, 150 / 255, 150 / 255, 1)
    readonly property var crownVertices: [[0, 0], [6, 8], [12, 0], [18, 8], [23, 0], [29, 8], [34, 0], [33, 20], [2, 20]]

    // Size of crown; scale is derived from width/height
    width: parent ? parent.width * 0.7 : 34
    height: width * (20.0 / 34.0)

    Canvas {
        anchors.fill: parent

        onPaint: {
            const context = getContext("2d");
            context.clearRect(0, 0, width, height);

            const pts = crownRoot.crownVertices;
            const sx = width / 34.0;
            const sy = height / 20.0;

            context.beginPath();
            context.moveTo(pts[0][0] * sx, pts[0][1] * sy);

            for (let i = 1; i < pts.length; ++i) {
                context.lineTo(pts[i][0] * sx, pts[i][1] * sy);
            }

            context.closePath();

            context.fillStyle = crownRoot.color;
            context.fill();

            context.lineWidth = 1;
            context.strokeStyle = "#666";
            context.stroke();
        }
    }
}
