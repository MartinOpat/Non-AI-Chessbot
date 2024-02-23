#ifndef UTILS_H
#define UTILS_H

#include "chess-library/include/chess.hpp"

struct ScoreMovePair {
    int score;
    chess::Move move; // Assuming Move is a suitable type for your chess library

    ScoreMovePair(int score, chess::Move move) : score(score), move(move) {}
};

bool operator<(const ScoreMovePair& a, const ScoreMovePair& b) {
        return a.score < b.score;
}

bool operator>(const ScoreMovePair& a, const ScoreMovePair& b) {
    return a.score > b.score;
}

bool operator==(const ScoreMovePair& a, const ScoreMovePair& b) {
    return a.score == b.score && a.move == b.move;
}

bool operator!=(const ScoreMovePair& a, const ScoreMovePair& b) {
    return !(a == b);
}

using namespace chess;

Square flipSquare(Square sq);
bool isLightSquared(Square sq);
int manhattanDistance(Square a, Square b);
int manhattanCornerDistance(Square s);
int manhattanEdgeDistance(Square s);
bool canPromote(const Board& board, Color side, Square pawnSquare);
bool isDraw(const Board& board);
bool controlsCorner(Square bishop, Square corner);
std::string moveToString(const chess::Move& move);
bool isValidSquare(Square sq);

#endif // UTILS_H
