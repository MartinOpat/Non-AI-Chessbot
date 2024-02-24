#pragma once
#ifndef MOVEGEN_H
#define MOVEGEN_H

#include "chess-library/include/chess.hpp"
#include "utils.h"
#include "moveHistory.h"

using namespace chess;

Movelist getSortedLegalMoves(const Board& board, std::array<std::array<int, 64>, 64>& historyCutoffTable, std::unordered_map<uint64_t, TTEntry>& transpositionTable);
Movelist getSortedCapture(const Board& board, std::array<std::array<int, 64>, 64>& historyCutoffTable);

#endif // MOVEGEN_H
