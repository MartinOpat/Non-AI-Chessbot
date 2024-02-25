
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

    std::unordered_map<uint64_t, TTEntry> transpositionTable;

    Board board;
public:
    Bot() {
        maxDepth = 4;
        maxQuiescenceDepth = 2;
        maxTime = std::chrono::microseconds(2000000);

        isOpening = true;
        isEndgame = false;

        // openingBook = loadOpeningsFromFile("better_filtered_openings.pgn");
        openingBook = loadOpeningsFromString(OPENINGS_BOOK_STRING);
        historyCutoffTable = {0};

        board = Board();
    }

    void updateHistoryScore(const Move& move, int depth) {
        this->historyCutoffTable[move.from().index()][move.to().index()] += depth * depth;
    }

    int evaluateBoard(const Board& board, int depth) {
        if (isDraw(board)) {
            return 0;
        }

        auto grr = board.isGameOver().first;
        if (grr == GameResultReason::CHECKMATE) {
            return (board.sideToMove() == Color::WHITE) ? -Value::MATE-depth : Value::MATE+depth;
        }

        int score = 0;
        if (isEndgame) {
            score = evaluateEndgames(board);
        } else {
            score += evaluateMaterialAndPosition(board, Color::WHITE, false);
            score += evaluateMaterialAndPosition(board, Color::BLACK, false);
        }
        return score;
    }

    void updateBoard(const std::string& fen) {
        Movelist legalMoves;
        movegen::legalmoves(legalMoves, board);
        for (const auto& move : legalMoves) {
            Board tempBoard = board;  // Make a copy of the current board
            tempBoard.makeMove(move);
            if (tempBoard.getFen() == fen) {
                board.makeMove(move);  // Make the move on the original board
                return;
            }
        }
        board.setFen(fen);
    }


    const char *getBestMove(const std::string& fen) {
        if (detectEndgameType(board) != EndgameType::NONE) {
            isEndgame = true;
        }

        // std::cout << fen << " " << board.getFen() << std::endl;
        if (fen != startFen) 
            updateBoard(fen);

        if (isOpening) {
            if (openingBook.find(board.getFen()) != openingBook.end()) {
                Move move;
                if (us == Color::WHITE) {
                    move = openingBook[fen].back().move;
                } else {
                    move = openingBook[fen].front().move;
                }
                board.makeMove(move);

                std::string temp = moveToString(move);
                char *cstr = new char[temp.length() + 1];
                std::strcpy(cstr, temp.c_str());
                return cstr;
            }
            isOpening = false;
        }

        transpositionTable.clear();
        MinMaxResult result = iterativeDeepening(board.sideToMove());
        Move move = result.bestMove;
        board.makeMove(move);

        std::cout << "Best Move: " << moveToString(move) << " Score: " << result.value << std::endl;
        std::string temp = moveToString(move);
        char *cstr = new char[temp.length() + 1];
        std::strcpy(cstr, temp.c_str());
        return cstr;
    }

    MinMaxResult iterativeDeepening(Color c) {
        int depth = 1;
        MinMaxResult bestMove;
        while (depth <= maxDepth) {
            bestMove = alphaBeta(depth, -Value::MATE, Value::MATE, c);
            std::cout << "Depth: " << depth << " Score: " << bestMove.value << " Best Move: " << moveToString(bestMove.bestMove) << std::endl;
            depth++;
        }
        return bestMove;
    }

    MinMaxResult alphaBeta(int depth, int alpha, int beta, Color c) {
        uint64_t hash = board.hash();
        int origAlpha = alpha;

        if (transpositionTable.find(hash) != transpositionTable.end()) {
            TTEntry entry = transpositionTable[hash];
            if (entry.depth >= depth) {
                if (entry.flag == NodeType::EXACT) {
                    return MinMaxResult{.value=entry.score, .depth=entry.depth};
                } else if (entry.flag == NodeType::LOWERBOUND) {
                    alpha = std::max(alpha, entry.score);
                } else if (entry.flag == NodeType::UPPERBOUND) {
                    beta = std::min(beta, entry.score);
                }
                if (alpha >= beta) {
                    return MinMaxResult{.value=entry.score, .depth=entry.depth};
                }
            }
        }

        if (board.isGameOver().first == GameResultReason::CHECKMATE) {
            return MinMaxResult{.value=-Value::MATE-depth, .depth=depth};
        }

        if (depth <= 0) {
            return quiescenseSearch(maxQuiescenceDepth, alpha, beta, c);
        }

        Movelist legalMoves = getSortedLegalMoves(board, historyCutoffTable, transpositionTable);
        MinMaxResult best{.value=Value::NEG_INFINITY, .depth=0};

        for (const Move& move: legalMoves) {
            board.makeMove(move);
            MinMaxResult possBest = alphaBeta(depth-1, -beta, -alpha, ~c);
            possBest.value = -possBest.value;
            possBest.bestMove = move;
            board.unmakeMove(move);

            if (possBest.value > best.value) {
                best = possBest;
            }
            if (possBest.value > alpha) {
                alpha = possBest.value;
            }
            if (alpha >= beta) {
                updateHistoryScore(move, depth);
                break;
            }
        }

        TTEntry entry{.score=best.value, .depth=best.depth, .bestMove=best.bestMove};
        if (best.value <= origAlpha) {
            entry.flag = NodeType::UPPERBOUND;
        } else if (best.value >= beta) {
            entry.flag = NodeType::LOWERBOUND;
        } else {
            entry.flag = NodeType::EXACT;
        }
        transpositionTable[hash] = entry;

        return best;
    }

    MinMaxResult quiescenseSearch(int depth, int alpha, int beta, Color c) {
        int max = (c == Color::WHITE ? 1 : -1);
        int boardValue = max * evaluateBoard(board, depth);
        uint64_t hash = board.hash();
        if (boardValue >= beta) {
            return MinMaxResult {.value=beta, .depth=depth};
        }
        if (alpha < boardValue) {
            alpha = boardValue;
        }

        if (transpositionTable.find(hash) != transpositionTable.end()) {
            TTEntry entry = transpositionTable[hash];
            if (entry.flag == NodeType::EXACT) {
                return MinMaxResult{.value=entry.score, .depth=entry.depth};
            } else if (entry.flag == NodeType::LOWERBOUND) {
                alpha = std::max(alpha, entry.score);
            } else if (entry.flag == NodeType::UPPERBOUND) {
                beta = std::min(beta, entry.score);
            }
            if (alpha >= beta) {
                return MinMaxResult{.value=entry.score, .depth=entry.depth};
            }
        }


        Movelist moves = getSortedCapture(board, historyCutoffTable);
        MinMaxResult best{.value=Value::NEG_INFINITY, .depth=0};
        for (const Move& move: moves) {
            board.makeMove(move);
            MinMaxResult possBest = quiescenseSearch(depth-1, -beta, -alpha, ~c);
            possBest.value = -possBest.value;
            possBest.bestMove = move;
            board.unmakeMove(move);

            if (possBest.value > beta) {
                updateHistoryScore(move, depth);
                return MinMaxResult {.value=beta, .depth=possBest.depth};
            }
            if (possBest.value > alpha) {
                best = possBest;
                alpha = possBest.value;
            }
        }

        if (best.value != Value::NEG_INFINITY) {
            TTEntry entry{.score=best.value, .depth=best.depth, .bestMove=best.bestMove};
            if (best.value <= alpha) {
                entry.flag = NodeType::UPPERBOUND;
            } else if (best.value >= beta) {
                entry.flag = NodeType::LOWERBOUND;
            } else {
                entry.flag = NodeType::EXACT;
            }
        }

        int tempDepth;
        if (best.value == Value::NEG_INFINITY) {
            tempDepth = 0;
        } else {
            tempDepth = best.depth;
        }

        return MinMaxResult{.value=alpha, .depth=tempDepth, .bestMove=best.bestMove};
    }
};


extern "C" Bot* createBot() {
    return new Bot();
}

extern "C" void deleteBot(Bot* bot) {
    delete bot;
}

extern "C" const char* getBestMove(Bot* bot, const char* fen) {
    return bot->getBestMove(fen);
}

extern "C" void freeMemory(char* str) {
    delete[] str;
}

// TODO: Update cutoff table everywhere where cutoff
int main() {
    Bot* bot = createBot();
    const char *move;

    //
    move = getBestMove(bot, "8/R5p1/7p/3kp2P/8/8/5PP1/4r1K1 w - - 14 47");
    std::cout << move << std::endl;
    freeMemory((char*)move);

    // 
    move = getBestMove(bot, "8/R5p1/7p/3kp2P/8/8/4rPPK/8 w - - 16 48");
    std::cout << move << std::endl;
    freeMemory((char*)move);

    //
    move = getBestMove(bot, "8/R5p1/7p/3kp2P/8/8/5PP1/4r1K1 w - - 18 49");
    std::cout << move << std::endl;
    freeMemory((char*)move);

    // 
    move = getBestMove(bot, "8/R5p1/7p/3kp2P/8/8/4rPPK/8 w - - 20 50");
    std::cout << move << std::endl;
    freeMemory((char*)move);

    //
    move = getBestMove(bot, "8/R5p1/7p/3kp2P/8/8/5PP1/4r1K1 w - - 22 51");
    std::cout << move << std::endl;
    freeMemory((char*)move);

    // 
    move = getBestMove(bot, "8/R5p1/7p/3kp2P/8/8/4rPPK/8 w - - 24 52");
    std::cout << move << std::endl;
    freeMemory((char*)move);

    //
    move = getBestMove(bot, "8/R5p1/7p/3kp2P/8/8/5PP1/4r1K1 w - - 26 53");
    std::cout << move << std::endl;
    freeMemory((char*)move);

    // 
    move = getBestMove(bot, "8/R5p1/7p/3kp2P/8/8/4rPPK/8 w - - 28 54");
    std::cout << move << std::endl;
    freeMemory((char*)move);

    deleteBot(bot);
    return 0;
}