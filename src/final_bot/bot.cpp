
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
        maxQuiescenceDepth = 0;
        maxTime = std::chrono::microseconds(2000000);

        isOpening = true;
        isEndgame = false;

        us = Color::NONE;

        openingBook = loadOpeningsFromFile("better_filtered_openings.pgn");
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
        throw std::runtime_error("No valid move found to match the FEN.");
    }


    const char *getBestMove(const std::string& fen) {
        if (us == Color::NONE) {
            us = board.sideToMove();
        }
        if (detectEndgameType(board) != EndgameType::NONE) {
            isEndgame = true;
        }

        std::cout << fen << " " << board.getFen() << std::endl;
        if (fen != startFen) 
            updateBoard(fen);
        transpositionTable.clear();

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

        // std::cout << "HERE" << std::endl;
        MinMaxResult result = iterativeDeepening();
        Move move = result.bestMove;
        board.makeMove(move);

        std::string temp = moveToString(move);
        char *cstr = new char[temp.length() + 1];
        std::strcpy(cstr, temp.c_str());
        return cstr;
    }

    MinMaxResult iterativeDeepening() {
        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        int alpha = -Value::INFINITY;
        int beta = Value::INFINITY;

        int depth = 1;
        MinMaxResult bestMove;
        while (duration < maxTime and depth <= maxDepth) {
            std::cout << depth << std::endl;
            bestMove = alphaBeta(depth, alpha, beta, board.sideToMove());
            depth++;
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);        
        }
        return bestMove;
    }

    // TODO: Make sure this is correct
    MinMaxResult alphaBeta(int depth, int alpha, int beta, Color c) {
        uint64_t hash = board.hash();
        int origAlpha = alpha;

        if (transpositionTable.find(hash) != transpositionTable.end()) {
            TTEntry entry = transpositionTable[hash];
            if (entry.depth >= depth) {
                MinMaxResult result{.value=entry.score, .depth=depth};
                if (entry.flag == NodeType::EXACT) {
                    return result;
                } else if (entry.flag == NodeType::LOWERBOUND) {
                    alpha = std::max(alpha, entry.score);
                } else if (entry.flag == NodeType::UPPERBOUND) {
                    beta = std::min(beta, entry.score);
                }
                if (alpha >= beta) {
                    return result;
                }
            }
        }

        if (board.isGameOver().first == GameResultReason::CHECKMATE) {
            return MinMaxResult{.value=(board.sideToMove() == Color::WHITE) ? Value::MATE : -Value::MATE, .depth=depth};
        }

        // std::cout << "HERE3" << std::endl;
        if (depth <= 0) {
            MinMaxResult result = quiescenseSearch(alpha, beta, maxQuiescenceDepth, c);
            return result;
        }

        Movelist legalMoves = getSortedLegalMoves(board, historyCutoffTable, transpositionTable);
        MinMaxResult best{.value=Value::NEG_INFINITY, .depth=0};

        for (const Move& move: legalMoves) {
            board.makeMove(move);
            MinMaxResult possBest = alphaBeta(depth-1, -beta, -alpha, ~c);
            board.unmakeMove(move);

            possBest.value = -possBest.value;
            possBest.bestMove = move;

            if (possBest.value > best.value) {
                best = possBest;
            }

            if (possBest.value > alpha) {
                alpha = possBest.value;
            }

            if (alpha >= beta) {
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

    MinMaxResult quiescenseSearch(int alpha, int beta, int depth, Color c) {
        int originalAlpha = alpha;
        uint64_t hash = board.hash();
        
        int boardValue;
        if (isEndgame) {
            boardValue = evaluateEndgames(board);
        } else {
            boardValue = evaluateBoard(board);
        }
        if (boardValue >= beta) {
            // std::cout << "HERE4.5" << std::endl;
            return MinMaxResult {.value=beta, .depth=depth};
        }
        // std::cout << "HERE4" << std::endl;
        if (alpha < boardValue) {
            alpha = boardValue;
        }

        if (transpositionTable.find(hash) != transpositionTable.end()) {
            TTEntry entry = transpositionTable[hash];
            if (entry.flag == NodeType::EXACT) {
                return MinMaxResult{.value=entry.score, .depth=depth};
            } else if (entry.flag == NodeType::LOWERBOUND) {
                alpha = std::max(alpha, entry.score);
            } else if (entry.flag == NodeType::UPPERBOUND) {
                beta = std::min(beta, entry.score);
            }
            if (alpha >= beta) {
                return MinMaxResult{.value=entry.score, .depth=depth};
            }
        }

        Movelist moves = getSortedCapture(board, historyCutoffTable);
        MinMaxResult best{.value=Value::NEG_INFINITY, .depth=0};
        for (const Move& move: moves) {
            board.makeMove(move);
            MinMaxResult possBest = quiescenseSearch(-beta, -alpha, depth-1, ~c);
            board.unmakeMove(move);
            // std::cout << "HERE5" << std::endl;
            
            possBest.value = -possBest.value;
            possBest.bestMove = move;

            if (possBest.value >= beta) {
                return MinMaxResult{.value=beta, .depth=possBest.depth};
            }
            if (possBest.value > best.value) {
                best = possBest;
                alpha = possBest.value;
            }
        }

        if (best.value != Value::NEG_INFINITY) {
            TTEntry entry{.score=best.value, .depth=best.depth, .bestMove=best.bestMove};
            if (best.value <= originalAlpha) {
                entry.flag = NodeType::UPPERBOUND;
            } else if (best.value >= beta) {
                entry.flag = NodeType::LOWERBOUND;
            } else {
                entry.flag = NodeType::EXACT;
            }
            transpositionTable[hash] = entry;
        }

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
    const char* move = getBestMove(bot, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::cout << move << std::endl;
    freeMemory((char*)move);
    deleteBot(bot);
    return 0;
}