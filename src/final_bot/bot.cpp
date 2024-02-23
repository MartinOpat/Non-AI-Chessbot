
#include "bot.h"

using namespace chess;

class Bot {
private:
    int maxDepth;
    int maxQuiescenceDepth;
    std::chrono::microseconds maxTime;

    bool isOpening;
    bool isEndgame;

    Color us;

    std::map<std::string, std::vector<ScoreMovePair>> openingBook;
    std::array<std::array<int, 64>, 64> historyCutoffTable;
    std::vector<MoveNode> moveHistoryTree;

    Board board;
public:
    Bot() {
        maxDepth = 4;
        maxQuiescenceDepth = 2;
        maxTime = std::chrono::microseconds(2000000);

        isOpening = true;
        isEndgame = false;

        us = Color::NONE;

        openingBook = loadOpeningsFromFile("openings_filtered.pgn");
        historyCutoffTable = {0};
        moveHistoryTree = {};

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

        assert(diff.empty());

        Move move = Move::make<Move::NORMAL>(s1, s2);
        board.makeMove(move);
        if (board.getFen() == fen) {
            return;
        }
        board.unmakeMove(move);
        move = Move::make<Move::NORMAL>(s2, s1);
        board.makeMove(move);

        assert(board.getFen() == fen);
    }

    const char *getBestMove(const std::string& fen) {
        if (us == Color::NONE) {
            us = board.sideToMove();
        }
        if (detectEndgameType(board) != EndgameType::NONE) {
            isEndgame = true;
        }
        updateBoard(fen);

        if (isOpening) {
            if (openingBook.find(board.getFen()) != openingBook.end()) {
                Move move;
                if (us == Color::WHITE) {
                    move = openingBook[fen].back().move;
                } else {
                    move = openingBook[fen].front().move;
                }
                std::string temp = moveToString(move);
                char *cstr = new char[temp.length() + 1];
                std::strcpy(cstr, temp.c_str());
                return cstr;
            }
            isOpening = false;
        } else if (isEndgame) {

        }
        
    }

    Move iterativeDeepening() {
        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        int alpha = -Value::INFINITY;
        int beta = Value::INFINITY;

        int maxDepth = 1;
        Move bestMove;
        while (duration < maxTime) {
            bestMove = alphaBeta(0, maxDepth, alpha, beta);
            maxDepth++;
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        }
        return bestMove;
    }

    Move alphaBeta(int depth, int maxDepth, int alpha, int beta) {
        auto moves = board.legalMoves();
        std::vector<ScoreMovePair> scoreMovePairs;
        for (const auto& move : moves) {
            board.makeMove(move);
            int score = quiescenceSearch(-Value::INFINITY, Value::INFINITY, 0);
            board.unmakeMove(move);
            scoreMovePairs.push_back(ScoreMovePair(score, move));
        }
        std::sort(scoreMovePairs.begin(), scoreMovePairs.end(), std::greater<ScoreMovePair>());
        return scoreMovePairs.front().move;
    }

};