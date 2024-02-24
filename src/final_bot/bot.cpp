
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
        transpositionTable.clear();

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
        }

        MinMaxResult result = iterativeDeepening();
        Move move = result.bestMove;
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

        int maxDepth = 1;
        MinMaxResult bestMove;
        while (duration < maxTime) {
            bestMove = alphaBeta(0, maxDepth, alpha, beta);
            maxDepth++;
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
            return MinMaxResult{.value=beta, .depth=depth};
        }
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