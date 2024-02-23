
#include "bot.h"

using namespace chess;

class Bot {
private:
    int maxDepth;
    std::chrono::microseconds maxTime;

    bool isOpening;
    bool isEndgame;

    Color us;

    std::map<std::string, std::vector<ScoreMovePair>> openingBook;
    std::array<std::array<int, 64>, 64> historyCutoffTable;

    Board board;
public:
    Bot() {
        maxDepth = 4;
        maxTime = std::chrono::microseconds(2000000);

        isOpening = true;
        isEndgame = false;

        us = Color::NONE;

        openingBook = loadOpeningsFromFile("openings_filtered.pgn");
        historyCutoffTable = {0};

        board = Board();
    }

    void updateHistoryScore(const Move& move, int depth) {
        this->historyCutoffTable[move.from().index()][move.to().index()] += depth * depth;
    }

    int get_move_history_score(const chess::Move& move) {
        return this->historyCutoffTable[move.from().index()][move.to().index()];
    }

    int evaluateBoard(const Board& board) {
        if (isDraw(board)) {
            return 0;
        }

        auto grr = board.isGameOver().first;
        if (grr == GameResultReason::CHECKMATE) {
            return (board.sideToMove() == Color::WHITE) ? Value::MATE : -Value::MATE;
        }

        int score = 0;
        score += evaluateMaterialAndPosition(board, us, isEndgame);
        return score;
    }

    void updateBoard(const std::string& fen) {
        Bitboard curr = board.all();
        Bitboard updated = Board(fen).all();
        Bitboard diff = curr ^ updated;

        Square s1 = Square(diff.lsb());
        diff.clear(s1.index());
        Square s2 = Square(diff.lsb());

        Move move = Move::make<Move::NORMAL>(s1, s2);
        board.makeMove(move);
        if (board.getFen() == fen) {
            return;
        }
        board.unmakeMove(move);
        move = Move::make<Move::NORMAL>(s2, s1);
        board.makeMove(move);
        if (board.getFen() == fen) {
            return;
        } else {
            std::cerr << "Error: Board not updated correctly" << std::endl;
        }
    }

};