#include "checkerboard.h"
#include "logic.h"
#include "tile.h"
#include <QPen>
#include <QGraphicsScene>
#include <QDebug>
#include <algorithm>

Checkerboard::Checkerboard() : QGraphicsRectItem(nullptr)
{
    QGraphicsRectItem::setRect(BOARD_POSITION_X, BOARD_POSITION_Y, BOARD_SIZE, BOARD_SIZE);
    setPen(QPen(BOARD_OUTLINE_COLOR, BOARD_OUTLINE_WIDTH));

    /*Checkerboard and tiles are only created once, pieces are recreated during every game restart*/
    CreateTiles();
    StartNewGame();
}

void Checkerboard::StartNewGame()
{
    qDebug("%s", __FUNCTION__);

    Common::ResetActivePlayer();

    CreatePieces();
    CheckAndMarkPlayerMoveOptions(Common::GetActivePlayer());
}

void Checkerboard::ClearPreviousGame()
{
    qDebug("%s", __FUNCTION__);

    for(auto& piecePlacement : m_PiecesPlacement)
    {
        if(piecePlacement.second)
        {
            delete piecePlacement.second;
            piecePlacement.second = nullptr;
        }
    }

    Piece* activePiece = Piece::GetActivePiece();

    if(activePiece)
    {
        activePiece->SetUnactive();
    }
}

void Checkerboard::RestartGame()
{
    qDebug("%s", __FUNCTION__);

    ClearPreviousGame();
    StartNewGame();
}

void Checkerboard::CreateTiles()
{
    std::vector<Coordinates> playableTilesCoordinates = Logic::GeneratePlayableTilesCoordinates();

    for(int row = 1; row <= 8; row++)
    {
        for(int column = 1; column <= 8; column++)
        {
            const Coordinates tileCoordinates(row, column);
            bool playable = false;

            /*Check if the tile is playable*/
            if(std::find(playableTilesCoordinates.cbegin(), playableTilesCoordinates.cend(), tileCoordinates) != playableTilesCoordinates.cend())
            {
                playable = true;
                m_PiecesPlacement[tileCoordinates] = nullptr;
            }

            Tile* tile = new Tile(tileCoordinates, playable, this);

            if(playable)
            {
                QObject::connect(tile, &Tile::ClickedSignal, this, &Checkerboard::ProcessTileClicked);
            }
        }
    }
}

void Checkerboard::CreatePieces()
{
    std::vector<Coordinates> playerLowerStartingPiecesCoordinates = Logic::GenerateStartingPiecesCoordinates(Player::DOWN);
    std::vector<Coordinates> playerUpperStartingPiecesCoordinates = Logic::GenerateStartingPiecesCoordinates(Player::UP);

    for(auto& pieceCoordinates : playerLowerStartingPiecesCoordinates)
    {
        Piece* piece = new Piece(pieceCoordinates, Player::DOWN, this);
        m_PiecesPlacement[Coordinates(pieceCoordinates.Row(), pieceCoordinates.Column())] = piece;
    }

    for(auto& pieceCoordinates : playerUpperStartingPiecesCoordinates)
    {
        Piece* piece = new Piece(pieceCoordinates, Player::UP, this);
        m_PiecesPlacement[Coordinates(pieceCoordinates.Row(), pieceCoordinates.Column())] = piece;
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
