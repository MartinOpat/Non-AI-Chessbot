#include "eval.h"

using namespace chess;

int evaluateMaterial(const Board& board, Color color, bool isEndgame) {
    int score = 0;
    score += evaluatePiece(board, PieceType::PAWN, color, isEndgame);
    score += evaluatePiece(board, PieceType::KNIGHT, color, isEndgame);
    score += evaluatePiece(board, PieceType::BISHOP, color, isEndgame);
    score += evaluatePiece(board, PieceType::ROOK, color, isEndgame);
    score += evaluatePiece(board, PieceType::QUEEN, color, isEndgame);
    return score;
}

int evaluatePiece(const Board& board, PieceType pt, Color color, bool isEndgame) {
    int score = 0;
    Bitboard bitboard = board.pieces(pt, color);

    if (pt == PieceType::PAWN) {
        score = evaluate(bitboard, color, PAWN_TABLE);
        score += bitboard.count() * (isEndgame? Value::PAWN_EG : Value::PAWN_MG);
    } else if (pt == PieceType::KNIGHT) {
        score = evaluate(bitboard, color, KNIGHTS_TABLE);
        score += bitboard.count() * (isEndgame? Value::KNIGHT_EG : Value::KNIGHT_MG);
    } else if (pt == PieceType::BISHOP) {
        score = evaluate(bitboard, color, BISHOPS_TABLE);
        score += bitboard.count() * (isEndgame? Value::BISHOP_EG : Value::BISHOP_MG);
    } else if (pt == PieceType::ROOK) {
        score = evaluate(bitboard, color, ROOKS_TABLE);
        score += bitboard.count() * (isEndgame? Value::ROOK_EG : Value::ROOK_MG);
    } else if (pt == PieceType::QUEEN) {
        score = evaluate(bitboard, color, QUEENS_TABLE);
        score += bitboard.count() * (isEndgame? Value::QUEEN_EG : Value::QUEEN_MG);
    }
    return score;
}

int evaluate(Bitboard& bitboard, Color color, const std::vector<std::vector<int>>& table) {
    int score = 0;
    int row = 0;
    int col = 0;

    int temp;
    while (bitboard) {
        temp = bitboard.lsb();
        bitboard.clear(temp);

        if (color == Color::WHITE) {
            row = temp / 8;
            col = temp % 8;
            score += table[row][col];
        } else {
            row = 7 - temp / 8;
            col = 7 - temp % 8;
            score -= table[row][col];
        }
    }
    return score;
}

int controlCornerWeakKing(Square bishop1, Square bishop2, Square weakKing) {
    std::vector<Square> corners = {Square::underlying::SQ_A1, Square::underlying::SQ_A8, Square::underlying::SQ_H1, Square::underlying::SQ_H8}; 

    // Check if the weak king is in any corner
    bool kingInCorner = std::any_of(corners.begin(), corners.end(), [&weakKing](const Square& corner) {
        return weakKing == corner;
    });

    // If the king is not in a corner, no need to evaluate further
    if (!kingInCorner) {
        return 0;
    }

    // Now, check if either bishop controls the corner square where the weak king is located
    bool isCornerControlled = false;
    for (const Square& corner : corners) {
        if (weakKing == corner) {
            if (controlsCorner(bishop1, corner) || controlsCorner(bishop2, corner)) {
                isCornerControlled = true;
                break; // No need to check other corners
            }
        }
    }

    // Increase score if weak king is pushed to a controlled corner
    if (isCornerControlled) {
        return 100; // Example value, adjust based on your engine's evaluation scale
    }
    return 0;
}

int pushToEdge(Square s) {
    int edgeDistance = manhattanEdgeDistance(s);

    // Maximize score when distance is smallest
    return (7 - edgeDistance) * 10; // Scale as needed
}

int pushToCorner(Square s) {
    int cornerDistance = manhattanCornerDistance(s);

    // Score increases as the piece gets closer to the corner
    return (7 - cornerDistance) * 15; // Score multiplier is arbitrary, adjust as needed
}

int pushClose(Square a, Square b) {
    int distance = manhattanDistance(a, b);

    // Decrease score as distance increases
    return (14 - distance) * 10; // Scale as needed
}

int pushAway(Square a, Square b) {
    int distance = manhattanDistance(a, b);

    // Increase score as distance increases
    return distance * 10; // Scale as needed

}


// TODO: Add king safety evaluation & king position
