#ifndef UTILS_H
#define UTILS_H

#include "chess-library/include/chess.hpp"

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
