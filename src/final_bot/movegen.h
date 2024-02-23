#ifndef MOVEGEN_H
#define MOVEGEN_H

#include "chess-library/include/chess.hpp"

using namespace chess;

Movelist getSortedLegalMoves(const Board& board, std::array<std::array<int, 64>, 64> historyCutoffTable);


#endif // MOVEGEN_H
