#pragma once
#ifndef UTILS_H
#define UTILS_H

#include "chess-library/include/chess.hpp"

struct ScoreMovePair {
    int score;
    chess::Move move; // Assuming Move is a suitable type for your chess library

    ScoreMovePair(int score, chess::Move move) : score(score), move(move) {}
};

inline bool operator<(const ScoreMovePair& a, const ScoreMovePair& b) {
        return a.score < b.score;
}

inline bool operator>(const ScoreMovePair& a, const ScoreMovePair& b) {
    return a.score > b.score;
}

inline bool operator==(const ScoreMovePair& a, const ScoreMovePair& b) {
    return a.score == b.score && a.move == b.move;
}

inline bool operator!=(const ScoreMovePair& a, const ScoreMovePair& b) {
    return !(a == b);
}

struct MinMaxResult {
    int value;
    int depth;
    chess::Move bestMove;
};

using namespace chess;

bool isSquareWhite(Square sq);
Square flipSquare(Square sq);
int manhattanCornerDistance(Square s, Color c);
int manhattanEdgeDistance(Square s);
bool canPromote(const Board& board, Color side, Square pawnSquare);
bool isDraw(const Board& board);
bool controlsCorner(Square bishop, Square corner);
std::string moveToString(const chess::Move& move);
bool isValidSquare(Square sq);

#endif // UTILS_H
