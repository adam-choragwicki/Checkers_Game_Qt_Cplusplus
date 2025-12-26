// #pragma once
//
// #include "piece.h"
// #include "gui_config.h"
// // #include "crown.h"
// // #include <QGraphicsEllipseItem>
// // #include <QGraphicsSceneMouseEvent>
// #include <QPropertyAnimation>
//
// class PieceModel// : public QObject, public QGraphicsEllipseItem
// {
// // Q_OBJECT
//     Q_PROPERTY(QPointF pos READ pos WRITE setPos)
//
// signals:
//     void endMovement(const Coordinates& newCoordinates);
//
// public slots:
//     void animateMovementToNewCoordinates(const Coordinates& currentCoordinates, const Coordinates& newCoordinates);
//     void addCrown();
//
// public:
//     explicit PieceModel(Piece& piece);
//     ~PieceModel();// override;
//
//     // void updateColours();
//
//     // void mousePressEvent(QGraphicsSceneMouseEvent* event); override;
//
//     [[nodiscard]] Piece& getPiece() const
//     { return piece_; }
//
// private:
//     Piece& piece_;
//
//     std::unique_ptr<QPropertyAnimation> animation_;
//     // std::unique_ptr<Crown> crown_;
// };
