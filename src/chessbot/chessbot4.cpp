#include <iostream>

#include <unordered_map>
#include <string>
#include <cstring>
#include <fstream>
#include <climits>
#include <chrono>

#include "chessbot4.h"

#define MAX_QUIESCENCE_DEPTH 10


struct ScoreMovePair {
    int score;
    chess::Move move; // Assuming Move is a suitable type for your chess library

    ScoreMovePair(int score, chess::Move move) : score(score), move(move) {}
};

// Comparator for sorting ScoreMovePair by score
bool compareScoreMovePairs(const ScoreMovePair& a, const ScoreMovePair& b) {
    return a.score < b.score;
}

std::map<std::string, std::vector<ScoreMovePair>> preprocessOpenings(const std::string& file_path) {
    std::map<std::string, std::vector<ScoreMovePair>> fenToBestMove;
    std::ifstream file(file_path);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return fenToBestMove; // Return empty map if file can't be opened
    }

    while (getline(file, line)) {
        auto delimiterPos = line.find(" | Score: ");
        std::string movesStr = line.substr(0, delimiterPos);
        int score = std::stoi(line.substr(delimiterPos + 10)); // "+ 10" to skip past " | Score: "

        chess::Board board; // Assuming Board is a suitable type for your chess library
        std::istringstream movesStream(movesStr);
        std::string moveSan;
        while (movesStream >> moveSan) {
            chess::Move move = chess::uci::parseSan(board, moveSan); // Assuming parseSan is a method to parse SAN move notation

            std::string fen = board.getFen(); // Assuming toFen generates a FEN string for the board state
            board.makeMove(move); // Assuming makeMove applies a move to the board

            ScoreMovePair pair(score, move);
            auto& movesList = fenToBestMove[fen];
            if (movesList.empty() || std::find_if(movesList.begin(), movesList.end(), [&pair](const ScoreMovePair& existingPair) {
                return existingPair.move == pair.move;}) == movesList.end()) {
                movesList.push_back(pair);
            }

        }

    }
    // Sorting each vector of moves by score after all moves are inserted
    for (auto& [fen, pairs] : fenToBestMove) {
        std::sort(pairs.begin(), pairs.end(), compareScoreMovePairs);
    }

    file.close();
    return fenToBestMove;
}

// Function to convert Move to std::string
std::string moveToString(const chess::Move& move) {
    std::ostringstream oss;
    oss << move; // Use the overloaded operator<<
    return oss.str(); // Convert the contents of the stream into a string
}

class ChessBot3 {
private:
    int depth;
    std::chrono::microseconds time_limit;
    std::chrono::steady_clock::time_point start_time;
    std::vector<std::vector<int>> history_table;
    bool is_opening;
    std::map<std::string, std::vector<ScoreMovePair>> fen_to_best_move;

public:
    std::unordered_map<std::string, int> fenHistory;
    int starting_eval;
    chess::Color us;

    ChessBot3(int depth, std::chrono::microseconds time_limit = std::chrono::microseconds(10)) : depth(depth), time_limit(time_limit), is_opening(true) {
        history_table.resize(64, std::vector<int>(64, 0));
        fen_to_best_move = preprocessOpenings("better_filtered_openings.pgn");
        start_time = std::chrono::steady_clock::now();
    }

    void update_history_score(const chess::Move& move, int depth) {
        this->history_table[move.from().index()][move.to().index()] += depth * depth;  // TODO: Make sure this doesn't overflow
    }

    int get_move_history_score(const chess::Move& move) {
        return this->history_table[move.from().index()][move.to().index()];
    }

    const char* get_best_move(chess::Board& board) {
        if (this->is_opening) {
            if (fen_to_best_move.count(board.getFen())) {
                chess::Move move;
                if (board.sideToMove() == chess::Color::WHITE) {
                    move = fen_to_best_move[board.getFen()].back().move;
                } else {
                    move = fen_to_best_move[board.getFen()].front().move;
                }
                std::string temp = moveToString(move);
                char* cstr = new char[temp.length() + 1];
                std::strcpy(cstr, temp.c_str());
                return cstr;
            }
            this->is_opening = false;
        }

        chess::Move best_move;
        if (is_endgame(board)) {
            // TODO: Add some endgame logic here
            best_move = select_move(board, this->depth, (board.sideToMove() == chess::Color::WHITE));
        } else {
            best_move = select_move(board, this->depth,  (board.sideToMove() == chess::Color::WHITE));
        }

        std::string temp = moveToString(best_move);
        char* cstr = new char[temp.length() + 1];
        std::strcpy(cstr, temp.c_str());
        return cstr;
    }

    chess::Move select_move(chess::Board& board, int depth, bool is_maximizing) {
        chess::Movelist legal_moves;
        chess::movegen::legalmoves(legal_moves, board);

        std::sort(legal_moves.begin(), legal_moves.end(), [this](const chess::Move& a, const chess::Move& b) {
            return get_move_history_score(a) > get_move_history_score(b);
        });


        int best_eval = is_maximizing ? INT_MIN : INT_MAX;
        chess::Move best_move;
        int alpha = INT_MIN;
        int beta = INT_MAX;
        for (const auto& move : legal_moves) {
            board.makeMove(move);
            int eval = alpha_beta_minimax_helper(board, depth - 1, alpha, beta, !is_maximizing);
            board.unmakeMove(move);

            // std::cout << eval << ", " << INT_MIN << std::endl;
            if ((is_maximizing && eval > best_eval) || (!is_maximizing && eval < best_eval)) {
                best_eval = eval;
                best_move = move;
            }

            if (is_maximizing) {
                alpha = std::max(alpha, eval);
            } else {
                beta = std::min(beta, eval);
            }

            if (beta <= alpha) {
                update_history_score(move, this->depth - depth);
                break;
            }
        }

        std::cout << best_eval << std::endl;
        return best_move;
    }

    int alpha_beta_minimax_helper(chess::Board& board, int depth, int alpha, int beta, bool is_maximizing) {
        if (board.isGameOver().first != chess::GameResultReason::NONE) {
            return evaluate_board(board, depth);
        } else if (depth == 0) {
            // int eval_q = quiescence_search(board, alpha, beta, is_maximizing);
            // int eval_b = evaluate_board(board, depth);
            // if (is_maximizing) {
            //     return std::max(eval_b, eval_q);
            // } else {
            //     return std::min(eval_b, eval_q);
            // }
            return evaluate_board(board, depth);
        } 

        chess::Movelist legal_moves;
        chess::movegen::legalmoves(legal_moves, board);
        std::sort(legal_moves.begin(), legal_moves.end(), [this](const chess::Move& a, const chess::Move& b) {
            return get_move_history_score(a) > get_move_history_score(b);
        });

        int best_eval = is_maximizing ? INT_MIN : INT_MAX;
        for (const auto& move : legal_moves) {
            board.makeMove(move);
            int eval = alpha_beta_minimax_helper(board, depth - 1, alpha, beta, !is_maximizing);
            board.unmakeMove(move);

            if (is_maximizing) {
                best_eval = std::max(best_eval, eval);
                alpha = std::max(alpha, eval);
            } else {
                best_eval = std::min(best_eval, eval);
                beta = std::min(beta, eval);
            }

            if (beta <= alpha) {
                update_history_score(move, this->depth - depth);
                break;
            }
        }
        return best_eval;
    }

    // TODO: Fix this
    int quiescence_search(chess::Board& board, int alpha, int beta, bool is_maximizing) {
        int best_eval = is_maximizing ? INT_MIN : INT_MAX;
        this->start_time = std::chrono::steady_clock::now();

        // Continuously deepen the search until the time limit is reached.
        for (int max_qdepth = 1; max_qdepth <= MAX_QUIESCENCE_DEPTH; max_qdepth++) {
            auto current_time = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(current_time - start_time);
            if (elapsed >= time_limit) {
                break; // Stop the search if the time limit has been reached.
            }

            int eval = quiescence_search_inner(board, alpha, beta, is_maximizing, 0, max_qdepth);
            // std::cout << "eval: " << eval << " is maximizing: " << is_maximizing << " ,best eval: " << best_eval << std::endl;

            // Update best evaluation based on search outcome.
            if (is_maximizing) {
                best_eval = std::max(best_eval, eval);
                alpha = std::max(alpha, best_eval);
            } else {
                best_eval = std::min(best_eval, eval);
                beta = std::min(beta, best_eval);
            }

            // Optional: Implement any early termination logic here.
            // For example, if eval represents a checkmate or a draw, you might break early.
        }

        return best_eval;
    }

    int quiescence_search_inner(chess::Board& board, int alpha, int beta, bool is_maximizing, int qdepth, int max_qdepth) {
        if (qdepth >= max_qdepth || board.isGameOver().first != chess::GameResultReason::NONE) {
            return evaluate_board(board, max_qdepth - qdepth); // Evaluate the board directly if max depth is reached.
        }

        int stand_pat = evaluate_board(board, 0);
        if (is_maximizing && stand_pat >= beta) return beta;
        if (!is_maximizing && stand_pat <= alpha) return alpha;

        if (is_maximizing) alpha = std::max(alpha, stand_pat);
        else beta = std::min(beta, stand_pat);

        chess::Movelist legal_moves;
        chess::movegen::legalmoves<chess::movegen::MoveGenType::CAPTURE>(legal_moves, board);

        std::sort(legal_moves.begin(), legal_moves.end(), [this](const chess::Move& a, const chess::Move& b) {
            return get_move_history_score(a) > get_move_history_score(b);
        });
        

        int best_eval = is_maximizing ? INT_MIN : INT_MAX;
        for (const auto& move : legal_moves) {
            board.makeMove(move);
            int eval = quiescence_search_inner(board, alpha, beta, !is_maximizing, qdepth + 1, max_qdepth);
            board.unmakeMove(move);

            if (is_maximizing) {
                alpha = std::max(alpha, eval);
                best_eval = std::max(best_eval, eval);
            } else {
                beta = std::min(beta, eval);
                best_eval = std::min(best_eval, eval);
            }
            if (alpha >= beta) break;
        }

        return best_eval;
    }

    int evaluate_board(chess::Board board, int depth) {
        auto temp = board.isGameOver();
        chess::GameResultReason grr = temp.first;
        if (grr == chess::GameResultReason::CHECKMATE) {
            if (board.sideToMove() == chess::Color::WHITE) return -1000000 - depth;  // TODO: Check if this is correct
            else return 1000000 + depth;
        } else if (grr == chess::GameResultReason::STALEMATE or grr == chess::GameResultReason::INSUFFICIENT_MATERIAL) {
            return 0;
        } else if (is_threefold_repetition(board)) {
            std::cout << "Threefold repetition, " << starting_eval << " us: " << us << std::endl;
            if (this->us == chess::Color::WHITE and this->starting_eval > -1) {
                return -1000000;
            } else if (this->us == chess::Color::BLACK and this->starting_eval < 1) {
                return 1000000;
            }
            return 0;
        }

        std::map<chess::PieceType, const std::vector<std::vector<int>>> piece_square_tables = {
            {chess::PieceType::PAWN, PAWN_TABLE},
            {chess::PieceType::KNIGHT, KNIGHTS_TABLE},
            {chess::PieceType::ROOK, ROOKS_TABLE},
            {chess::PieceType::BISHOP, BISHOPS_TABLE},
            {chess::PieceType::QUEEN, QUEENS_TABLE},
        };

        if (is_endgame(board)) {
            piece_square_tables.insert({chess::PieceType::KING, KINGS_TABLE_ENDGAME});
        } else {
            piece_square_tables.insert({chess::PieceType::KING, KINGS_TABLE_OPENING});
        }

        int board_value = 0;
        for (const auto& [piece_type, value] : PIECE_VALUES) {
            for (const auto& color : {chess::Color::WHITE, chess::Color::BLACK}) {
                int sign = color == chess::Color::WHITE ? 1 : -1;
                auto pieces = board.pieces(piece_type, color);
                int material_value = value * pieces.count();
                int positional_value = 0;
                
                chess::Bitboard copy = pieces;
                while (copy) {
                    uint8_t pos = copy.lsb();
                    int row = pos/8;
                    int col = pos%8;
                    (void)copy.pop();

                    if (color == chess::Color::WHITE) {
                        positional_value += piece_square_tables[piece_type][row][col];
                    } else {
                        positional_value += piece_square_tables[piece_type][7-row][7-col];
                    }
                }
                board_value += sign * (material_value + positional_value);
            }
        }
        return board_value;
    }

    bool is_threefold_repetition(chess::Board board) {
        std::string fen = board.getFen();
        std::string hash_fen = fen.substr(0, fen.length() - 6);

        if (this->fenHistory.find(hash_fen) != this->fenHistory.end()) {
            return this->fenHistory[hash_fen] >= 2;
        }
        return false;
    }

    bool is_endgame(chess::Board board) {
        chess::Bitboard queens = board.pieces(chess::PieceType::QUEEN);
        bool has_queens = !queens.empty();
        int num_pieces = board.occ().count();
        return (!has_queens && num_pieces < 15) || num_pieces < 12;
    }
};

extern "C" ChessBot3* new_chessbot(int depth) {
    return new ChessBot3(depth);
}

extern "C" void delete_chessbot(ChessBot3* bot) {
    delete bot;
}

extern "C" const char* get_best_move(ChessBot3* bot, const char* board_fen) {

    std::string board_fen_str(board_fen);
    std::string board_fen_substr = board_fen_str.substr(0, board_fen_str.length() - 6);
    bot->fenHistory[board_fen_substr]++;
    
    for (auto const& [key, val] : bot->fenHistory) {
        std::cout << key << ": " << val << std::endl;
    }

    bot->starting_eval = bot->evaluate_board(chess::Board(board_fen), 0);
    bot->us = chess::Board(board_fen).sideToMove();
    chess::Board board(board_fen);
    return bot->get_best_move(board);
}

extern "C" void free_allocated_memory(char* ptr) {
    delete[] ptr;
}


int main() {
    ChessBot3* bot = new_chessbot(6);
    const char* board_fen = "4Rbk1/p4p1p/1n4p1/5b2/4N3/N1Pp2P1/PP5P/6K1 w - - 4 28";
    const char* best_move = get_best_move(bot, board_fen);
    std::cout << "Best move: " << best_move << std::endl;

    // chess::Board board_played("r7/1p1bkpp1/p3p2p/3n4/4P3/1P1B1P2/P5PP/R4RK1 b - - 0 20");
    // chess::Board board_better("1r5r/1p1Nkpp1/p3p2p/3n4/8/1P1BPP2/P5PP/2R2RK1 b - - 0 20");
    // ... so you can come to the correct conclusion, huh ??? Then why the hell don't you
    // ... it wasn't deep enough so you didn't know you can take back ... TODO: probably should special 
    // case that somehow
    // Python does this as well, as the issue really is with the depth. -> Horizon effect
    // std::cout << bot->evaluate_board(board_played, 1) << ", " <<
    // bot->evaluate_board(board_better, 1) << std::endl;


    free_allocated_memory(const_cast<char*>(best_move));
    delete_chessbot(bot);


    return 0;
}

// Here we let ourselves get forked (b3d2):
// 8/ppN4p/4Q3/2p1pkp1/4p3/8/PPP1N1PP/1K1R1B1R b - - 6 26

// Didn't move rook away -> Horizon effect
// r6r/1p1bkpp1/pN2p2p/8/8/1PnBPP2/P5PP/R4RK1 b - - 1 18


// The hell ???
// 8/1Pk5/3R4/4PP2/P7/4K3/1r3P2/8 w - - 9 63
// ->
// 8/1PkR4/8/4PP2/P7/4K3/1r3P2/8 b - - 10 63
// ->
// 1k6/1P1R4/8/4PP2/P7/4K3/1r3P2/8 w - - 11 64


