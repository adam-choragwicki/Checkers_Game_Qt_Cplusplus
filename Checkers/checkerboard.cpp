#include "checkerboard.h"
#include "logic.h"
#include "tile.h"
#include <QPen>
#include <QGraphicsScene>
#include <QDebug>

std::map<Coordinates, Piece*> Checkerboard::m_PiecesPlacement;
Piece* Checkerboard::m_MultiCaptureInProgressPiece = nullptr;

Checkerboard::Checkerboard(QGraphicsScene& scene) : QGraphicsRectItem(nullptr)
{
    QGraphicsRectItem::setRect(BOARD_POSITION_X, BOARD_POSITION_Y, BOARD_SIZE, BOARD_SIZE);
    setPen(QPen(BOARD_OUTLINE_COLOR, BOARD_OUTLINE_WIDTH));

    CreateTiles(scene);
    CreatePieces(scene);
    //CreatePiecesCustomCoordinates(scene);

    std::vector<Piece*> piecesWhichCanCapture = Logic::WhichPiecesCanCapture(Common::GetActivePlayer(), m_PiecesPlacement);

    if(piecesWhichCanCapture.size() == 0)
    {
        std::vector<Piece*> piecesWhichCanMove = Logic::WhichPiecesCanMove(Common::GetActivePlayer(), m_PiecesPlacement);
        MarkPieces(piecesWhichCanMove);
    }
    else
    {
        MarkPieces(piecesWhichCanCapture);
    }
}

void Checkerboard::CreateTiles(QGraphicsScene& scene)
{
    for(int row = 1; row <= 8; row++)
    {
        for(int column = 1; column <= 8; column++)
        {
            Tile* tile = new Tile(row, column, this);
            m_PiecesPlacement[Coordinates(row, column)] = nullptr;
            scene.addItem(tile);
        }
    }

    assert(m_PiecesPlacement.size() == 64);
}

void Checkerboard::CreatePieces(QGraphicsScene& scene)
{
    std::vector<Coordinates> playerLowerStartingPiecesCoordinates = Logic::GenerateStartingPiecesCoordinates(Player::Down);
    std::vector<Coordinates> playerUpperStartingPiecesCoordinates = Logic::GenerateStartingPiecesCoordinates(Player::Up);

    for(auto pieceCoordinates : playerLowerStartingPiecesCoordinates)
    {
        Piece* piece = new Piece(pieceCoordinates, Player::Down, this);
        m_PiecesPlacement[Coordinates(pieceCoordinates.Row(), pieceCoordinates.Column())] = piece;
        scene.addItem(piece);
    }

    for(auto pieceCoordinates : playerUpperStartingPiecesCoordinates)
    {
        Piece* piece = new Piece(pieceCoordinates, Player::Up, this);
        m_PiecesPlacement[Coordinates(pieceCoordinates.Row(), pieceCoordinates.Column())] = piece;
        scene.addItem(piece);
    }
}

void Checkerboard::CreatePiecesCustomCoordinates(QGraphicsScene &scene)
{
    //    GENERAL TEST
    //    std::vector<Coordinates> customCoordinatesPlayerDown = {Coordinates(5, 4)};
    //    std::vector<Coordinates> customCoordinatesPlayerUp = {Coordinates(7, 6)};

    //    MULTICAPTURE TEST
    //    std::vector<Coordinates> customCoordinatesPlayerDown = {Coordinates(7, 6)};
    //    std::vector<Coordinates> customCoordinatesPlayerUp = {Coordinates(2, 5), Coordinates(4, 5), Coordinates(6, 5)};

    //    PROMOTION (crown generation) TEST
    //    std::vector<Coordinates> customCoordinatesPlayerDown = {Coordinates(2, 3)};
    //    std::vector<Coordinates> customCoordinatesPlayerUp = {Coordinates(7, 6)};

    //    BACKWARD MOVEMENT TEST
    //    std::vector<Coordinates> customCoordinatesPlayerDown = {Coordinates(2, 3)};
    //    std::vector<Coordinates> customCoordinatesPlayerUp = {Coordinates(7, 6)};

    //BACKWARD CAPTURE TEST
    std::vector<Coordinates> customCoordinatesPlayerDown = {Coordinates(4, 3)};
    std::vector<Coordinates> customCoordinatesPlayerUp = {Coordinates(6, 5)};

    for(auto pieceCoordinates : customCoordinatesPlayerDown)
    {
        Piece* piece = new Piece(pieceCoordinates, Player::Down, this);
        m_PiecesPlacement[Coordinates(pieceCoordinates.Row(), pieceCoordinates.Column())] = piece;
        scene.addItem(piece);
    }

    for(auto pieceCoordinates : customCoordinatesPlayerUp)
    {
        Piece* piece = new Piece(pieceCoordinates, Player::Up, this);
        m_PiecesPlacement[Coordinates(pieceCoordinates.Row(), pieceCoordinates.Column())] = piece;
        scene.addItem(piece);
    }
}

void Checkerboard::ProcessTileClicked(const int targetRow, const int targetColumn, bool tileIsPlayable)
{
    if(tileIsPlayable)
    {
        if(m_PiecesPlacement.at(Coordinates(targetRow, targetColumn)) == nullptr)
        {
            //qDebug("Clicked tile (%d,%d) is PLAYABLE and EMPTY", targetRow, targetColumn);
        }
        else
        {
            //qDebug("Clicked tile (%d,%d) is PLAYABLE and THERE IS PIECE ON IT", targetRow, targetColumn);
        }
    }
    else
    {
        assert(m_PiecesPlacement.at(Coordinates(targetRow, targetColumn)) == nullptr);
        //qDebug("Clicked tile (%d,%d)", targetRow, targetColumn);
    }

    Piece* activePiece = Piece::GetActivePiece();

    if(activePiece && tileIsPlayable)
    {
        if(Logic::CheckCapturePossibility(activePiece, m_PiecesPlacement, targetRow, targetColumn))
        {
            CapturePiece(activePiece, targetRow, targetColumn);

            if(Logic::CheckIfPieceCanCapture(activePiece, m_PiecesPlacement))
            {
                qDebug("SetMultiCaptureInProgressPiece");
                m_MultiCaptureInProgressPiece = activePiece;

                activePiece->SetActivePiecePointer();
                activePiece->MarkActive();
                return;
            }
            else
            {
                qDebug("ResetMultiCaptureInProgressPiece");
                m_MultiCaptureInProgressPiece = nullptr;
            }

            if(!activePiece->IsPromoted() && Logic::CheckPromotion(activePiece))
            {
                activePiece->Promote();
            }

            EndTurn();
        }
        else if(!IsMultiCaptureInProgress() && Logic::CheckMovePossibility(activePiece, m_PiecesPlacement, targetRow, targetColumn))
        {
            MovePiece(activePiece, targetRow, targetColumn);

            if(!activePiece->IsPromoted() && Logic::CheckPromotion(activePiece))
            {
                activePiece->Promote();
            }

            EndTurn();
        }
    }

    if(!IsMultiCaptureInProgress())
    {
        UnmarkAllPieces();

        std::vector<Piece*> piecesWhichCanCapture = Logic::WhichPiecesCanCapture(Common::GetActivePlayer(), m_PiecesPlacement);

        if(piecesWhichCanCapture.size() == 0)
        {
            std::vector<Piece*> piecesWhichCanMove = Logic::WhichPiecesCanMove(Common::GetActivePlayer(), m_PiecesPlacement);
            MarkPieces(piecesWhichCanMove);
        }
        else
        {
            MarkPieces(piecesWhichCanCapture);
        }
    }
}

void Checkerboard::MarkPieces(std::vector<Piece*>& pieces)
{
    for(auto piece : pieces)
    {
        piece->MarkValidMoveAvailable();
    }
}

void Checkerboard::UnmarkAllPieces()
{
    for(auto piecePlacement : m_PiecesPlacement)
    {
        if(piecePlacement.second != nullptr)
        {
            piecePlacement.second->Unmark();
        }
    }
}

void Checkerboard::MovePiece(Piece* piece, const int targetRow, const int targetColumn)
{
    m_PiecesPlacement[Coordinates(piece->Row(), piece->Column())] = nullptr;
    m_PiecesPlacement[Coordinates(targetRow, targetColumn)] = piece;
    piece->MoveToTile(targetRow, targetColumn);
}

void Checkerboard::CapturePiece(Piece* piece, const int targetRow, const int targetColumn)
{
    qDebug("Capture executed!");
    Coordinates pieceBetween((targetRow + piece->Row()) / 2, (targetColumn + piece->Column()) / 2);
    MovePiece(piece, targetRow, targetColumn);
    delete m_PiecesPlacement.at(pieceBetween);
    m_PiecesPlacement[pieceBetween] = nullptr;
}

void Checkerboard::EndTurn()
{
    if(Common::GetActivePlayer() == Player::Down)
    {
        Common::SetActivePlayer(Player::Up);
    }
    else if(Common::GetActivePlayer() == Player::Up)
    {
        Common::SetActivePlayer(Player::Down);
    }
    else
    {
        assert(false);
    }
}

bool Checkerboard::IsMultiCaptureInProgress()
{
    return m_MultiCaptureInProgressPiece != nullptr;
}
