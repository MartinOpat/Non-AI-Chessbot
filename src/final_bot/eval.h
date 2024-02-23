#ifndef EVAL_H
#define EVAL_H

#include "chess-library/include/chess.hpp"
#include "utils.h"
#include "consts.h"

int evaluateMaterial(const Board& board, Color color, bool isEndgame);
int evaluatePiece(const Board& board, PieceType pt, Color color, bool isEndgame);
int controlCornerWeakKing(Square bishop1, Square bishop2, Square weakKing);
int pushToEdge(Square s);
int pushToCorner(Square s);
int pushClose(Square a, Square b);
int pushAway(Square a, Square b);




#endif // EVAL_H
