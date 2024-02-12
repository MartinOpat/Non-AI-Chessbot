#include <iostream>

#include <unordered_map>
#include <string>
#include <fstream>

#include "chessbot3.h"
#include <climits>


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
            board.makeMove(move); // Assuming makeMove applies a move to the board

            std::string fen = board.getFen(); // Assuming toFen generates a FEN string for the board state
            ScoreMovePair pair(score, move);
            auto& movesList = fenToBestMove[fen];
            if (movesList.empty() || std::find_if(movesList.begin(), movesList.end(), [&pair](const ScoreMovePair& existingPair) {
                return existingPair.move == pair.move; // Assuming Move has an equality operator
            }) == movesList.end()) {
                movesList.push_back(pair);
            }

            // This might need adjustment depending on how your chess library handles move equality and sorting
        }

        // Sorting each vector of moves by score after all moves are inserted
        for (auto& [fen, pairs] : fenToBestMove) {
            std::sort(pairs.begin(), pairs.end(), compareScoreMovePairs);
        }
    }

    file.close();
    return fenToBestMove;
}

class ChessBot3 {
private:
    int depth;
    int time_limit;
    int start_time;
    std::vector<std::vector<int>> history_table;
    std::map<std::string, std::vector<ScoreMovePair>> fen_to_best_move;
    bool is_opening;

public:
    ChessBot3(int depth = 2, int time_limit = 10) : depth(depth), time_limit(time_limit), start_time(0), is_opening(true) {
        history_table.resize(64, std::vector<int>(64, 0));
        fen_to_best_move = preprocessOpenings("src/chessbot/openings_filtered.pgn");
    }

    void update_history_score(chess::Move move, int depth) {
        history_table[move.from().index()][move.to().index()] += depth * depth;
    }

    int get_move_history_score(chess::Move move) {
        return history_table[move.from().index()][move.to().index()];
    }

    chess::Move get_best_move(chess::Board board) {
        if (is_opening) {
            if (fen_to_best_move.count(board.getFen())) {
                if (board.sideToMove() == chess::Color::WHITE) {
                    return fen_to_best_move[board.getFen()].back().move;
                } else {
                    return fen_to_best_move[board.getFen()].front().move;
                }
            }
            is_opening = false;
        }

        chess::Move best_move;
        if (is_endgame(board)) {
            best_move = select_move(board, depth + 1, board.sideToMove() == chess::Color::WHITE);
        } else {
            best_move = select_move(board, depth, board.sideToMove() == chess::Color::WHITE);
        }
        return best_move;
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
            int eval = alpha_beta_minimax_helper(board, depth - 1, alpha, beta, not is_maximizing);
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
                update_history_score(move, depth - this->depth);
                break;
            }
        }
        return best_move;
    }

    int alpha_beta_minimax_helper(chess::Board board, int depth = 3, int alpha = INT_MIN, int beta = INT_MAX, bool is_maximizing = true) {
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
                update_history_score(move, depth - this->depth);
                break;
            }
        }
        return best_eval;
    }

    int evaluate_board(chess::Board board, int depth) {
        auto temp = board.isGameOver();
        chess::GameResultReason grr = temp.first;
        chess::GameResult gres = temp.second;
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
            piece_square_tables.insert({chess::PieceType::KING, KINGS_TABLE_OPENING});
        } else {
            piece_square_tables.insert({chess::PieceType::KING, KINGS_TABLE_ENDGAME});
        }

        int board_value = 0;
        for (const auto& [piece_type, value] : PIECE_VALUES) {
            for (const auto& color : {chess::Color::WHITE, chess::Color::BLACK}) {
                int sign = color == chess::Color::WHITE ? 1 : -1;
                auto pieces = board.pieces(piece_type, color);
                int material_value = value * pieces.size();
                int positional_value = 0;
                for (const auto& square : pieces) {
                    if (color == chess::Color::WHITE) {
                        positional_value += piece_square_tables[piece_type][square];
                    } else {
                        positional_value += piece_square_tables[piece_type][chess::squareMirror(square)];
                    }
                }
                board_value += sign * (material_value + positional_value);
            }
        }
        return board_value;
    }

    bool is_endgame(chess::Board board) {
        bool has_queens = false;
        for (const auto& [square, piece] : board.getPieceMap()) {
            if (piece.getType() == chess::QUEEN) {
                has_queens = true;
                break;
            }
        }
        int num_pieces = board.getPieceMap().size();
        return (!has_queens && num_pieces < 15) || num_pieces < 12;
    }
};

