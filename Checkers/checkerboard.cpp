#include "checkerboard.h"
#include "logic.h"
#include "tile.h"
#include <QPen>
#include <QGraphicsScene>
#include <QDebug>
#include <algorithm>

Checkerboard::Checkerboard(QGraphicsScene& scene) : QGraphicsRectItem(nullptr)
{
    QGraphicsRectItem::setRect(BOARD_POSITION_X, BOARD_POSITION_Y, BOARD_SIZE, BOARD_SIZE);
    setPen(QPen(BOARD_OUTLINE_COLOR, BOARD_OUTLINE_WIDTH));

    CreateTiles(scene);
    CreatePieces(scene);
    //CreatePiecesCustomCoordinates(scene);

    CheckAndMarkPlayerMoveOptions(Common::GetActivePlayer());
}

void Checkerboard::CreateTiles(QGraphicsScene& scene)
{
    std::vector<Coordinates> playableTilesCoordinates = Logic::GeneratePlayableTilesCoordinates();

    for(int row = 1; row <= 8; row++)
    {
        for(int column = 1; column <= 8; column++)
        {
            const Coordinates coordinates(row, column);
            bool playable = false;

            /*Check if the tile is playable*/
            if(std::find(playableTilesCoordinates.cbegin(), playableTilesCoordinates.cend(), coordinates) != playableTilesCoordinates.cend())
            {
                playable = true;
                m_PiecesPlacement[Coordinates(row, column)] = nullptr;
            }

            Tile* tile = new Tile(Coordinates(row, column), playable, this);

            if(playable)
            {
                QObject::connect(tile, &Tile::ClickedSignal, this, &Checkerboard::ProcessTileClicked);
            }

            scene.addItem(tile);
        }
    }

    assert(m_PiecesPlacement.size() == 32);
}

void Checkerboard::CreatePieces(QGraphicsScene& scene)
{
    std::vector<Coordinates> playerLowerStartingPiecesCoordinates = Logic::GenerateStartingPiecesCoordinates(Player::DOWN);
    std::vector<Coordinates> playerUpperStartingPiecesCoordinates = Logic::GenerateStartingPiecesCoordinates(Player::UP);

    for(auto& pieceCoordinates : playerLowerStartingPiecesCoordinates)
    {
        Piece* piece = new Piece(pieceCoordinates, Player::DOWN, this);
        m_PiecesPlacement[Coordinates(pieceCoordinates.Row(), pieceCoordinates.Column())] = piece;
        scene.addItem(piece);
    }

    for(auto& pieceCoordinates : playerUpperStartingPiecesCoordinates)
    {
        Piece* piece = new Piece(pieceCoordinates, Player::UP, this);
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
    std::vector<Coordinates> customCoordinatesPlayerDown = {Coordinates(4, 7), Coordinates(7, 6)};
    std::vector<Coordinates> customCoordinatesPlayerUp = {Coordinates(2, 3), Coordinates(3, 6), Coordinates(4, 3), Coordinates(6, 5)};

    //    PROMOTION (crown generation) TEST
    //    std::vector<Coordinates> customCoordinatesPlayerDown = {Coordinates(2, 3)};
    //    std::vector<Coordinates> customCoordinatesPlayerUp = {Coordinates(7, 6)};

    //    BACKWARD MOVEMENT TEST
    //    std::vector<Coordinates> customCoordinatesPlayerDown = {Coordinates(2, 3)};
    //    std::vector<Coordinates> customCoordinatesPlayerUp = {Coordinates(7, 6)};

    //BACKWARD CAPTURE TEST
    //std::vector<Coordinates> customCoordinatesPlayerDown = {Coordinates(4, 3)};
    //std::vector<Coordinates> customCoordinatesPlayerUp = {Coordinates(6, 5)};

    for(auto& pieceCoordinates : customCoordinatesPlayerDown)
    {
        Piece* piece = new Piece(pieceCoordinates, Player::DOWN, this);
        m_PiecesPlacement[Coordinates(pieceCoordinates.Row(), pieceCoordinates.Column())] = piece;
        scene.addItem(piece);
    }

    for(auto& pieceCoordinates : customCoordinatesPlayerUp)
    {
        Piece* piece = new Piece(pieceCoordinates, Player::UP, this);
        m_PiecesPlacement[Coordinates(pieceCoordinates.Row(), pieceCoordinates.Column())] = piece;
        scene.addItem(piece);
    }
}

void Checkerboard::CheckAndMarkPlayerMoveOptions(Player player)
{
    if(IsMultiCaptureInProgress())
    {
        return;
    }

    std::vector<Piece*> piecesWhichCanCapture = Logic::WhichPiecesCanCapture(player, m_PiecesPlacement);

    if(piecesWhichCanCapture.size() != 0)
    {
        Piece::MarkPiecesWhichCanMove(piecesWhichCanCapture);
    }
    else
    {
        std::vector<Piece*> piecesWhichCanMove = Logic::WhichPiecesCanMove(player, m_PiecesPlacement);
        Piece::MarkPiecesWhichCanMove(piecesWhichCanMove);
    }
}

void Checkerboard::ProcessTileClicked(const Coordinates& targetTileCoordinates)
{
    Piece* activePiece = Piece::GetActivePiece();

    if(activePiece)
    {
        ProcessMove(targetTileCoordinates);
        activePiece->SetUnactive();
    }

    UnmarkAllPieces();

    if(IsMultiCaptureInProgress())
    {
        m_MultiCaptureInProgressPiece->SetActive();
    }
    else
    {
        UnmarkAllPieces();
        CheckAndMarkPlayerMoveOptions(Common::GetActivePlayer());
    }

    qDebug() << "=============================END OF TILE CLICK PROCESSING=============================";
}

void Checkerboard::ProcessMove(const Coordinates& targetTileCoordinates)
{
    Piece* activePiece = Piece::GetActivePiece();

    /*If any capture is possible then any capture has to be the next move*/
    if(Logic::CheckIfPieceCanCapture(activePiece, m_PiecesPlacement))
    {
        if(Logic::CheckCapturePossibility(activePiece, m_PiecesPlacement, targetTileCoordinates))
        {
            CapturePiece(activePiece, targetTileCoordinates);

            if(Logic::CheckIfPieceCanCapture(activePiece, m_PiecesPlacement))
            {
                qDebug("MULTICAPTURE IN PROGRESS");
                m_MultiCaptureInProgressPiece = activePiece;
                return;
            }
            else
            {
                qDebug("END MULTICAPTURE");
                m_MultiCaptureInProgressPiece = nullptr;
                activePiece->SetUnactive();
            }

            CheckEligibilityAndPromotePiece(activePiece);

            activePiece->SetUnactive();
            EndTurn();
        }
        else
        {
            qDebug("Capture was possible but player chose other tile so no move was taken and active piece is reset!");
            activePiece->SetUnactive();
            return;
        }
    }
    else if(Logic::CheckIfPieceCanMove(activePiece, m_PiecesPlacement))
    {
        if(Logic::CheckMovePossibility(activePiece, m_PiecesPlacement, targetTileCoordinates))
        {
            MovePiece(activePiece, targetTileCoordinates);

            CheckEligibilityAndPromotePiece(activePiece);

            activePiece->SetUnactive();
            EndTurn();
        }
    }
    else
    {
        qDebug() << "PIECE CANNOT CAPTURE AND CANNOT MOVE, THIS SHOULD NOT HAPPEN";
        assert(false);
    }

    qDebug() << "=============================END OF MOVE PROCESSING=============================";
}

void Checkerboard::UnmarkAllPieces()
{
    qDebug("%s", __FUNCTION__);

    for(auto& piecePlacement : m_PiecesPlacement)
    {
        Piece* piece = piecePlacement.second;

        if(piece && (piece->IsMarkedActive() || piece->IsMarkedMoveAvailable()))
        {
            piece->Unmark();
        }
    }
}

void Checkerboard::MovePiece(Piece* piece, const Coordinates& targetTileCoordinates)
{
    Coordinates pieceCoordinates(piece->Row(), piece->Column());

    m_PiecesPlacement[pieceCoordinates] = nullptr;
    m_PiecesPlacement[targetTileCoordinates] = piece;
    piece->MoveToTile(targetTileCoordinates);
}

void Checkerboard::CapturePiece(Piece* piece, const Coordinates& targetTileCoordinates)
{
    //qDebug("Capture executed!");
    Coordinates pieceBetween((targetTileCoordinates.Row() + piece->Row()) / 2, (targetTileCoordinates.Column() + piece->Column()) / 2);
    MovePiece(piece, targetTileCoordinates);
    delete m_PiecesPlacement.at(pieceBetween);
    m_PiecesPlacement[pieceBetween] = nullptr;
}

void Checkerboard::EndTurn()
{
    qDebug("%s", __FUNCTION__);

    if(Common::GetActivePlayer() == Player::DOWN)
    {
        Common::SetActivePlayer(Player::UP);
    }
    else if(Common::GetActivePlayer() == Player::UP)
    {
        Common::SetActivePlayer(Player::DOWN);
    }
}

void Checkerboard::CheckEligibilityAndPromotePiece(Piece* piece)
{
    if(Logic::CheckPromotionEligibility(piece))
    {
        piece->Promote();
    }
}

bool Checkerboard::IsMultiCaptureInProgress()
{
    return m_MultiCaptureInProgressPiece != nullptr;
}
