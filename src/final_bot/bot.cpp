
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
        maxQuiescenceDepth = 4;
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
            std::cout << "We found ourselves in the endgame" << std::endl;
            score = evaluateEndgames(board);
        } else {
            score += evaluateMaterialAndPosition(board, Color::WHITE, false);
            score += evaluateMaterialAndPosition(board, Color::BLACK, false);
            // score += evaluateMaterial(board, Color::WHITE, false);
            // score += evaluateMaterial(board, Color::BLACK, false);
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
            // std::cout << "Depth: " << depth << " Score: " << bestMove.value << " Best Move: " << moveToString(bestMove.bestMove) << std::endl;
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
                    return MinMaxResult{.value=entry.score, .depth=depth, .bestMove=entry.bestMove};
                } else if (entry.flag == NodeType::LOWERBOUND) {
                    alpha = std::max(alpha, entry.score);
                } else if (entry.flag == NodeType::UPPERBOUND) {
                    beta = std::min(beta, entry.score);
                }
                if (alpha >= beta) {
                    return MinMaxResult{.value=entry.score, .depth=depth, .bestMove=entry.bestMove};
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

    MinMaxResult alphaBetaOld(int depth, int alpha, int beta, Color c) {
        uint64_t hash = board.hash();

        if (transpositionTable.find(hash) != transpositionTable.end()) {
            TTEntry entry = transpositionTable[hash];
            if (entry.depth >= depth) {
                if (entry.flag == NodeType::EXACT) {
                    return MinMaxResult{.value=entry.score, .depth=depth, .bestMove=entry.bestMove};
                } else if (entry.flag == NodeType::LOWERBOUND) {
                    alpha = std::max(alpha, entry.score);
                } else if (entry.flag == NodeType::UPPERBOUND) {
                    beta = std::min(beta, entry.score);
                }
                if (alpha >= beta) {
                    return MinMaxResult{.value=entry.score, .depth=depth, .bestMove=entry.bestMove};
                }
            }
        }

        if (board.isGameOver().first == GameResultReason::CHECKMATE) {
            return MinMaxResult{.value=(board.sideToMove() == Color::WHITE) ? Value::MATE : -Value::MATE, .depth=depth, .bestMove=Move::NO_MOVE};
        }

        if (depth <= 0) {
            return quiescenseSearch(maxQuiescenceDepth, alpha, beta, c);
        }

        Movelist legalMoves = getSortedLegalMoves(board, historyCutoffTable, transpositionTable);
        MinMaxResult best{.value=(c == Color::WHITE? Value::NEG_INFINITY: Value::INFINITY), .depth=0};

        for (const Move& move: legalMoves) {
            board.makeMove(move);
            MinMaxResult possBest = alphaBeta(depth-1, alpha, beta, ~c);
            board.unmakeMove(move);

            if (c == Color::WHITE) {
                if (possBest.value > best.value) {
                    best = possBest;
                    best.bestMove = move;
                }
                if (best.value > beta) {
                    updateHistoryScore(move, depth);
                    break;
                }
                alpha = std::max(alpha, best.value);
            } else {
                if (possBest.value < best.value) {
                    best = possBest;
                    best.bestMove = move;
                }
                if (best.value < alpha) {
                    updateHistoryScore(move, depth);
                    break;
                }
                beta = std::min(beta, best.value);
            }
        }
        
        TTEntry entry{.score=best.value, .depth=best.depth, .bestMove=best.bestMove};
        if (c == Color::WHITE) {
            if (best.value <= alpha) {
                entry.flag = NodeType::UPPERBOUND;
            } else if (best.value >= beta) {
                entry.flag = NodeType::LOWERBOUND;
            } else {
                entry.flag = NodeType::EXACT;
            }
        } else {
            if (best.value >= beta) {
                entry.flag = NodeType::UPPERBOUND;
            } else if (best.value <= alpha) {
                entry.flag = NodeType::LOWERBOUND;
            } else {
                entry.flag = NodeType::EXACT;
            }
        }
        transpositionTable[hash] = entry;

        return best;
    }

    MinMaxResult quiescenseSearch(int depth, int alpha, int beta, Color c) {
        int max = (c == Color::WHITE ? 1 : -1);
        int boardValue = max * evaluateBoard(board, depth);
        if (boardValue >= beta) {
            return MinMaxResult {.value=beta, .depth=depth};
        }
        if (alpha < boardValue) {
            alpha = boardValue;
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
                return MinMaxResult {.value=beta, .depth=depth};
            }
            if (possBest.value > alpha) {
                best = possBest;
                alpha = possBest.value;
            }
        }

        return MinMaxResult{.value=alpha, .depth=depth, .bestMove=best.bestMove};
    }

    MinMaxResult quiescenseSearchOld(int depth, int alpha, int beta, Color c) {
        uint64_t hash = board.hash();
        int boardValue = evaluateBoard(board, depth);

        if (c == Color::WHITE) {
            if (boardValue >= beta) {
                return MinMaxResult {.value=beta, .depth=depth};
            }
            if (boardValue > alpha) {
                alpha = boardValue;
            }
        } else {
            if (boardValue <= alpha) {
                return MinMaxResult {.value=alpha, .depth=depth};
            }
            if (boardValue < beta) {
                beta = boardValue;
            }
        }

        if (transpositionTable.find(hash) != transpositionTable.end()) {
            TTEntry entry = transpositionTable[hash];
            if (entry.flag == NodeType::EXACT) {
                return MinMaxResult{.value=entry.score, .depth=depth, .bestMove=entry.bestMove};
            } else if (entry.flag == NodeType::LOWERBOUND) {
                alpha = std::max(alpha, entry.score);
            } else if (entry.flag == NodeType::UPPERBOUND) {
                beta = std::min(beta, entry.score);
            }
            if (alpha >= beta) {
                return MinMaxResult{.value=entry.score, .depth=depth, .bestMove=entry.bestMove};
            }
        }

        Movelist moves = getSortedCapture(board, historyCutoffTable);
        MinMaxResult best{.value=(c==Color::WHITE?Value::NEG_INFINITY: Value::INFINITY), .depth=0};
        for (const Move& move: moves) {
            board.makeMove(move);
            MinMaxResult possBest = quiescenseSearch(depth-1, alpha, beta, ~c);
            board.unmakeMove(move);
            
            if (c == Color::WHITE) {
                if (possBest.value >= beta) {
                    return MinMaxResult {.value=beta, .depth=depth};
                }
                if (possBest.value > alpha) {
                    alpha = possBest.value;
                }
            } else {
                if (possBest.value <= alpha) {
                    return MinMaxResult {.value=alpha, .depth=depth};
                }
                if (possBest.value < beta) {
                    beta = possBest.value;
                }
            }
        }

        TTEntry entry{.score=best.value, .depth=best.depth, .bestMove=best.bestMove};
        if (c == Color::WHITE) {
            if (best.value <= alpha) {
                entry.flag = NodeType::UPPERBOUND;
            } else if (best.value >= beta) {
                entry.flag = NodeType::LOWERBOUND;
            } else {
                entry.flag = NodeType::EXACT;
            }
        } else {
            if (best.value >= beta) {
                entry.flag = NodeType::UPPERBOUND;
            } else if (best.value <= alpha) {
                entry.flag = NodeType::LOWERBOUND;
            } else {
                entry.flag = NodeType::EXACT;
            }
        }
        transpositionTable[hash] = entry;

        int tmpDepth;
        if (best.value == Value::NEG_INFINITY) {
            tmpDepth = depth;
        } else {
            tmpDepth = best.depth;
        }
        return MinMaxResult{.value=alpha, .depth=tmpDepth};
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

int main() {
    Bot* bot = createBot();
    // 
    const char* move = getBestMove(bot, "8/8/2R5/2P5/5PP1/4k3/8/7K w - - 1 102");
    std::cout << move << std::endl;
    freeMemory((char*)move);

    // 
    move = getBestMove(bot, "8/8/2R5/2P2P2/5kP1/8/8/7K w - - 1 103");
    std::cout << move << std::endl;
    freeMemory((char*)move);

    // // 
    // move = getBestMove(bot, "8/5R2/2p1k3/2P5/8/4B3/5PP1/6K1 w - - 62 105");
    // std::cout << move << std::endl;
    // freeMemory((char*)move);

    // // 
    // move = getBestMove(bot, "8/6R1/2p5/2P1k3/8/4B3/5PP1/6K1 w - - 64 106");
    // std::cout << move << std::endl;
    // freeMemory((char*)move);

    // //
    // move = getBestMove(bot, "8/5R2/2p1k3/2P5/8/4B3/5PP1/6K1 w - - 66 107");
    // std::cout << move << std::endl;
    // freeMemory((char*)move);

    // //
    // move = getBestMove(bot, "8/6R1/2p5/2P1k3/8/4B3/5PP1/6K1 w - - 68 108");
    // std::cout << move << std::endl;
    // freeMemory((char*)move);

    // //
    // move = getBestMove(bot, "8/5R2/2p1k3/2P5/8/4B3/5PP1/6K1 w - - 70 109");
    // std::cout << move << std::endl;
    // freeMemory((char*)move);

    // // 
    // move = getBestMove(bot, "8/2R5/2p5/2P1k3/8/4B3/5PP1/6K1 w - - 72 110");
    // std::cout << move << std::endl;
    // freeMemory((char*)move);



    deleteBot(bot);
    return 0;
}