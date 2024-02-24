
#include "movegen.h"

using namespace chess;

Movelist getSortedLegalMoves(const Board& board, std::array<std::array<int, 64>, 64>& historyCutoffTable, std::unordered_map<uint64_t, TTEntry>& transpositionTable) {
    Movelist captureMoves;
    Movelist quietMoves;
    movegen::legalmoves<movegen::MoveGenType::CAPTURE>(captureMoves, board);
    movegen::legalmoves<movegen::MoveGenType::QUIET>(quietMoves, board);

    sortMoves(captureMoves, historyCutoffTable);
    sortMoves(quietMoves, historyCutoffTable);

    Movelist ans;

    uint64_t zobristHash = board.hash();
    if (transpositionTable.find(zobristHash) != transpositionTable.end()) {
        TTEntry entry = transpositionTable[zobristHash];
        if (entry.flag == NodeType::EXACT) {
            ans.add(entry.bestMove);
        }
    }

    ans.merge(captureMoves);
    ans.merge(quietMoves);
    return ans;
}

Movelist getSortedCapture(const Board& board, std::array<std::array<int, 64>, 64>& historyCutoffTable) {
    Movelist captureMoves;
    movegen::legalmoves<movegen::MoveGenType::CAPTURE>(captureMoves, board);
    sortMoves(captureMoves, historyCutoffTable);
    return captureMoves;
}

void sortMoves(Movelist& moves, std::array<std::array<int, 64>, 64> historyCutoffTable) {
    std::sort(moves.begin(), moves.end(), [&](const Move& a, const Move& b) {
        return historyCutoffTable[a.from().index()][a.to().index()] > historyCutoffTable[b.from().index()][b.to().index()];
    });
}