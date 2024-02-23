
#include "movegen.h"

using namespace chess;

Movelist getSortedLegalMoves(const Board& board, std::array<std::array<int, 64>, 64> historyCutoffTable) {
    Movelist captureMoves;
    Movelist quietMoves;
    movegen::legalmoves<movegen::MoveGenType::CAPTURE>(captureMoves, board);
    movegen::legalmoves<movegen::MoveGenType::QUIET>(quietMoves, board);

    sortMoves(captureMoves, historyCutoffTable);
    sortMoves(quietMoves, historyCutoffTable);

    captureMoves.merge(quietMoves);
    return captureMoves;
}

void sortMoves(Movelist& moves, std::array<std::array<int, 64>, 64> historyCutoffTable) {
    std::sort(moves.begin(), moves.end(), [&](const Move& a, const Move& b) {
        return historyCutoffTable[a.from().index()][a.to().index()] > historyCutoffTable[b.from().index()][b.to().index()];
    });
}