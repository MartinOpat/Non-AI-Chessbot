#include "utils.h"

using namespace chess;

bool isSquareWhite(Square sq) {
    return (sq.rank() + sq.file()) % 2;
}

Square flipSquare(Square sq) {
    // Calculate the rank (0-7) and file (0-7) of the square.
    int rank = sq.rank();
    int file = sq.file();
    
    // Flip the rank. If we are on rank 0 (bottom rank), we want to go to rank 7 (top rank), and vice versa.
    int flippedRank = 7 - rank;
    
    // Convert back to square index.
    return Square(flippedRank * 8 + file);
}

// Distance to the closest corner (a1, h1, a8, h8)
int manhattanCornerDistance(Square s, Color c) {
    if (c == Color::WHITE) {
        return std::min({Square::distance(s, Square::underlying::SQ_H1), Square::distance(s, Square::underlying::SQ_A8)});
    } else {
        return std::min({Square::distance(s, Square::underlying::SQ_H8), Square::distance(s, Square::underlying::SQ_A1)});
    }
}

int manhattanEdgeDistance(Square s) {
    int file = s.file(); // 0-7 for a-h
    int rank = s.rank(); // 0-7 for 1-8
    int fileEdgeDistance = std::min(file, 7 - file);
    int rankEdgeDistance = std::min(rank, 7 - rank);
    return std::min(fileEdgeDistance, rankEdgeDistance);
}

bool canPromote(const Board& board, Color side, Square pawnSquare) {
    // Assuming the board's rank is from 0 (rank 1) to 7 (rank 8)
    int rank = pawnSquare.rank(); // Determine the pawn's rank based on its square.
    
    if (side == Color::WHITE) {
        // White pawns promote on the 8th rank (which is rank 7 in 0-indexed array).
        return rank == 7;
    } else {
        // Black pawns promote on the 1st rank (which is rank 0 in 0-indexed array).
        return rank == 0;
    }
}

bool isDraw(const Board& board) {
    // Draw by insufficient material
    if (board.isInsufficientMaterial()) {
        return true;
    }

    // Draw by threefold repetition
    if (board.isRepetition()) {
        return true;
    }

    // Draw by 50-move rule
    if (board.isHalfMoveDraw()) {
        return board.getHalfMoveDrawType().first == GameResultReason::FIFTY_MOVE_RULE;
    }

    GameResultReason grr = board.isGameOver().first;
    if (grr == GameResultReason::STALEMATE) {
        return true;
    }

    return false;
}

bool controlsCorner(Square bishop, Square corner) {
    return isSquareWhite(bishop) == isSquareWhite(corner);
}

std::string moveToString(const chess::Move& move) {
    std::ostringstream oss;
    oss << move; // Use the overloaded operator<<
    return oss.str(); // Convert the contents of the stream into a string
}

bool isValidSquare(Square sq) {
    int rank = sq.rank(); // Determine the rank (0 to 7)
    int file = sq.file(); // Determine the file (0 to 7)

    return rank >= 0 && rank < 8 && file >= 0 && file < 8;
}
