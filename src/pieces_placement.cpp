// #include "pieces_placement.h"
// #include "coordinates_database.h"
// #include "piece_state_manager.h"
//
// void PiecesPlacement::createPiece(const Coordinates& coordinates, Player player)
// {
//     // if (!isPieceAtCoordinates(c oordinates))
//     // {
//     //     const auto& ref = pieces_.emplace_back(std::make_unique<Piece>(coordinates, player));
//     //     piecesModels_.push_back(std::make_unique<PieceModel>(*ref));
//     // }
//     // else
//     // {
//     //     throw std::runtime_error("Error, piece is already present on given coordinates");
//     // }
// }
//
// void PiecesPlacement::createPieces()
// {
//     std::set<Coordinates> southPlayerStartingPiecesCoordinates = CoordinatesDatabase::getInstance().getStartingPieceCoordinatesOfSouthPlayer();
//     std::set<Coordinates> northPlayerStartingPiecesCoordinates = CoordinatesDatabase::getInstance().getStartingPieceCoordinatesOfNorthPlayer();
//
//     std::set<Coordinates> playableTilesCoordinates = CoordinatesDatabase::getInstance().getPlayableCoordinates();
//
//     auto placePieces = [this, &playableTilesCoordinates](const std::set<Coordinates>& piecesCoordinates, const Player& player)
//     {
//         for (const auto& pieceCoordinates: piecesCoordinates)
//         {
//             if (playableTilesCoordinates.contains(pieceCoordinates))
//             {
//                 createPiece(pieceCoordinates, player);
//             }
//             else
//             {
//                 throw std::runtime_error("Error, cannot place piece on non-playable tile");
//             }
//         }
//     };
//
//     placePieces(southPlayerStartingPiecesCoordinates, Player::SOUTH);
//     placePieces(northPlayerStartingPiecesCoordinates, Player::NORTH);
// }
//
// void PiecesPlacement::markPiecesWhichCanMove(const std::vector<Piece*>& pieces)
// {
//     for (auto& piece: pieces)
//     {
//         qDebug() << "Piece" << piece->getId() << "can move";
//         PieceStateManager::markPieceHasValidMovePossible(*piece);
//     }
// }
//
// bool PiecesPlacement::isPieceAtCoordinates(const Coordinates& coordinates) const
// {
//     return std::ranges::find_if(pieces_, [&coordinates](const auto& piece)
//     {
//         return piece->getCoordinates() == coordinates;
//     }) != pieces_.end();
// }
//
// Piece& PiecesPlacement::getPieceAtCoordinates(const Coordinates& coordinates) const
// {
//     if (isPieceAtCoordinates(coordinates))
//     {
//         auto iter = std::find_if(pieces_.begin(), pieces_.end(), [coordinates](const std::unique_ptr<Piece>& piece)
//         {
//             return piece->getCoordinates() == coordinates;
//         });
//
//         return *(iter->get());
//     }
//     else
//     {
//         throw std::runtime_error("Error, no piece at given coordinates");
//     }
// }
//
// void PiecesPlacement::removePieceAtCoordinates(const Coordinates& coordinates)
// {
//     auto iter = std::ranges::find_if(pieces_, [coordinates](const auto& piece)
//     {
//         return piece->getCoordinates() == coordinates;
//     });
//
//     if (iter != pieces_.end())
//     {
//         pieces_.erase(iter);
//     }
//     else
//     {
//         throw std::runtime_error("Error, trying to remove piece which is not present in pieces placement");
//     }
// }
//
// size_t PiecesPlacement::countPlayerPieces(Player player) const
// {
//     return std::ranges::count_if(pieces_, [&player](const auto& piece)
//     {
//         return piece->getPlayer() == player;
//     });
// }
//
// bool PiecesPlacement::didAnyPlayerRunOutOfPieces() const
// {
//     return (countPlayerPieces(Player::SOUTH) == 0) || (countPlayerPieces(Player::NORTH) == 0);
// }
//
// Player PiecesPlacement::getPlayerWithNoPiecesLeft() const
// {
//     if (countPlayerPieces(Player::SOUTH) == 0)
//     {
//         return Player::SOUTH;
//     }
//     else if (countPlayerPieces(Player::NORTH) == 0)
//     {
//         return Player::NORTH;
//     }
//     else
//     {
//         throw std::runtime_error("Error, both players have pieces left");
//     }
// }
