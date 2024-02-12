#include <iostream>

#include <unordered_map>
#include <string>
#include <cstring>
#include <fstream>
#include <climits>

#include "chessbot4.h"


#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))




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
                return existingPair.move == pair.move; // Assuming Move has an equality operator
            }) == movesList.end()) {
                movesList.push_back(pair);
            }

            // This might need adjustment depending on how your chess library handles move equality and sorting
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
    int time_limit;
    int start_time;
    std::vector<std::vector<int>> history_table;
    bool is_opening;

public:
    std::map<std::string, std::vector<ScoreMovePair>> fen_to_best_move;
    ChessBot3(int depth, int time_limit = 10) : depth(depth), time_limit(time_limit), start_time(0), is_opening(true) {
        history_table.resize(64, std::vector<int>(64, 0));
        fen_to_best_move = preprocessOpenings("openings_filtered.pgn");
    }

    void update_history_score(chess::Move move, int depth) {
        history_table[move.from().index()][move.to().index()] += depth * depth;
    }

    int get_move_history_score(chess::Move move) {
        return history_table[move.from().index()][move.to().index()];
    }

    const char* get_best_move(chess::Board board) {
        if (is_opening) {
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
            is_opening = false;
        }

        chess::Move best_move;
        if (is_endgame(board)) {
            best_move = select_move(board, depth + 1, INT_MIN, INT_MAX, board.sideToMove() == chess::Color::WHITE);
        } else {
            best_move = select_move(board, depth,  INT_MIN, INT_MAX, board.sideToMove() == chess::Color::WHITE);
        }
        std::string temp = moveToString(best_move);
        char* cstr = new char[temp.length() + 1];
        std::strcpy(cstr, temp.c_str());
        return cstr;
    }

    chess::Move select_move(chess::Board board, int depth = 2, float alpha=INT_MIN, float beta=INT_MAX, bool is_maximizing = true) {
        chess::Movelist legal_moves;
        chess::movegen::legalmoves(legal_moves, board);

        std::sort(legal_moves.begin(), legal_moves.end(), [this](const chess::Move& a, const chess::Move& b) {
            return get_move_history_score(a) > get_move_history_score(b);
        });

        int best_eval = is_maximizing ? INT_MIN : INT_MAX;
        chess::Move best_move;
        for (const auto& move : legal_moves) {
            board.makeMove(move);
            int eval = alpha_beta_minimax_helper(board, depth - 1, alpha, beta, !is_maximizing);
            board.unmakeMove(move);

            if ((is_maximizing && eval > best_eval) || (!is_maximizing && eval < best_eval)) {
                best_eval = eval;
                best_move = move;
            }

            if (is_maximizing) {
                alpha = MAX(alpha, eval);
            } else {
                beta = MIN(beta, eval);
            }

            if (beta <= alpha) {
                update_history_score(move, this->depth - depth);
                break;
            }
        }
        return best_move;
    }

    int alpha_beta_minimax_helper(chess::Board board, int depth, int alpha = INT_MIN, int beta = INT_MAX, bool is_maximizing = true) {
        if (depth == 0 or board.isGameOver().first != chess::GameResultReason::NONE) {
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

    int evaluate_board(chess::Board board, int depth) {
        auto temp = board.isGameOver();
        chess::GameResultReason grr = temp.first;
        if (grr == chess::GameResultReason::CHECKMATE) {
            if (board.sideToMove() == chess::Color::WHITE) return -1000000;  // TODO: Check if this is correct
            else return 1000000;
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
    chess::Board board(board_fen);
    return bot->get_best_move(board);
}

extern "C" void free_allocated_memory(char* ptr) {
    delete[] ptr;
}


int main() {
    ChessBot3* bot = new_chessbot(4);
    const char* board_fen = "r4bQ1/pppk1N2/6p1/3K4/2B3q1/2BR4/P6P/8 b - - 5 24";
    const char* best_move = get_best_move(bot, board_fen);
    std::cout << "Best move: " << best_move << std::endl;
    free_allocated_memory(const_cast<char*>(best_move));
    delete_chessbot(bot);
    return 0;
}


// b3d2 in 8/ppN4p/4Q3/2p1pkp1/4p3/8/PPP1N1PP/1K1R1B1R b - - 6 26